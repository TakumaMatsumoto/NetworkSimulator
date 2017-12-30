#pragma once
#include <unordered_map>
#include <string>

namespace sim {
	class ResultValue {
	public:
		std::string m_type;
		std::string m_value;
	};
	using Result = std::unordered_map<std::string, ResultValue>;
	using Results = std::vector<Result>;
}