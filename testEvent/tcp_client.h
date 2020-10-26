#ifndef MINDSPORE_CCSRC_PS_COMM_TCP_CLIENT_H_
#define MINDSPORE_CCSRC_PS_COMM_TCP_CLIENT_H_

#include "tcp_message_handler.h"

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <functional>
#include <string>


class TcpClient {
 public:
  using OnMessage = std::function<void(const TcpClient &, const void *, size_t)>;
  using OnConnected = std::function<void(const TcpClient &)>;
  using OnDisconnected = std::function<void(const TcpClient &, int)>;
  using OnRead = std::function<void(const TcpClient &, const void *, size_t)>;
  using OnTimeout = std::function<void(const TcpClient &)>;

  explicit TcpClient(std::string address, std::uint16_t port);
  virtual ~TcpClient();

  std::string GetServerAddress() const;
  void SetCallback(const OnConnected &conn, const OnDisconnected &disconn, const OnRead &read,
                   const OnTimeout &timeout);
  void InitTcpClient();
  void StartWithDelay(int seconds);
  void Stop();
  void ReceiveMessage(const OnMessage &cb);
  void SendMessage(const void *buf, size_t num) const;
  void Start();

 protected:
  static void SetTcpNoDelay(const evutil_socket_t &fd);
  static void TimeoutCallback(evutil_socket_t fd, std::int16_t what, void *arg);
  static void ReadCallback(struct bufferevent *bev, void *ctx);
  static void EventCallback(struct bufferevent *bev, std::int16_t events, void *ptr);
  virtual void OnReadHandler(const void *buf, size_t num);

 private:
  TcpMessageHandler message_handler_;
  OnMessage message_callback_;
  OnConnected connected_callback_;
  OnDisconnected disconnected_callback_;
  OnRead read_callback_;
  OnTimeout timeout_callback_;

  event_base *event_base_;
  event *event_timeout_;
  bufferevent *buffer_event_;

  std::string server_address_;
  std::uint16_t server_port_;
};

#endif  // MINDSPORE_CCSRC_PS_COMM_TCP_CLIENT_H_
