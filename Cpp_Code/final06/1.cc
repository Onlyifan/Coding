#include <iostream>
#include <time.h>
#include <functional>
#include <openssl/sha.h>
#include <workflow/WFFacilities.h>
/* #include <workflow/HttpUtil.h> */
/* #include <workflow/MySQLMessage.h> */
/* #include <workflow/MySQLResult.h> */
#include <wfrest/HttpServer.h>
#include <wfrest/json.hpp>
using namespace std;
using namespace wfrest;
using namespace std::placeholders;
#define SIZE 4096

class Sharding
{
public:
    Sharding(int count)
    :_waitGroup(count){}
    ~Sharding(){}
    void start(unsigned short port);
    void load();
private:
    void login();
    void loginCallback(const HttpReq *req, HttpResp *resp, SeriesWork *series);
    void loginCallback2(WFRedisTask *redisTask, HttpResp* resp);
    void upload();
private:
    WFFacilities::WaitGroup _waitGroup;
    wfrest::HttpServer _server;
};



void Sharding::start(unsigned short port){
    if(_server.start(port) == 0){
        _server.list_routes();
        _waitGroup.wait();
        _server.stop();
    }
    else{
        cout << "start failed!\n";
    }
}

void Sharding::load(){
    login();
    /* upload(); */
}

void Sharding::login(){
    using namespace std::placeholders; 
    _server.POST("/login", bind(&Sharding::loginCallback, this, _1, _2, _3));
}

void Sharding::loginCallback(const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series){
    using Json = nlohmann::json;
    string body = req->body();
    Json info = Json::parse(body);
    string filename = info["filename"];
    string filehash = info["filehash"];
    int filesize = info["filesize"];

    time_t now = ::time(NULL) % 1000;
    string uploadID = "yangjian" + to_string(now);

    int chunksize = SIZE;
    int chunkcount;
    if(filesize % chunksize == 0){
        chunkcount = filesize / chunksize + 1;
    }
    else{
        chunkcount = filesize / chunksize;
    }

    vector<vector<string>> vec = {
        {uploadID, "filename", filename},
        {uploadID, "filehash", filehash},
        {uploadID, "filesize", to_string(filesize)},
        {uploadID, "chunksize", to_string(chunksize)},
        {uploadID, "chunkcount", to_string(chunkcount)}
    };
    for(size_t i=0; i<vec.size(); ++i){
        WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
            "redis://127.0.0.1:6379", 0, nullptr);
        redisTask->get_req()->set_request("HSET", vec[i]);
        series->push_back(redisTask);
    }
    
    WFRedisTask *redisTask2 = WFTaskFactory::create_redis_task(
        "redis://127.0.0.1:6379", 0, 
        bind(&Sharding::loginCallback2, this, _1, resp));
    redisTask2->get_req()->set_request("HGETALL", {uploadID});
    series->push_back(redisTask2);
}

void Sharding::loginCallback2(WFRedisTask* redisTask2, wfrest::HttpResp* resp){
    cout << "11";
    protocol::RedisResponse *redisResp = redisTask2->get_resp();
    protocol::RedisValue value;
    redisResp->get_result(value);


    cout << value.arr_at(0).string_value();
    cout << "22";

    resp->String(value.arr_at(1).string_value());
    
}

int main()
{
    Sharding sharding(1);
    sharding.load();
    sharding.start(1234);
}
