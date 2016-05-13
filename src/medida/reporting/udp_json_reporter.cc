#include "medida/reporting/udp_json_reporter.h"
#include "medida/reporting/udp_client.h"
#include "medida/reporting/util.h"

namespace medida {
namespace reporting {
class UDPJsonReporter::Impl {
 public:
  Impl(UDPJsonReporter& self, const std::string& hostname, std::uint16_t port);
  ~Impl();
  void Run();

 private:
	 UDPClient client_;
	 UDPJsonReporter& self_;
};

UDPJsonReporter::UDPJsonReporter(MetricsRegistry& registry,
                                 const std::string& hostname,
                                 std::uint16_t port)
    : AbstractPollingReporter(),
      JsonReporter(registry),
      impl_{new UDPJsonReporter::Impl{*this, hostname, port}} {};

UDPJsonReporter::~UDPJsonReporter() {}

void UDPJsonReporter::Run() { impl_->Run(); }

// === Implementation ===

UDPJsonReporter::Impl::Impl(UDPJsonReporter& self, const std::string& hostname, std::uint16_t port)
    : self_(self),
	  client_(hostname, port)
	{}

UDPJsonReporter::Impl::~Impl(){}

void UDPJsonReporter::Impl::Run() {
	auto json = self_.Report();
	client_.Send(json);
}

}
}