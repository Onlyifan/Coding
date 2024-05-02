#include "CloudiskServer.h"
#include <string>

using namespace AlibabaCloud::OSS;

int main( ) {
    OSSInfo ossInfo;
#include "/Users/Onlyifan/.ssh/AliOSSKey"


    RabbitMQInfo mqInfo;
    mqInfo.RoutingKey = "oss";
    mqInfo.RabbitURL = "amqp://guest:guest@127.0.0.1:5672";
    mqInfo.Exchange = "uploadserver.trans";
    mqInfo.Queue = "uploadserver.trans.oss";


    // 初始化网络资源
    InitializeSdk( );

    // 配置客户端的属性
    ClientConfiguration conf;
    conf.maxConnections = 30;
    conf.requestTimeoutMs = 3000;
    conf.connectTimeoutMs = 3000;

    CloudiskServer cloudiskServer(1, std::move(ossInfo), std::move(mqInfo), conf);
    cloudiskServer.loadModules( );
    cloudiskServer.start(1234);
    
    return 0;
}
