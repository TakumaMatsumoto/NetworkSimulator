#pragma once
#include <unordered_map>
#include <string>

namespace sim {
	template<typename T>
	class IFactory {
	public:
		virtual ~IFactory() = default;
		// インスタンスを作成する
		// @param param_map: パラメータ名をkey,値をvalueとしたハッシュマップ
		virtual T* createInstance(const std::unordered_map<std::string, std::string>& param_map) = 0;
		virtual void init() = 0;
		virtual void terminate() = 0;
	};
}