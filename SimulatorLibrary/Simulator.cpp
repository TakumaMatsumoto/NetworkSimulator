#include <Windows.h>
#include <memory>
#include <functional>
#include <algorithm>
#include "Simulator.h"
using namespace sim;
using CFUNC = sim::IRunnable*(*)(const table::RowHeader& row_header, const table::Table& tbl);
using RFUNC = void(*)(const std::unordered_map<std::string, std::string>& result);

void Simulator::run() {
	const HMODULE sim_lib_handle = LoadLibraryA(m_conf.m_simulation_dll_filename.c_str());
	const std::vector<HMODULE> result_lib_handlers = [](const Config& conf) {
		std::vector<HMODULE> ret;
		for (const auto& result_output_dll_filename : conf.m_output_dlls_filename)
		{
			ret.push_back(LoadLibraryA(result_output_dll_filename.c_str()));
		}
		return ret;
	}(m_conf);
	if (sim_lib_handle == NULL || std::any_of(result_lib_handlers.begin(), result_lib_handlers.end(), [](const HMODULE& handle) { return handle == NULL; })) {
		MessageBoxA(NULL, "指定したdllファイルが見つかりませんでした", "error", MB_ICONERROR);
		return;
	}

	const CFUNC CreateSimulationInstance = reinterpret_cast<CFUNC>(GetProcAddress(sim_lib_handle, "CreateSimulatorInstance"));
	const std::vector<RFUNC> OutputResultFunctions = [](const std::vector<HMODULE>& result_lib_handlers) {
		std::vector<RFUNC> ret;
		for (const auto& result_handle_module : result_lib_handlers)
		{
			ret.push_back(reinterpret_cast<RFUNC>(GetProcAddress(result_handle_module, "OutputResult")));
		}
		return ret;
	}(result_lib_handlers);
	if (CreateSimulationInstance == NULL || std::any_of(OutputResultFunctions.begin(), OutputResultFunctions.end(), [](const RFUNC& func) { return func == NULL; })) {
		MessageBoxA(NULL, "関数の呼び出しに失敗しました", "error", MB_ICONERROR);
		return;
	}

	const auto row_heads = m_param_table.getRowHeaders();
	for (const auto& row_head : row_heads)
	{
		const auto simulation = std::unique_ptr<sim::IRunnable>(CreateSimulationInstance(row_head, m_param_table));
		simulation->run();
		for (const auto& OutputResult : OutputResultFunctions)
		{
			OutputResult(simulation->toMap());
		}
	}

	FreeLibrary(sim_lib_handle);
	for (const auto& result_lib_handle : result_lib_handlers)
	{
		FreeLibrary(result_lib_handle);
	}
}