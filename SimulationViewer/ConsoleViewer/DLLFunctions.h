#pragma once
#include "ISimulationObserver.h"

sim::ISimulationObserver* CreateInstance(const std::unordered_map<std::string, std::string>& param_map);