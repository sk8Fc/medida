#ifndef MEDIDA_REPORTING_UDP_CLIENT_H_
#define MEDIDA_REPORTING_UDP_CLIENT_H_

#include <cstdint>
#include <string>
#include <mutex>

#include "medida/medida_dll.h"

namespace medida {
namespace reporting {

class DLLEXPORT UDPClient {
 public:
  UDPClient(const std::string& hostname, std::uint16_t port);
  virtual ~UDPClient();
  virtual int Send(const std::string& msg);
  virtual std::string UName();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}
}

#endif // !MEDIDA_REPORTING_UDP_CLIENT_H_
