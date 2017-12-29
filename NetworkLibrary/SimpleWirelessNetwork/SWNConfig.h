#pragma once
#include <unordered_map>
#include <string>
#include "geo.h"
#include "Rail.h"
#include "UIDCreator.h"
#include "EnergyConsumption.h"

namespace sim {
	namespace swn {
		class Config {
		public:
			// エリア幅[m]
			unsigned int m_area_width;
			// エリア高さ[m]
			unsigned int m_area_height;
			// センサノード数
			unsigned int m_number_of_sensor_nodes;
			// レールの角度[radian]
			std::vector<double> m_rail_angles;

			// 通信可能範囲(最小、最大)[m]
			std::pair<double, double> m_transmission_range;
			// 1つのノードが収集するデータ数[bit]
			unsigned int m_message_size;

			// 初期エネルギー[J]
			double m_initial_energy;
			// 各主動作に必要な電力量
			EnergyConsumption m_energy_consumption;

			// 障害物の個数
			std::pair<unsigned int, unsigned int> m_number_of_obstacles;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
			// エリアの範囲を取得する
			std::pair<unsigned int, unsigned int> getAreaRange() const {
				return std::make_pair(m_area_width, m_area_height);
			}
			// レールを取得する
			std::vector<Rail> getRails(UIDCreator& uid_creator) const {
				std::vector<Rail> ret;
				for (const auto& rail_angle : m_rail_angles)
				{
					ret.push_back(Rail(uid_creator.get(), geo::StraightLine<double>::createFromSlopeAngleAndIntercept(rail_angle, 0.0)));
				}
				return ret;
			}
			// 通信可能範囲を選択する
			double selectTransmissionRange(const double random_0_to_1) const {
				return m_transmission_range.first + random_0_to_1 * (m_transmission_range.second - m_transmission_range.first);
			}
			// 障害物の個数を選択する
			unsigned int selectNumberOfObstacles(const double random_0_to_1) const {
				return static_cast<unsigned int>(m_number_of_obstacles.first + random_0_to_1 * (m_number_of_obstacles.second - m_number_of_obstacles.first));
			}
		};
	}
}