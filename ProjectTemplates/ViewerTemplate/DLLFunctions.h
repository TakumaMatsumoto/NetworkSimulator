#pragma once
#include <unordered_map>
#include <string>
#include "IViewer.h"

sim::IViewer* CreateInstance(const std::unordered_map<std::string, std::string>& param_map);