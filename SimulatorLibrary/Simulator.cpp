#include <Windows.h>
#include <memory>
#include <functional>
#include "Simulator.h"
using namespace sim;

void Simulator::run() {
	HMODULE sim_lib_handle_module = LoadLibraryA(m_conf.m_simulation_dll_filename.c_str());
	using CFUNC = sim::IRunnable*(*)(const table::RowHeader& row_header, const table::Table& tbl);
	auto CreateSimulationInstance = reinterpret_cast<CFUNC>(GetProcAddress(sim_lib_handle_module, "CreateSimulatorInstance"));

	std::vector<HMODULE> result_handle_modules;
	for (const auto& result_output_dll_filename : m_conf.m_output_dlls_filename)
	{
		result_handle_modules.push_back(LoadLibraryA(result_output_dll_filename.c_str()));
	}
	using RFUNC = void(*)(const std::unordered_map<std::string, std::string>& result);
	std::vector<RFUNC> result_output_functions;
	for (const auto& result_handle_module : result_handle_modules)
	{
		result_output_functions.push_back(reinterpret_cast<RFUNC>(GetProcAddress(result_handle_module, "OutputResult")));
	}
	const auto row_heads = m_param_table.getRowHeaders();
	for (const auto& row_head : row_heads)
	{
		const auto simulation = std::unique_ptr<sim::IRunnable>(CreateSimulationInstance(row_head, m_param_table));
		simulation->run();
		for (const auto& result_output_function : result_output_functions)
		{
			result_output_function(simulation->toMap());
		}
	}

	FreeLibrary(sim_lib_handle_module);
	for (const auto& result_handle_module : result_handle_modules)
	{
		FreeLibrary(result_handle_module);
	}
}