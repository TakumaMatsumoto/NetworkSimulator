#include <vector>
#include "Config.h"
#pragma once
namespace sim {
	namespace msw {
		// �V�~�����[�V�����̐ݒ�p�����[�^�N���X
		class Config {
		public:
			// �V�~�����[�V�����̐ݒ�(OS�Ɉˑ����Ȃ��ӏ�)
			const sim::Config m_sim_config;
			// ���s����V�~�����[�V������dll�t�@�C����
			const std::string m_simulation_dll_filename;
			// ���ʏo�͂�S������dll�t�@�C����
			const std::vector<std::string> m_output_dlls_filename;
			// �V�~�����[�V�����S�̂̐ݒ�
			// @param number_of_trials:�V�~�����[�V�������s��
			// @param simulation_dll_filename:�V�~�����[�V�������@����`���ꂽdll�t�@�C����
			// @param output_dlls_filenam:�V�~�����[�V�������ʂ̏o�͕��@�ɂ��Ē�`���ꂽdll�t�@�C�����Q
			Config(
				const sim::Config& sim_config,
				const std::string& simulation_dll_filename,
				const std::vector<std::string>& output_dlls_filename) :
				m_sim_config(sim_config),
				m_simulation_dll_filename(simulation_dll_filename),
				m_output_dlls_filename(output_dlls_filename) {
			}
		};
	}
}