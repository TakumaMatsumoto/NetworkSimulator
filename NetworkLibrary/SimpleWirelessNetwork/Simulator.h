#pragma once
#include "IRunnable.h"

namespace sim {
	namespace swn {
		class Simulator : public IRunnable {
		public:
			void run() override;
			std::unordered_map<std::string, std::string> toMap() const override {
				return std::unordered_map<std::string, std::string>();
			}
		};
	}
}