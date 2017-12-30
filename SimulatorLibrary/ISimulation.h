#pragma once
#include <unordered_map>
#include "Result.h"

namespace sim
{
	class ISimulation {
	public:
		virtual ~ISimulation() = default;
		// return: ハッシュ値にした実行結果
		virtual Result run() = 0;
	};
}