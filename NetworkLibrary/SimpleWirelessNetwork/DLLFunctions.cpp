#include "DLLFunctions.h"
#include "Simulation.h"
using namespace sim::swn;

sim::ISimulation* CreateInstance(const std::unordered_map<std::string, std::string>& param_map) {
	return new Simulation(param_map);
}