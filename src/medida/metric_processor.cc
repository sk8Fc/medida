//
// Copyright (c) 2012 Daniel Lundin
//

#include "medida/metric_processor.h"

namespace medida {

    MetricProcessor::~MetricProcessor() {
    }

    void MetricProcessor::Process(Counter& counter) {
    }

    void MetricProcessor::Process(Histogram& histogram) {
    }

    void MetricProcessor::Process(Value &value) {
    }

    void MetricProcessor::Process(Meter& meter) {
    }

    void MetricProcessor::Process(Timer& timer) {
    }

    void MetricProcessor::Process(MetricInterface& metric) {
    }

} // namespace medida
