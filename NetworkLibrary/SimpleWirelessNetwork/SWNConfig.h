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
			// センサノード数
			unsigned int m_number_of_sensor_nodes;
			// 通信可能範囲
			unsigned int m_transmission_range;
			// 1つのノードが収集するデータ数[bit]
			unsigned int m_message_size;
			// 初期エネルギー[J]
			unsigned int m_initial_energy;
			// 1bitのデータを通信する際の消費電力[J/bit]
			double m_consume_energy_for_communication_per_bit;
			// 1bitのデータを1mだけ送信する際に使用される増幅器の消費電力[J/(bit・m^2)]
			double m_consume_energy_for_transmission_per_bit;
			// レールの角度
			std::vector<double> m_rails;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
			// エリアの範囲を取得する
			std::pair<unsigned int, unsigned int> getAreaRange() const {
				return std::make_pair(m_area_width, m_area_height);
			}
		};
	}
}