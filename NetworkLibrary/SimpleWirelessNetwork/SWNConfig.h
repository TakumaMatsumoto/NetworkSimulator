#pragma once
#include "Table.h"

namespace sim {
	namespace swn {
		class Config {
		public:
			// �V�~�����[�V�������s����
			unsigned int m_simulation_period;
			// �m�[�h��
			unsigned int m_number_of_nodes;
			// 1�̃m�[�h�����W����f�[�^��
			unsigned int m_size_of_data;
			// �G���A��
			unsigned int m_area_width;
			// �G���A����
			unsigned int m_area_height;
			static Config createFromMap(const std::unordered_map<std::string, std::string>& umap);
		};
	}
}