#include "medida/reporting/udp_json_reporter.h"

#include <gtest/gtest.h>

#include "medida/metrics_registry.h"

using namespace medida;
using namespace medida::reporting;


TEST(UDPJsonReporterTest, single) {
  MetricsRegistry registry{};
  auto& counter = registry.NewCounter({"test", "console_reporter", "counter"});
  auto& histogram =
      registry.NewHistogram({"test", "console_reporter", "histogram"});
  auto& meter =
      registry.NewMeter({"test", "console_reporter", "meter"}, "cycles");
  auto& timer = registry.NewTimer({"test", "console_reporter", "timer"});

  UDPJsonReporter reporter{ registry , "127.0.0.1", 5044 };

  counter.inc();
  for (auto i = 1; i <= 1000; i++) {
    auto t = timer.TimeScope();
    histogram.Update(i);
    meter.Mark();
  }


  reporter.Start();

}


TEST(UDPJsonReporterTest, multi) {
  MetricsRegistry registry1 {};
  MetricsRegistry registry2 {};
  auto& counter1 = registry1.NewCounter({"test", "console_reporter", "counter"});
  auto& counter2 = registry2.NewCounter({"test", "console_reporter", "counter"});

  UDPJsonReporter reporter1{ registry1 , "127.0.0.1", 5044 };
  UDPJsonReporter reporter2{ registry2 , "127.0.0.1", 5044 };

  counter1.set_count(1);
  counter2.set_count(2);


  reporter1.Start();
  std::this_thread::sleep_for(std::chrono::seconds(20));

  reporter2.Start();
  std::this_thread::sleep_for(std::chrono::seconds(10));
  reporter2.Shutdown();
  //while (true) {
  //  std::this_thread::sleep_for(std::chrono::seconds(10));
  //}
  
}