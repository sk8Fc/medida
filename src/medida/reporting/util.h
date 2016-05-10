//
// Copyright (c) 2012 Daniel Lundin
//

#ifndef MEDIDA_REPORTING_UTIL_H_
#define MEDIDA_REPORTING_UTIL_H_

#include <chrono>
#include <string>


#include "medida/medida_dll.h"

namespace medida {
namespace reporting {

std::string FormatRateUnit(const std::chrono::nanoseconds& rate_unit);

#ifdef _WIN32
std::string GetHostName();

void MyWSAStartup();
#endif // _WIN32


} // namespace reporting
} // namespace medida

#endif // MEDIDA_REPORTING_UTIL_H_
