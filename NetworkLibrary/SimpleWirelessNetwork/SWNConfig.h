#pragma once
#include "Table.h"

namespace sim {
	namespace swn {
		class Config {
		public:
			// エリア幅
			unsigned int m_area_width;
			// エリア高さ
			unsigned int m_area_height;
			// ノード数
			unsigned int m_number_of_nodes;
			// 通信可能範囲
			unsigned int m_transmission_range;
			// 1つのノードが収集するデータ数[bit]
			unsigned int m_message_size;
			// 初期エネルギー[J]
			unsigned int m_initial_energy;
			// レールの角度
			std::vector<double> m_rails;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
		};
	}
}