// #include
#include "tcp_client.h"
#include "tcp_server.h"
// #include "common/common_test.h"

#include <thread>


int main()
{
    TcpClient *client_;
    client_ = new TcpClient("127.0.0.1", 9000);
    client_->ReceiveMessage(
        [](const TcpClient &client, const void *buffer, size_t num) { client.SendMessage(buffer, num); });
    
    return 0;
}