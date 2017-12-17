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
			// �m�[�h��
			unsigned int m_number_of_nodes;
			// �ʐM�\�͈�
			unsigned int m_transmission_range;
			// 1�̃m�[�h�����W����f�[�^��[bit]
			unsigned int m_message_size;
			// �����G�l���M�[[J]
			unsigned int m_initial_energy;
			// ���[���̊p�x
			std::vector<double> m_rails;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
		};
	}
}