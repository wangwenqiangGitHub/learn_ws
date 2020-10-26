#ifndef MINDSPORE_CCSRC_PS_COMM_TCP_MESSAGE_HANDLER_H_
#define MINDSPORE_CCSRC_PS_COMM_TCP_MESSAGE_HANDLER_H_

#include <functional>
#include <iostream>
#include <memory>

// #include "utils/log_adapter.h"
using messageReceive = std::function<void(const void *buffer, size_t len)>;

class TcpMessageHandler {
 public:
  TcpMessageHandler() = default;
  virtual ~TcpMessageHandler() = default;

  void SetCallback(messageReceive cb);
  void ReceiveMessage(const void *buffer, size_t num);

 private:
  messageReceive message_callback_;
};

#endif  // MINDSPORE_CCSRC_PS_COMM_TCP_MESSAGE_HANDLER_H_