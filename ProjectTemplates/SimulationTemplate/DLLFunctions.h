#pragma once
#include "IRunnable.h"
#include "Table.h"

sim::IRunnable* CreateSimulationInstance(const std::unordered_map<std::string, std::string>& param_map);