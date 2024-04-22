#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;




int main( ) {
    auto channel = AmqpClient::Channel::Create();
    channel->BasicConsume()
    channel->BasicConsumeMessage();
    
}
