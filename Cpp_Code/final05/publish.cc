#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>
struct RabbitMQInfo {
    std::string rabbitUrl = "amqp://guest:guest@127.0.0.1:5672";
    std::string exchange = "exchange_test";
    std::string queue = "queue1";
    std::string routingKey = "key1";
};

int main( ) {
    RabbitMQInfo mqinfo;
    // 创建一个channel
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create( ); // pause();
    // 创建一个消息
    AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create("Hello");
    // 把消息发布给交换器
    channel->BasicPublish(mqinfo.exchange, mqinfo.routingKey, message);
}