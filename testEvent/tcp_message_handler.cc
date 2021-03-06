#include "tcp_message_handler.h"
#include <iostream>
#include <utility>


void TcpMessageHandler::SetCallback(messageReceive message_receive) { message_callback_ = std::move(message_receive); }

void TcpMessageHandler::ReceiveMessage(const void *buffer, size_t num) {
//   MS_EXCEPTION_IF_NULL(buffer);

  if (message_callback_) {
    message_callback_(buffer, num);
  }
}
