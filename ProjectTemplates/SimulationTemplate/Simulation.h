#pragma once
#include "IRunnable.h"

namespace sim {
	namespace sample {
		class Simulation : public IRunnable {
		public:
			std::unordered_map<std::string, std::string> run() override {
				return std::unordered_map<std::string, std::string>();
			}
		};
	}
}