#include "DLLFunctions.h"
#include "ISimulation.h"

namespace sim {
	namespace sample {
		class Simulation : public ISimulation {
		public:
			std::unordered_map<std::string, std::string> run() override {
				return std::unordered_map<std::string, std::string>();
			}
		};
	}
}
sim::ISimulation* CreateInstance(const std::unordered_map<std::string, std::string>& param_map) {
	return new sim::sample::Simulation();
}