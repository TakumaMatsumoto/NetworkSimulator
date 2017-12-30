#include <iostream>
#include "DLLFunctions.h"
#include "CSVRecorder.h"
using namespace std;

sim::ISimulationObserver* CreateInstance(const sim::Parameter& param_map) {
	return new sim::observer::CSVRecorder(sim::observer::CSVRecorder::Config::createFromConfigFile());
}