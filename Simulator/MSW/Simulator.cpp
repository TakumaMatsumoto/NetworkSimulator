#include <Windows.h>
#include <memory>
#include <functional>
#include <algorithm>
#include "Simulator.h"
#include "SimulatorLibrary\Simulator.h"
#include <time.h>
using namespace sim::msw;

int Simulator::run() const {
	srand(static_cast<unsigned int>(time(NULL)));
	const auto env_factory = new sim::RunnableEnvironmentFactory(
		new DLLInstanceFactory<ISimulation>(m_conf.m_simulation_dll_filename),
		new DLLInstanceFactory<ISimulationObserver>(m_conf.m_observer_dll_filename));
	const sim::Simulator simulator(
		env_factory, 
		m_conf.m_sim_config,
		std::make_pair(0, -1),
		[](const std::exception& ex) {
		MessageBoxA(NULL, ex.what(), "error", MB_OK | MB_ICONERROR);
	});
	return simulator.run();
}
