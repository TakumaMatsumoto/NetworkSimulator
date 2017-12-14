#include <Windows.h>
#include <memory>
#include <functional>
#include <algorithm>
#include "Simulator.h"
using namespace sim::msw;

void Simulator::Simulation::init() {
	m_lib_handle = LoadLibraryA(m_dll_filename.c_str());
	if (m_lib_handle == NULL) {
		throw std::exception("DLL file for simulation not found");
	}
	m_func = reinterpret_cast<CREATE_SIMULATION_INSTANCE_FUNC>(GetProcAddress(m_lib_handle, "CreateSimulationInstance"));
	if (m_func == NULL) {
		throw std::exception("CreateSimulationInstance function not found");
	}
}

void Simulator::Simulation::terminate() {
	if(m_lib_handle != NULL) FreeLibrary(m_lib_handle);
}

void Simulator::Viewer::init() {
	m_lib_handle = LoadLibraryA(m_dll_filename.c_str());
	if (m_lib_handle == NULL) {
		throw std::exception("DLL file for viewer not found");
	}
	m_simulator_begin_func	 = reinterpret_cast<ON_SIMULATOR_BEGIN_FUNC>	(GetProcAddress(m_lib_handle, "OnSimulatorBegin"));
	m_simulations_begin_func = reinterpret_cast<ON_SIMULATIONS_BEGIN_FUNC>	(GetProcAddress(m_lib_handle, "OnSimulationsBegin"));
	m_simulation_begin_func  = reinterpret_cast<ON_SIMULATION_BEGIN_FUNC>	(GetProcAddress(m_lib_handle, "OnSimulationBegin"));
	m_simulation_end_func	 = reinterpret_cast<ON_SIMULATION_END_FUNC>		(GetProcAddress(m_lib_handle, "OnSimulationEnd"));
	m_simulations_end_func	 = reinterpret_cast<ON_SIMULATIONS_END_FUNC>	(GetProcAddress(m_lib_handle, "OnSimulationsEnd"));
	m_simulator_end_func	 = reinterpret_cast<ON_SIMULATOR_END_FUNC>		(GetProcAddress(m_lib_handle, "OnSimulatorEnd"));
	if (m_simulator_begin_func	 == NULL || 
		m_simulations_begin_func == NULL || 
		m_simulation_begin_func  == NULL || 
		m_simulation_end_func	 == NULL ||
		m_simulations_end_func	 == NULL ||
		m_simulator_end_func	 == NULL) {
		throw std::exception("Any function in viewer dll not found");
	}
}

void Simulator::Viewer::terminate() {
	if (m_lib_handle != NULL) FreeLibrary(m_lib_handle);
}

void Simulator::Viewers::init() {
	for (auto& viewer : m_viewers)
	{
		viewer.init();
	}
}

void Simulator::Viewers::terminate() {
	for (auto& viewer : m_viewers)
	{
		viewer.terminate();
	}
}

void Simulator::run() {
	Simulation sim(m_conf.m_simulation_dll_filename);
	Viewers viewers(m_conf);
	try {
		// シミュレータ、ビューアの初期化処理
		sim.init();
		viewers.init();

		// シミュレータを動かす
		viewers.onSimulatorBegin(m_conf);
		// パラメータ表から一行ずつパラメータを取り出す
		for (const auto& row_head : m_param_table.getRowHeaders())
		{
			const auto param = m_param_table.getRow(row_head);
			viewers.onSimulationsBegin(row_head, param);
			std::vector<std::unordered_map<std::string, std::string>> results(m_conf.m_number_of_trials);
			// 試行回数分、シミュレーションを行い、結果を出力する
			for (size_t i = 0; i < m_conf.m_number_of_trials; i++)
			{
				viewers.onSimulationBegin(i);
				const auto result = std::unique_ptr<sim::IRunnable>(sim.createInstance(param))->run();
				results.at(i) = result;
				viewers.onSimulationEnd(result);
			}
			viewers.onSimulationsEnd(results);
		}
		viewers.onSimulatorEnd();
	}
	catch(const std::exception& ex){
		MessageBoxA(NULL, ex.what(), "error", MB_OK | MB_ICONERROR);
	}
	sim.terminate();
	viewers.terminate();

}