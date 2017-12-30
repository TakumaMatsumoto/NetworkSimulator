#pragma once
#include "ISimulationObserver.h"
#include "Table.h"

namespace sim {
	namespace observer {
		class CSVRecorder : public ISimulationObserver {
		public:
			class Config {
			public:
				const bool m_log = false;
				const std::string m_filename;
				Config(const std::string& filename) : m_filename(filename) {
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
			virtual void onSimulationsBegin(const std::string& param_name, const sim::Parameter& param) override {

			}
			// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			virtual void onSimulationBegin(const unsigned int current_trial_number) override {

			}
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
			virtual void onSimulatorEnd() override {
				table::FileStorage(m_conf.m_filename).save(m_table);
			}
		private:
			const Config m_conf;
			table::Table m_table;
		};
	}
}