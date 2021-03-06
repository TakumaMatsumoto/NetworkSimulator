#pragma once
#include <unordered_map>
#include <string>

namespace sim {
	using ResultName = std::string;
	using ResultType = std::string;
	using ResultValue = std::string;
	using ResultNameTypePair = std::pair<ResultName, ResultType>;
	using ResultTypeValuePair = std::pair<ResultType, ResultValue>;
	// 名前とResultValueを紐づけている
	using Result = std::unordered_map<ResultName, ResultTypeValuePair>;
	using Results = std::vector<Result>;
}