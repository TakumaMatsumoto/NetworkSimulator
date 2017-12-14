#pragma once
#include <unordered_map>
#include <string>
#include "IRunnable.h"

namespace sim
{
	class ISimulation {
	public:
		virtual ~ISimulation() = default;
		// シミュレーションのインスタンスを作成します
		// @param param_map: パラメータ名をkey,値をvalueとしたハッシュマップ
		virtual sim::IRunnable* createInstance(const std::unordered_map<std::string, std::string>& param_map) = 0;
	};
}