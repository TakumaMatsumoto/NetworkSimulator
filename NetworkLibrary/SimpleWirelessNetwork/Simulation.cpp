#include "Simulation.h"
#include "Table.h"
#include "Result.h"
using namespace sim::swn;

std::unordered_map<std::string, std::string> Simulation::run() {
	Result result;
	return result.toMap();
}