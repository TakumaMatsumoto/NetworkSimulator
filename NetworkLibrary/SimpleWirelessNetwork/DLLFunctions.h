#pragma once
#include "ISimulation.h"

sim::ISimulation* CreateInstance(const std::unordered_map<std::string, std::string>& param_map);