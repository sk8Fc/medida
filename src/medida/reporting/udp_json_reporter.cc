#include "medida/reporting/udp_json_reporter.h"
#include "medida/reporting/util.h"

namespace medida {
namespace reporting {
class UDPJsonReporter::Impl {
 public:
  Impl(UDPJsonReporter& self);
  ~Impl();
  void Run();

 private:
	 UDPJsonReporter& self_;
};

UDPJsonReporter::UDPJsonReporter(MetricsRegistry& registry,
                                 const std::string& hostname,
                                 std::uint16_t port)
    : AbstractPollingReporter(),
      JsonReporter(registry),
      UDPClient(hostname, port),
      impl_{new UDPJsonReporter::Impl{*this}} {};

UDPJsonReporter::~UDPJsonReporter() {}

void UDPJsonReporter::Run() { impl_->Run(); }

// === Implementation ===

UDPJsonReporter::Impl::Impl(UDPJsonReporter& self)
    : self_(self) {}

UDPJsonReporter::Impl::~Impl(){}

void UDPJsonReporter::Impl::Run() {
	auto json = self_.Report();
	self_.Send(json);
}

}
}