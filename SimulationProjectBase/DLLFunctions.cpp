#include "DLLFunctions.h"
#include "Simulation.h"
using namespace sim::sample;

sim::IRunnable* CreateSimulatorInstance(const std::unordered_map<std::string, std::string>& param_map) {
	return new Simulation();
}