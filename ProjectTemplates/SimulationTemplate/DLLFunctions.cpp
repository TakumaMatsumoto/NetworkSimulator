#include "DLLFunctions.h"
#include "ISimulation.h"

namespace sim {
	namespace sample {
		class Simulation : public ISimulation {
		public:
			sim::Result run() override {
				return sim::Result();
			}
		};
	}
}
sim::ISimulation* CreateInstance(const std::unordered_map<std::string, std::string>& param_map) {
	return new sim::sample::Simulation();
}