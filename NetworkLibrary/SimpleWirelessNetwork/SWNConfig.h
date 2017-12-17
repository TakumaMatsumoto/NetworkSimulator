#pragma once
#include "Table.h"

namespace sim {
	namespace swn {
		class Config {
		public:
			// シミュレーション実行時間
			unsigned int m_simulation_period;
			// ノード数
			unsigned int m_number_of_nodes;
			// 1つのノードが収集するデータ数
			unsigned int m_size_of_data;
			// エリア幅
			unsigned int m_area_width;
			// エリア高さ
			unsigned int m_area_height;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
		};
	}
}