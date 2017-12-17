#pragma once
#include <unordered_map>
#include <string>
#include "Table.h"

namespace sim {
	class Config {
	public:
		// ���s��
		const unsigned int m_number_of_trials;
		// �p�����[�^�e�[�u��
		const table::Table m_param_table;
		// �V�~�����[�V�����S�̂̐ݒ�
		// @param number_of_trials:�V�~�����[�V�������s��
		// @param param_table:�p�����[�^�e�[�u��
		Config(const unsigned int number_of_trials, const table::Table& param_table)
			: m_number_of_trials(number_of_trials), m_param_table(param_table) {

		}
		std::unordered_map<std::string, std::string> toMap() const {
			return {
				{"number of trials", std::to_string(m_number_of_trials)}
			};
		}
	};
}