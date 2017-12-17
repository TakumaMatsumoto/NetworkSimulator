#pragma once
#include <unordered_map>
#include <string>
#include "Table.h"

namespace sim {
	class Config {
	public:
		// 試行回数
		const unsigned int m_number_of_trials;
		// パラメータテーブル
		const table::Table m_param_table;
		// シミュレーション全体の設定
		// @param number_of_trials:シミュレーション試行回数
		// @param param_table:パラメータテーブル
		Config(const unsigned int number_of_trials, const table::Table& param_table)
			: m_number_of_trials(number_of_trials), m_param_table(param_table) {

		}
		std::unordered_map<std::string, std::string> toMap() const {
			return {
				{"number of trials", std::to_string(m_number_of_trials)}
			};
		}
	};
}