//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/reporting/console_reporter.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace medida {
namespace reporting {

ConsoleReporter::ConsoleReporter(MetricsRegistry &registry, std::ostream& out)
    : AbstractPollingReporter(registry),
      out_ (out) {
}


ConsoleReporter::~ConsoleReporter() {
}


void ConsoleReporter::Run() {
  for (auto& kv : registry_.GetAllMetrics()) {
    auto name = kv.first;
    auto metric = kv.second;
    out_ << name.ToString() << ":" << std::endl;
    metric->Process(*this);
  }
  out_ << std::endl;
}


void ConsoleReporter::Process(Counter& counter) {
  out_ << "  count = " << counter.count() << std::endl;
}


void ConsoleReporter::Process(Meter& meter) {
  auto event_type = meter.event_type();
  auto unit = FormatRateUnit(meter.rate_unit());
  out_ << "           count = " << meter.count() << std::endl
       << "       mean rate = " << meter.mean_rate() << " " << event_type << "/" << unit << std::endl
       << "   1-minute rate = " << meter.one_minute_rate() << " " << event_type << "/" << unit << std::endl
       << "   5-minute rate = " << meter.five_minute_rate() << " " << event_type << "/" << unit << std::endl
       << "  15-minute rate = " << meter.fifteen_minute_rate() << " " << event_type << "/" << unit << std::endl;
}


void ConsoleReporter::Process(Histogram& histogram) {
  auto snapshot = histogram.GetSnapshot();
  out_ << "             min = " << histogram.min() << std::endl
       << "             max = " << histogram.max() << std::endl
       << "            mean = " << histogram.mean() << std::endl
       << "          stddev = " << histogram.std_dev() << std::endl
       << "          median = " << snapshot.getMedian() << std::endl
       << "             75% = " << snapshot.get75thPercentile() << std::endl
       << "             95% = " << snapshot.get95thPercentile() << std::endl
       << "             98% = " << snapshot.get98thPercentile() << std::endl
       << "             99% = " << snapshot.get99thPercentile() << std::endl
       << "           99.9% = " << snapshot.get999thPercentile() << std::endl;
}


void ConsoleReporter::Process(Timer& timer) {
  auto snapshot = timer.GetSnapshot();
  auto unit = FormatRateUnit(timer.duration_unit());
  out_ << "             min = " << timer.min() << unit << std::endl
       << "             max = " << timer.max() << unit << std::endl
       << "            mean = " << timer.mean() << unit << std::endl
       << "          stddev = " << timer.std_dev() << unit << std::endl
       << "          median = " << snapshot.getMedian() << unit << std::endl
       << "             75% = " << snapshot.get75thPercentile() << unit << std::endl
       << "             95% = " << snapshot.get95thPercentile() << unit << std::endl
       << "             98% = " << snapshot.get98thPercentile() << unit << std::endl
       << "             99% = " << snapshot.get99thPercentile() << unit << std::endl
       << "           99.9% = " << snapshot.get999thPercentile() << unit << std::endl;
}


std::string ConsoleReporter::FormatRateUnit(const std::chrono::nanoseconds& rate_unit) const {
  static auto one_day = std::chrono::nanoseconds(std::chrono::hours(24)).count();
  static auto one_hour = std::chrono::nanoseconds(std::chrono::hours(1)).count();
  static auto one_minute = std::chrono::nanoseconds(std::chrono::minutes(1)).count();
  static auto one_seconds = std::chrono::nanoseconds(std::chrono::seconds(1)).count();
  static auto one_millisecond = std::chrono::nanoseconds(std::chrono::milliseconds(1)).count();
  static auto one_microsecond = std::chrono::nanoseconds(std::chrono::microseconds(1)).count();
  auto unit_count = rate_unit.count();
  if (unit_count >= one_day ) {
    return "d";
  } else if (unit_count >= one_hour) {
    return "h";
  } else if (unit_count >= one_minute) {
    return "m";
  } else if (unit_count >= one_seconds) {
    return "s";
  } else if (unit_count >= one_millisecond) {
    return "ms";
  } else if (unit_count >= one_microsecond) {
    return "us";
  }
  return "ns";
}


} // namespace reporting
} // namespace medida