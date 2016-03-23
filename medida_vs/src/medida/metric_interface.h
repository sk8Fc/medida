//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_METRIC_INTERFACE_H_
#define MEDIDA_METRIC_INTERFACE_H_

#include "medida/medida_dll.h"
#include "medida/metric_processor.h"

namespace medida {

class DLLEXPORT MetricInterface {
public:
  virtual ~MetricInterface() {};
  virtual void Process(MetricProcessor& processor) = 0;
};

} // namespace medida

#endif // MEDIDA_METRIC_INTERFACE_H_
