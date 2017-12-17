#pragma once
#include <unordered_map>
#include <string>

namespace sim {
	namespace swn {
		class Result {
		private:
			// First Node Die��ԂɂȂ������E���h
			unsigned int m_fnd_round = 0;
		public:
			std::unordered_map<std::string, std::string> toMap() const {
				return {
					{"fnd_round", std::to_string(m_fnd_round)}
				};
			}
		};
	}
}