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
			// データ収集率
			// 収集できたデータ量 / 最大データ量
			const double m_data_collected_rate = 0.0;
			// エリアカバー率
			const double m_area_cover_rate = 0.0;
		public:
			Result(
				const unsigned int fnd_round,
				const unsigned int and_round,
				const double data_collected_rate,
				const double area_cover_rate) : 
				m_fnd_round(fnd_round), m_and_round(and_round),
				m_data_collected_rate(data_collected_rate),
				m_area_cover_rate(area_cover_rate)	{
			}
			std::unordered_map<std::string, std::string> toMap() const {
				return {
					{ "fnd_round", std::to_string(m_fnd_round)},
					{ "and_round", std::to_string(m_and_round)},
					{ "data_collection_rate",	std::to_string(m_data_collected_rate) },
					{ "area_cover_rate",		std::to_string(m_area_cover_rate) },
				};
			}
		};
	}
}