//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_SAMPLING_INTERFACE_H_
#define MEDIDA_SAMPLING_INTERFACE_H_

#include "medida/medida_dll.h"
#include "medida/stats/snapshot.h"

namespace medida {

class DLLEXPORT SamplingInterface {
public:
  enum SampleType { kUniform, kBiased };
  virtual ~SamplingInterface() {};
  virtual stats::Snapshot GetSnapshot() const = 0;
};

} // namespace medida

#endif // MEDIDA_SAMPLING_INTERFACE_H_
