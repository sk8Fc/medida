#ifndef MEDIDA_REPORTING_UDP_JSON_REPORTER_H_
#define MEDIDA_REPORTING_UDP_JSON_REPORTER_H_

#include "medida/reporting/abstract_polling_reporter.h"
#include "medida/reporting/json_reporter.h"
#include "medida/reporting/udp_client.h"

namespace medida {
namespace reporting {

class DLLEXPORT UDPJsonReporter : public JsonReporter,
                                  public AbstractPollingReporter,
								  public UDPClient{
 public:
  UDPJsonReporter(MetricsRegistry& registry,
                  const std::string& hostname = "127.0.0.1",
                  std::uint16_t port = 25826);
  virtual ~UDPJsonReporter();
  virtual void Run();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace reporting
} // namespace medida

#endif // !MEDIDA_REPORTING_UDP_JSON_REPORTER_H_
