#include <iostream>
#include <string>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>


using std::cout;
using std::string;

void redisCallback(WFRedisTask *redisTask) {
    protocol::RedisResponse *resp = redisTask->get_resp( );
    protocol::RedisValue value;
    resp->get_result(value);

    if (value.is_string( )) {
        cout << "resp = " << value.string_value( ) << "\n";
    }
}

void getBody(WFHttpTask *httpTask) {
    protocol::HttpResponse *resp = httpTask->get_resp( );

    int state = httpTask->get_state( );
    int error = httpTask->get_error( );

    switch (state) {
    case WFT_STATE_SYS_ERROR:
        cout << "system error: " << strerror(error) << "\n";
        exit(-1);
    case WFT_STATE_DNS_ERROR:
        cout << "dns error " << gai_strerror(error) << "\n";
        exit(-1);
    case WFT_STATE_SUCCESS:
        char *body;
        size_t bodySize;
        resp->get_parsed_body(((const void **)&body), &bodySize);
        printf("%s\n", body);
        series_of(httpTask)->set_context(body);

        WFRedisTask *redisTask =
            WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
        series_of(httpTask)->push_back(redisTask);
        
        protocol::RedisRequest *reqRedis = redisTask->get_req( );
        reqRedis->set_request("SET",
                              { "taobao", (const char *)series_of(redisTask)->get_context( ) });
    }
}


int main( ) {
    WFHttpTask *httpTask = WFTaskFactory::create_http_task("https://www.taobao.com", 0, 0, getBody);
    // protocol::HttpRequest *reqHttp = httpTask->get_req( );
    // reqHttp->add_header_pair("Accept", "*/*");
    httpTask->start( );
    sleep(1);
}
