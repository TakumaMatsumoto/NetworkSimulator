#pragma once
#include <string>
#include <unordered_map>

namespace sim {
	class IMappable {
	public:
		virtual ~IMappable() = default;
		virtual std::unordered_map<std::string, std::string> toMap() const = 0;
	};
}