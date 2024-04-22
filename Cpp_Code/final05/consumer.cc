#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>
#include <unistd.h>
struct RabbitMQInfo {
    std::string rabbitUrl = "amqp://guest:guest@127.0.0.1:5672";
    std::string exchange = "exchange_test";
    std::string queue = "queue1";
    std::string routingKey = "key1";
};

int main( ) {
    RabbitMQInfo mqinfo;
    // 建立一个channel
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create( ); // 取出消息
    channel->BasicConsume(mqinfo.queue, "", true, true, true, 2);        // 创建一个envelope对象
    AmqpClient::Envelope::ptr_t envelope;
    while (1) {
        bool flag = channel->BasicConsumeMessage(envelope, 10000);
        if (flag) {
            fprintf(stderr, "Data! msg = %s\n", envelope->Message( )->Body( ).c_str( ));
        } else {
            fprintf(stderr, "No Data!\n");
        }
        sleep(10);
    }
}
