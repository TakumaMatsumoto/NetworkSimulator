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
			// �G���A��[m]
			unsigned int m_area_width;
			// �G���A����[m]
			unsigned int m_area_height;
			// �Z���T�m�[�h��
			unsigned int m_number_of_sensor_nodes;
			// ���[���̊p�x[radian]
			std::vector<double> m_rail_angles;

			// �ʐM�\�͈�(�ŏ��A�ő�)[m]
			std::pair<double, double> m_transmission_range;
			// 1�̃m�[�h�����W����f�[�^��[bit]
			unsigned int m_message_size;

			// �����G�l���M�[[J]
			double m_initial_energy;
			// �e�哮��ɕK�v�ȓd�͗�
			EnergyConsumption m_energy_consumption;

			// ��Q���̌�
			std::pair<unsigned int, unsigned int> m_number_of_obstacles;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
			// �G���A�͈̔͂��擾����
			std::pair<unsigned int, unsigned int> getAreaRange() const {
				return std::make_pair(m_area_width, m_area_height);
			}
			// ���[�����擾����
			std::vector<Rail> getRails(UIDCreator& uid_creator) const {
				std::vector<Rail> ret;
				for (const auto& rail_angle : m_rail_angles)
				{
					ret.push_back(Rail(uid_creator.get(), geo::StraightLine<double>::createFromSlopeAngleAndIntercept(rail_angle, 0.0)));
				}
				return ret;
			}
			// �ʐM�\�͈͂�I������
			double selectTransmissionRange(const double random_0_to_1) const {
				return m_transmission_range.first + random_0_to_1 * (m_transmission_range.second - m_transmission_range.first);
			}
			// ��Q���̌���I������
			unsigned int selectNumberOfObstacles(const double random_0_to_1) const {
				return static_cast<unsigned int>(m_number_of_obstacles.first + random_0_to_1 * (m_number_of_obstacles.second - m_number_of_obstacles.first));
			}
		};
	}
}