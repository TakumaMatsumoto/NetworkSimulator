#include "DLLFunctions.h"
#include "Simulator.h"
using namespace sim::swn;

sim::IRunnable* CreateSimulatorInstance(const table::RowHeader& row_header, const table::Table& tbl) {
	return new Simulator();
}