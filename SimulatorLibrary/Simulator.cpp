#include <Windows.h>
#include <memory>
#include "Simulator.h"
using namespace sim;

void Simulator::run() {
	HMODULE hModule = LoadLibraryA(m_conf.m_simulation_dll_filename.c_str());
	using FUNC = sim::IRunnable* (*)(const table::RowHeader& row_header, const table::Table& tbl);
	FUNC CreateSimulationInstance = (FUNC)GetProcAddress(hModule, "CreateSimulatorInstance");

	const auto row_heads = m_param_table.getRowHeaders();
	for (size_t i = 0, length = row_heads.size(); i < length; i++)
	{
		const auto simulation = std::make_unique<sim::IRunnable>(CreateSimulationInstance(row_heads[i], m_param_table));
		simulation->run();
		simulation->toMap();
	}
	FreeLibrary(hModule);
}