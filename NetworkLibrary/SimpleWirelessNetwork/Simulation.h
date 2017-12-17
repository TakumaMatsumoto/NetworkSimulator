#pragma once
#include <unordered_map>
#include "ISimulation.h"
#include "SWNConfig.h"

namespace sim {
	namespace swn {
		class Simulation : public ISimulation {
			const swn::Config m_conf;
		public:
			Simulation(const std::unordered_map<std::string, std::string>& param_map) : m_conf(Config::createFromMap(param_map)) {

			}
			std::unordered_map<std::string, std::string> run() override;
		};
	}
}