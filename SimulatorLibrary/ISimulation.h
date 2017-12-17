#pragma once
#include <unordered_map>

namespace sim
{
	class ISimulation {
	public:
		virtual ~ISimulation() = default;
		// return: �n�b�V���l�ɂ������s����
		virtual std::unordered_map<std::string, std::string> run() = 0;
	};
}