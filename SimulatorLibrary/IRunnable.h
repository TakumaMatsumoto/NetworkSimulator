#pragma once
#include <unordered_map>

namespace sim
{
	class IRunnable {
	public:
		virtual ~IRunnable() = default;
		// return: �n�b�V���l�ɂ������s����
		virtual std::unordered_map<std::string, std::string> run() = 0;
	};
}