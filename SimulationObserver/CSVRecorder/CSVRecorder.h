#pragma once
#include "ISimulationObserver.h"
#include "Table.h"

namespace sim {
	namespace observer {
		class CSVRecorder : public ISimulationObserver {
			std::string m_param_name;
		public:
			class Config {
			public:
				// [required]
				const std::string m_filename;
				// [option]
				const bool m_verbose = false;
				Config(const std::string& filename, const bool verbose = false) 
					: m_filename(filename), m_verbose(verbose) {
				}
				static Config createFromConfigFile();
			};
			CSVRecorder(const Config& conf) : m_conf(conf) {
			}
			// �V�~�����[�^�J�n���Ɏ��s�����֐�
			// @param conf: �V�~�����[�^�̐ݒ�
			virtual void onSimulatorBegin(const sim::Config& conf) override {
			}
			// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
			// @param param_name:	�V�~�����[�V�����ݒ�̖��O
			// @param param:		�V�~�����[�V�����ݒ�
			virtual void onSimulationsBegin(const std::string& param_name, const sim::Parameter& param) override;
			// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			virtual void onSimulationBegin(const unsigned int current_trial_number) override;
			// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			// @param result: �V�~�����[�V��������
			virtual void onSimulationEnd(const unsigned int current_trial_number, const sim::Result& result) override {

			}
			// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
			// @param param_name:	�V�~�����[�V�����ݒ�̖��O
			// @param results: ���s�񐔕��̃V�~�����[�V��������
			virtual void onSimulationsEnd(const std::string& param_name, const sim::Results& results) override;
			// �V�~�����[�^�I�����Ɏ��s�����֐�
			virtual void onSimulatorEnd() override;
		private:
			// �e�[�u���̍X�V
			// @param rup: sim::Result�Ɋւ�郆�j�[�N�ȃy�A
			// rup first:  name
			// rup second: type
			void updateTable(const sim::ResultNameTypePair& ntp, const std::string& param_name, const sim::Results& results);
			const Config m_conf;
			// �z��^�̒l���L�^�����e�[�u��
			// first: �J������
			// second: �e�[�u��
			std::unordered_map<std::string, table::Table> m_tables_for_array_values;
			table::Table& searchTableForColumn(const std::string& column) {
				if (m_tables_for_array_values.find(column) == m_tables_for_array_values.end()) {
					m_tables_for_array_values.insert({ column, table::Table() });
				}
				return m_tables_for_array_values.at(column);
			}
			table::Table m_table_for_primitive_values;
		};
	}
}