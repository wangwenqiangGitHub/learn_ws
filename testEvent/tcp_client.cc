#include "tcp_client.h"

#include <arpa/inet.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/buffer_compat.h>
#include <event2/event.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <string>
#include <string.h>

#include "comm_util.h"



TcpClient::TcpClient(std::string address, std::uint16_t port)
    : event_base_(nullptr),
      event_timeout_(nullptr),
      buffer_event_(nullptr),
      server_address_(std::move(address)),
      server_port_(port) {
  message_handler_.SetCallback([this](const void *buf, size_t num) {
    if (buf == nullptr) {
      if (disconnected_callback_) disconnected_callback_(*this, 200);
      Stop();
    }
    if (message_callback_) message_callback_(*this, buf, num);
  });
}

TcpClient::~TcpClient() { Stop(); }

std::string TcpClient::GetServerAddress() const { return server_address_; }

void TcpClient::SetCallback(const OnConnected &conn, const OnDisconnected &disconn, const OnRead &read,
                            const OnTimeout &timeout) {
  connected_callback_ = conn;
  disconnected_callback_ = disconn;
  read_callback_ = read;
  timeout_callback_ = timeout;
}

void TcpClient::InitTcpClient() {
  if (buffer_event_) {
    return;
  }
  CommUtil::CheckIp(server_address_);

  event_base_ = event_base_new();
//   MS_EXCEPTION_IF_NULL(event_base_);

  sockaddr_in sin{};
  // if (memset_s(&sin, sizeof(sin), 0, sizeof(sin)) != 0) {
    
    // MS_LOG(EXCEPTION) << "Initialize sockaddr_in failed!";
  // }
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(server_address_.c_str());
  sin.sin_port = htons(server_port_);

  buffer_event_ = bufferevent_socket_new(event_base_, -1, BEV_OPT_CLOSE_ON_FREE);
//   MS_EXCEPTION_IF_NULL(buffer_event_);

  bufferevent_setcb(buffer_event_, ReadCallback, nullptr, EventCallback, this);
  if (bufferevent_enable(buffer_event_, EV_READ | EV_WRITE) == -1) {
    // MS_LOG(EXCEPTION) << "buffer event enable read and write failed!";
  }

  int result_code = bufferevent_socket_connect(buffer_event_, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin));
  if (result_code < 0) {
    // MS_LOG(EXCEPTION) << "Connect server ip:" << server_address_ << " and port: " << server_port_ << " is failed!";
  }
}

void TcpClient::StartWithDelay(int seconds) {
  if (buffer_event_) {
    return;
  }

  event_base_ = event_base_new();

  timeval timeout_value{};
  timeout_value.tv_sec = seconds;
  timeout_value.tv_usec = 0;

  event_timeout_ = evtimer_new(event_base_, TimeoutCallback, this);
  if (evtimer_add(event_timeout_, &timeout_value) == -1) {
    // MS_LOG(EXCEPTION) << "event timeout failed!";
  }
}

void TcpClient::Stop() {
  if (buffer_event_) {
    bufferevent_free(buffer_event_);
    buffer_event_ = nullptr;
  }

  if (event_timeout_) {
    event_free(event_timeout_);
    event_timeout_ = nullptr;
  }

  if (event_base_) {
    event_base_free(event_base_);
    event_base_ = nullptr;
  }
}

void TcpClient::SetTcpNoDelay(const evutil_socket_t &fd) {
  const int one = 1;
  int ret = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(int));
  if (ret < 0) {
    // MS_LOG(EXCEPTION) << "Set socket no delay failed!";
  }
}

void TcpClient::TimeoutCallback(evutil_socket_t, std::int16_t, void *arg) {
//   MS_EXCEPTION_IF_NULL(arg);
  auto tcp_client = reinterpret_cast<TcpClient *>(arg);
  tcp_client->InitTcpClient();
}

void TcpClient::ReadCallback(struct bufferevent *bev, void *ctx) {
//   MS_EXCEPTION_IF_NULL(bev);
//   MS_EXCEPTION_IF_NULL(ctx);
  auto tcp_client = reinterpret_cast<TcpClient *>(ctx);
  struct evbuffer *input = bufferevent_get_input(const_cast<struct bufferevent *>(bev));
//   MS_EXCEPTION_IF_NULL(input);

  char read_buffer[4096];
  int read = 0;

  while ((read = EVBUFFER_LENGTH(input)) > 0) {
    if (evbuffer_remove(input, &read_buffer, sizeof(read_buffer)) == -1) {
    //   MS_LOG(EXCEPTION) << "Can not drain data from the event buffer!";
    }
    tcp_client->OnReadHandler(read_buffer, read);
  }
}

void TcpClient::OnReadHandler(const void *buf, size_t num) {
//   MS_EXCEPTION_IF_NULL(buf);
  if (read_callback_) {
    read_callback_(*this, buf, num);
  }
  message_handler_.ReceiveMessage(buf, num);
}

void TcpClient::EventCallback(struct bufferevent *bev, std::int16_t events, void *ptr) {
//   MS_EXCEPTION_IF_NULL(bev);
//   MS_EXCEPTION_IF_NULL(ptr);
  auto tcp_client = reinterpret_cast<TcpClient *>(ptr);
  if (events & BEV_EVENT_CONNECTED) {
    // Connected
    if (tcp_client->connected_callback_) {
      tcp_client->connected_callback_(*tcp_client);
    }
    evutil_socket_t fd = bufferevent_getfd(const_cast<struct bufferevent *>(bev));
    SetTcpNoDelay(fd);
    // MS_LOG(INFO) << "Client connected!";
  } else if (events & BEV_EVENT_ERROR) {
    // MS_LOG(ERROR) << "Client connected error!";
    if (tcp_client->disconnected_callback_) {
      tcp_client->disconnected_callback_(*tcp_client, errno);
    }
  } else if (events & BEV_EVENT_EOF) {
    // MS_LOG(ERROR) << "Client connected end of file";
    if (tcp_client->disconnected_callback_) {
      tcp_client->disconnected_callback_(*tcp_client, 0);
    }
  }
}

void TcpClient::Start() {
//   MS_EXCEPTION_IF_NULL(event_base_);
  int ret = event_base_dispatch(event_base_);
  if (ret == 0) {
    // MS_LOG(INFO) << "Event base dispatch success!";
  } else if (ret == 1) {
    // MS_LOG(ERROR) << "Event base dispatch failed with no events pending or active!";
  } else if (ret == -1) {
    // MS_LOG(ERROR) << "Event base dispatch failed with error occurred!";
  } else {
    // MS_LOG(EXCEPTION) << "Event base dispatch with unexpect error code!";
  }
}

void TcpClient::ReceiveMessage(const OnMessage &cb) { message_callback_ = cb; }

void TcpClient::SendMessage(const void *buf, size_t num) const {
//   MS_EXCEPTION_IF_NULL(buffer_event_);
  if (evbuffer_add(bufferevent_get_output(buffer_event_), buf, num) == -1) {
//     MS_LOG(EXCEPTION) << "event buffer add failed!";
  }
}
