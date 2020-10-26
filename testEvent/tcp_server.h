#ifndef MINDSPORE_CCSRC_PS_COMM_TCP_SERVER_H_
#define MINDSPORE_CCSRC_PS_COMM_TCP_SERVER_H_

#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <stdint.h>

// #include "utils/log_adapter.h"
#include "tcp_message_handler.h"



class TcpServer;
class TcpConnection {
 public:
  TcpConnection() : buffer_event_(nullptr), fd_(0), server_(nullptr) {}
  virtual ~TcpConnection() = default;

  virtual void InitConnection(const evutil_socket_t &fd, const struct bufferevent *bev, const TcpServer *server);
  void SendMessage(const void *buffer, size_t num) const;
  virtual void OnReadHandler(const void *buffer, size_t numBytes);
  TcpServer *GetServer() const;
  evutil_socket_t GetFd() const;

 protected:
  TcpMessageHandler tcp_message_handler_;
  struct bufferevent *buffer_event_;
  evutil_socket_t fd_;
  TcpServer *server_;
};

using OnServerReceiveMessage =
  std::function<void(const TcpServer &tcp_server, const TcpConnection &conn, const void *buffer, size_t num)>;

class TcpServer {
 public:
  using OnConnected = std::function<void(const TcpServer *, const TcpConnection *)>;
  using OnDisconnected = std::function<void(const TcpServer *, const TcpConnection *)>;
  using OnAccepted = std::function<const TcpConnection *(const TcpServer *)>;

  explicit TcpServer(std::string address, std::uint16_t port);
  virtual ~TcpServer();

  void SetServerCallback(const OnConnected &client_conn, const OnDisconnected &client_disconn,
                         const OnAccepted &client_accept);
  void InitServer();
  void Start();
  void Stop();
  void SendToAllClients(const char *data, size_t len);
  void AddConnection(const evutil_socket_t &fd, const TcpConnection *connection);
  void RemoveConnection(const evutil_socket_t &fd);
  void ReceiveMessage(const OnServerReceiveMessage &cb);
  static void SendMessage(const TcpConnection &conn, const void *data, size_t num);
  void SendMessage(const void *data, size_t num);
  OnServerReceiveMessage GetServerReceiveMessage() const;

 protected:
  static void ListenerCallback(struct evconnlistener *listener, evutil_socket_t socket, struct sockaddr *saddr,
                               int socklen, void *server);
  static void SignalCallback(evutil_socket_t sig, std::int16_t events, void *server);
  static void ReadCallback(struct bufferevent *, void *connection);
  static void EventCallback(struct bufferevent *, std::int16_t events, void *server);
  virtual TcpConnection *onCreateConnection();

 private:
  struct event_base *base_;
  struct event *signal_event_;
  struct evconnlistener *listener_;
  std::string server_address_;
  std::uint16_t server_port_;

  std::map<evutil_socket_t, const TcpConnection *> connections_;
  OnConnected client_connection_;
  OnDisconnected client_disconnection_;
  OnAccepted client_accept_;
  std::recursive_mutex connection_mutex_;
  OnServerReceiveMessage message_callback_;
};

#endif  // MINDSPORE_CCSRC_PS_COMM_TCP_SERVER_H_