#pragma once
#include "IRunnable.h"
#include "Table.h"

sim::IRunnable* CreateSimulatorInstance(const std::unordered_map<std::string, std::string>& param_map);