#include "CloudiskServer.h"
#include <iostream>
#include <string>

using namespace AlibabaCloud::OSS;

int main( ) {
    OSSInfo ossInfo;
    RabbitMQInfo mqInfo;

#include "/Users/Onlyifan/.ssh/AliOSSKey"


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
