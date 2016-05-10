//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/reporting/util.h"

#include <cstdint>

#ifdef _WIN32
#	include <WinSock2.h>
#	include <WS2tcpip.h>
#	pragma comment(lib, "WS2_32.lib")
#endif

namespace medida {
namespace reporting {
static const std::int64_t NS_PER_US = 1000, 
                          NS_PER_MS = 1000 * NS_PER_US,
                          NS_PER_SECOND = 1000 * NS_PER_MS,
                          NS_PER_MIN = 60 * NS_PER_SECOND,
                          NS_PER_HOUR = 60 * NS_PER_MIN,
                          NS_PER_DAY = 24 * NS_PER_HOUR;

std::string FormatRateUnit(const std::chrono::nanoseconds& rate_unit) {
  auto nanosecs = rate_unit.count();
  if (nanosecs >= NS_PER_DAY) {
    return "d";
  } else if (nanosecs >= NS_PER_HOUR) {
    return "h";
  } else if (nanosecs >= NS_PER_MIN) {
    return "m";
  } else if (nanosecs >= NS_PER_SECOND) {
    return "s";
  } else if (nanosecs >= NS_PER_MS) {
    return "ms";
  } else if (nanosecs >= NS_PER_US) {
    return "us";
  }
  return "ns";
}

#ifdef _WIN32
void MyWSAStartup() {
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  wVersionRequested = MAKEWORD(2, 0);
  err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    // WSAStartup failed with error
  }
}

std::string GetHostName() {
  char nameBuf[128] = {};
  std::string uname;

  if (gethostname(nameBuf, sizeof(nameBuf)) == 0) {
    uname = std::string(nameBuf);
  } else {
    uname = std::string("localhost");
  }

  return uname;
}

#endif // _WIN32

}  // namespace reporting
} // namespace medida