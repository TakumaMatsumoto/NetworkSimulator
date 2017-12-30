#pragma once
#include <unordered_map>
#include <string>

namespace sim {
	namespace swn {
		class Result {
			// First Node Die状態になったラウンド
			const unsigned int m_fnd_round = 0;
			// All Node Die状態になったラウンド
			const unsigned int m_and_round = 0;
			// 収集できたデータ量 / 最大データ量
			const double m_data_collected_rate = 0.0;
			// エリアカバー率
			const double m_area_cover_rate = 0.0;
			// 各ラウンドでのノード生存率
			const std::vector<double> m_nodes_survival_rates;
		public:
			Result(
				const unsigned int fnd_round,
				const unsigned int and_round,
				const double data_collected_rate,
				const double area_cover_rate,
				const std::vector<double>& nodes_survival_rates) :
				m_fnd_round(fnd_round), m_and_round(and_round),
				m_data_collected_rate(data_collected_rate),
				m_area_cover_rate(area_cover_rate),
				m_nodes_survival_rates(nodes_survival_rates){
			}
			sim::Result toSimResult() const {
				std::string buf;
				for (size_t i = 0, length = m_nodes_survival_rates.size(); i < length; i++)
				{
					buf += std::to_string(m_nodes_survival_rates[i]) + (i == length - 1 ? "" : ":");
				}
				return {
					{ "fnd_round", std::to_string(m_fnd_round)},
					{ "and_round", std::to_string(m_and_round)},
					{ "nodes_survival_rates", buf },
					{ "data_collection_rate",	std::to_string(m_data_collected_rate) },
					{ "area_cover_rate",		std::to_string(m_area_cover_rate) },
				};
			}
		};
	}
}