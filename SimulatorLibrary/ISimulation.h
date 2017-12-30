#pragma once
#include <unordered_map>
#include "Result.h"

namespace sim
{
	class ISimulation {
	public:
		virtual ~ISimulation() = default;
		// return: �n�b�V���l�ɂ������s����
		virtual Result run() = 0;
	};
}