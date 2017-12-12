#pragma once
#include <unordered_map>
#include "IRunnable.h"

namespace sim {
	namespace swn {
		class Simulation : public IRunnable {
			
		public:
			Simulation(const std::unordered_map<std::string, std::string>& param_map) {

			}
			std::unordered_map<std::string, std::string> run() override;
		};
	}
}