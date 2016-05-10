#include "medida/reporting/udp_client.h"
#include "medida/reporting/util.h"

#include <sstream>

#ifdef _WIN32
#	include <WinSock2.h>
#	include <WS2tcpip.h>
#	pragma comment(lib, "WS2_32.lib")

#else
#	include <netdb.h>
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <sys/utsname.h>
#endif // _WIN32

namespace medida {
namespace reporting {

class UDPClient::Impl {
 public:
  Impl(UDPClient& self, const std::string& hostname, std::uint16_t port);
  ~Impl();
  int Send(const std::string& msg);
  std::string UName();

 private:
  UDPClient& self_;
  std::string uname_;
  struct addrinfo* addrinfo_;
  int socket_;
};

UDPClient::UDPClient(const std::string& hostname, std::uint16_t port)
    : impl_{new UDPClient::Impl{*this, hostname, port}} {}

UDPClient::~UDPClient() {}


int UDPClient::Send(const std::string& msg) { return impl_->Send(msg); }

std::string UDPClient::UName() { return impl_->UName(); }


// === Implementation ===

UDPClient::Impl::Impl(UDPClient& self, const std::string& hostname,
                      std::uint16_t port)
    : self_(self) {

#ifdef _WIN32
  // --- WSAStartup ---
  MyWSAStartup();
  // Get hostname
  uname_ = GetHostName();
#else
  utsname name;
  uname_ = {uname(&name) ? "localhost" : name.nodename};
#endif

  // Get addrinfo
  auto port_str = std::to_string(port);
  auto err = getaddrinfo(hostname.c_str(), port_str.c_str(), NULL, &addrinfo_);
  if (err != 0) {
    throw std::invalid_argument("getaddrinfo error: " +
                                std::string(gai_strerrorA(err)));
  }

  // Get socket
  socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_ == -1) {
    std::stringstream ss;
    char strerr[256];
    strerror_s(strerr, errno);
    ss << "Socket error (" << errno << "): " << strerr;

    throw std::runtime_error(ss.str());
  }
}

UDPClient::Impl::~Impl() {
	freeaddrinfo(addrinfo_);
#ifdef _WIN32
  // --- WSACleanup ---
  WSACleanup();
#endif  // _WIN32
}

int UDPClient::Impl::Send(const std::string& msg) {
	return sendto(socket_, msg.c_str(), msg.length(), 0, addrinfo_->ai_addr, addrinfo_->ai_addrlen);
}

std::string UDPClient::Impl::UName() {
	return uname_;
}

}
}