#include "../CloudiskServer.h"
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <sstream>
#include <string>
#include <unistd.h>


using namespace AlibabaCloud::OSS;

int main( ) {
    OSSInfo ossInfo;
#include "/Users/Onlyifan/.ssh/AliOSSKey"

    RabbitMQInfo mqInfo;
    mqInfo.RoutingKey = "oss";
    mqInfo.RabbitURL = "amqp://guest:guest@127.0.0.1:5672";
    mqInfo.Exchange = "uploadserver.trans";
    mqInfo.Queue = "uploadserver.trans.oss";


    InitializeSdk( );


    // 配置客户端的属性
    ClientConfiguration conf;
    conf.maxConnections = 30;
    conf.requestTimeoutMs = 3000;
    conf.connectTimeoutMs = 3000;


    OssClient client(ossInfo.EndPoint, ossInfo.AccessKeyID, ossInfo.AccessKeySecret, conf);

    // 建立一个channel
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create( ); // 取出消息
    channel->BasicConsume(mqInfo.Queue);                                 // 创建一个envelope对象
    AmqpClient::Envelope::ptr_t envelope;
    for (;;) {
        bool flag = channel->BasicConsumeMessage(envelope, 10000);
        if (flag) {
            fprintf(stderr, "Data! msg = %s\n", envelope->Message( )->Body( ).c_str( ));
            std::istringstream iss(envelope->Message( )->Body( ));

            std::string fileHash;
            std::string fileName;

            std::getline(iss, fileHash);
            std::getline(iss, fileName);

            std::cerr << fileHash << "\n"
                      << fileName << "\n";

            PutObjectOutcome outcome = client.PutObject(ossInfo.Bucket, fileHash, "../" + fileName);

            if (!outcome.isSuccess( )) {
                std::cerr << "code = " << outcome.error( ).Code( )
                          << ",message = " << outcome.error( ).Message( ) << "\n";
            }

        } else {
            fprintf(stderr, "No Data!\n");
        }
    }
}
