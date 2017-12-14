#pragma once
#include <unordered_map>

namespace sim
{
	class IRunnable {
	public:
		virtual ~IRunnable() = default;
		// return: ハッシュ値にした実行結果
		virtual std::unordered_map<std::string, std::string> run() = 0;
	};
}