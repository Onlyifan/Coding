#include "workflow/HttpMessage.h"
#include "workflow/RedisMessage.h"
#include "workflow/SubTask.h"
#include "workflow/WFFacilities.h"
#include "workflow/WFHttpServer.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"
#include <climits>
#include <cstddef>
#include <ctime>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <mutex>
#include <nlohmann/json.hpp>
#include <regex>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <type_traits>
#include <unistd.h>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum) {
    gWaitGroup.done( );
}

struct Context {
    size_t idxNumNow;
    size_t idxTotal;
    WFHttpTask *serverTask;
};

class Netdisk {
public:
    static void handleInvalidRequest(protocol::HttpResponse *resp) {
        resp->set_status_code("404");
        resp->set_reason_phrase("Method Not Found");
    }

    static void handleValidRequest(protocol::HttpResponse *resp) {
        resp->set_status_code("200");
        resp->set_reason_phrase("OK");
    }

    static unordered_map<string, string> parseArgs(const string &uri) {
        unordered_map<string, string> result;
        auto pathIndex = uri.find("?");
        result.emplace("httpPath", uri.substr(0, pathIndex));

        if (pathIndex == std::string::npos) {
            return result;
        }

        string parameters = uri.substr(pathIndex + 1);

        for (auto &ch : parameters) {
            if (ch == '&') {
                ch = ' ';
            }
        }

        istringstream iss(parameters);
        string KVpair;
        while (iss >> KVpair) {
            auto it = KVpair.find("=");
            if (it == string::npos) {
                cerr << "client http request args error!\n";
                continue;
            }

            result.emplace(KVpair.substr(0, it), KVpair.substr(it + 1));
        }


        // while ((andIndex = uri.find("&", pathIndex) != string::npos)) {
        //     string keypair = uri.substr(pathIndex, andIndex);

        //     auto divideIndex = keypair.find("=");
        //     if (divideIndex == string::npos) {
        //         cerr << "Valid http request parametrs!\n";
        //         continue;
        //     }

        //     string key = keypair.substr(0, keypair.find("="));
        //     string value = keypair.substr(divideIndex + 1, andIndex);
        //     result.emplace_back(std::move(key), std::move(value));

        //     pathIndex = andIndex + 1;
        // }

        return result;
    }

    static void startRedisSeries(const vector<pair<string, string>> &params, const string &method, redis_callback_t redisCallback = nullptr) {
        string uploadID;

        for (auto &KVpair : params) {
            if (KVpair.first == "uploadID") {
                uploadID = KVpair.second;
                break;
            }
        }

        for (int i = 1; i < params.size( ); ++i) {
            auto redisTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);

            redisTask->get_req( )->set_request(method, { uploadID, params[i].first, params[i].second });
            redisTask->start( );
        }
    }

    static void RedisTaskCallback(WFRedisTask *redisTask, int index) {
        auto resp = redisTask->get_resp( );
        protocol::RedisValue value;
        resp->get_result(value);
        Context *pctext = (Context *)series_of(redisTask)->get_context( );

        if (index == 0) {
            if (!value.is_array( )) {
                cerr << "redis task result error!\n";
                return;
            }

            for (size_t i = 0; i != value.arr_size( ); ++i) {
                if (value.arr_at(i).is_string( ) && value.arr_at(i).string_value( ).substr(0, 4) == "idx_") {
                    ++pctext->idxNumNow;
                }
            }

        } else {
            pctext->idxTotal = ::stoi(value.string_value( ));
            if (pctext->idxNumNow < pctext->idxTotal) {
                pctext->serverTask->get_resp( )->append_output_body("Not complete");
            } else if (pctext->idxNumNow == pctext->idxTotal) {
                pctext->serverTask->get_resp( )->append_output_body("Complete");
            } else {
                pctext->serverTask->get_resp( )->append_output_body("Database Error!");
            }
        }
    }
};


void process(WFHttpTask *serverTask) {
    cout << "process is called\n";
    protocol::HttpRequest *req = serverTask->get_req( );
    protocol::HttpResponse *resp = serverTask->get_resp( );
    resp->set_http_version("HTTP/1.1");

    char *cbody;
    size_t bodySize;

    req->get_parsed_body((const void **)&cbody, &bodySize);

    unordered_map<string, string> parsedURI = Netdisk::parseArgs(req->get_request_uri( ));

    if (req->get_method( ) != string("POST")) {
        Netdisk::handleInvalidRequest(resp);
        return;
    } else {
        Netdisk::handleValidRequest(resp);
    }


    vector<pair<string, string>> redisParams;

    if (parsedURI["httpPath"] == "/file/mupload/init") {
        string body(cbody, bodySize);
        nlohmann::json JSON = nlohmann::json::parse(body);

        string uploadID = parsedURI["name"] + ::to_string(time(nullptr));

        redisParams.emplace_back("uploadID", uploadID);
        redisParams.emplace_back("filename", JSON["filename"]);
        redisParams.emplace_back("hash", JSON["hash"]);
        redisParams.emplace_back("chunkSize", "1024");

        size_t size = JSON["size"];
        redisParams.emplace_back("size", ::to_string(size));
        size_t chunkSize = 1024;
        size_t chunkCount = (size - 1) / chunkSize + 1;

        redisParams.emplace_back("chunkCount", ::to_string(chunkCount));
        Netdisk::startRedisSeries(redisParams, "HSET");


        // 设置响应报文
        resp->add_header_pair("uploadID", uploadID);
        resp->add_header_pair("chunkSize", ::to_string(chunkSize));
        resp->add_header_pair("chunkCount", ::to_string(chunkCount));

    } else if (parsedURI["httpPath"] == "/file/mupload/upppart") {
        string &uploadID = parsedURI["uploadID"];
        string &idx = parsedURI["idx"];
        redisParams.emplace_back("uploadID", uploadID);
        redisParams.emplace_back("idx_" + idx, "114514");

        Netdisk::startRedisSeries(redisParams, "HSET");

        ::mkdir(uploadID.c_str( ), 0755);

        int fd = ::open((uploadID + "/" + idx).c_str( ), O_RDWR | O_CREAT | O_TRUNC, 0666);

        size_t ret = write(fd, cbody, bodySize);
        if (ret != bodySize) {
            close(fd);
            unlink((uploadID + "/" + idx).c_str( ));
            return;
        }

    } else if (parsedURI["httpPath"] == "/file/mupload/complete") {
        string uploadID = parsedURI["uploadID"];

        Context *text = new Context( );
        series_of(serverTask)->set_context((void *)text);
        text->serverTask = serverTask;

        auto redisTask0 = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, bind(&Netdisk::RedisTaskCallback, std::placeholders::_1, 0));
        redisTask0->get_req( )->set_request("HGETALL", { uploadID });
        series_of(serverTask)->push_back(redisTask0);

        auto redisTask1 = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, bind(&Netdisk::RedisTaskCallback, std::placeholders::_1, 1));
        redisTask1->get_req( )->set_request("HGET", { uploadID, "chunkCount" });
        series_of(serverTask)->push_back(redisTask1);

        series_of(serverTask)->set_callback([](const SeriesWork *work) {
            delete (Context *)work->get_context( );
        });
    }
}

int main( ) {
    WFHttpServer svr(process);
    svr.start(23334);

    gWaitGroup.wait( );
    svr.stop( );
}