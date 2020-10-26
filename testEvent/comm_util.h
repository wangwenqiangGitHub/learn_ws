#ifndef MINDSPORE_CCSRC_PS_COMM_COMM_UTIL_H_
#define MINDSPORE_CCSRC_PS_COMM_COMM_UTIL_H_

#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/keyvalq_struct.h>
#include <event2/listener.h>
#include <event2/util.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>
#include <utility>

// #include "utils/log_adapter.h"



class CommUtil {
 public:
  static bool CheckIpWithRegex(const std::string &ip);
  static void CheckIp(const std::string &ip);
};

#endif  // MINDSPORE_CCSRC_PS_COMM_COMM_UTIL_H_