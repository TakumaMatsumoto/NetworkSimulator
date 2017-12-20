#pragma once
#include "Table.h"

namespace sim {
	namespace swn {
		class Config {
		public:
			// �G���A��
			unsigned int m_area_width;
			// �G���A����
			unsigned int m_area_height;
			// �Z���T�m�[�h��
			unsigned int m_number_of_sensor_nodes;
			// �ʐM�\�͈�
			unsigned int m_transmission_range;
			// 1�̃m�[�h�����W����f�[�^��[bit]
			unsigned int m_message_size;
			// �����G�l���M�[[J]
			unsigned int m_initial_energy;
			// 1bit�̃f�[�^��ʐM����ۂ̏���d��[J/bit]
			double m_consume_energy_for_communication_per_bit;
			// 1bit�̃f�[�^��1m�������M����ۂɎg�p����鑝����̏���d��[J/(bit�Em^2)]
			double m_consume_energy_for_transmission_per_bit;
			// ���[���̊p�x
			std::vector<double> m_rails;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
			// �G���A�͈̔͂��擾����
			std::pair<unsigned int, unsigned int> getAreaRange() const {
				return std::make_pair(m_area_width, m_area_height);
			}
		};
	}
}