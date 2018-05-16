#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>

#include "types.h"
using FuncOnError = std::function<void(const std::string&)>;
using FuncOnVirtualKey = std::function<void(VirtualKey, int)>;
#endif // FUNCTIONS_H
