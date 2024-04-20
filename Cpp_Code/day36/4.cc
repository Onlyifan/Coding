#include <iostream>
#include <string>
#include <workflow/WFFacilities.h>


using std::cout;
using std::string;

void redisCallback(WFRedisTask *task) {
    protocol::RedisResponse *resp = task->get_resp( );
    protocol::RedisValue value;
    resp->get_result(value);

    if (value.is_nil( )) {
        std::vector<string> para;
        task->get_req( )->get_params(para);
        cout << "final result = " << para[0] << "\n";
        return;
    }

    if (value.is_string( )) {
        series_of(task)->set_context((void *)value.string_value( ).c_str( ));
        WFRedisTask *redisTask =
            WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
        redisTask->get_req( )->set_request("GET", { value.string_value( ) });
        cout << "result = " << value.string_value( ) << "\n";
        series_of(task)->push_back(redisTask);
    }
}

int main( ) {
    WFRedisTask *redisTask =
        WFTaskFactory::create_redis_task("redis://127.0.0.1:6379", 0, redisCallback);
    redisTask->get_req( )->set_request("GET", { "k1" });

    redisTask->start( );
    sleep(1);
};
