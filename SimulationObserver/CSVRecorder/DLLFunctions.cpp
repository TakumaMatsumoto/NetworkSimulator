#include <iostream>
#include "DLLFunctions.h"
#include "CSVRecorder.h"
using namespace std;

sim::ISimulationObserver* CreateInstance(const std::unordered_map<std::string, std::string>& param_map) {
	return new sim::observer::CSVRecorder();
}