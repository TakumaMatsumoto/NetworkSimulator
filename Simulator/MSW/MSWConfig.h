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
			// �V�~�����[�V�����̏󋵊Ď���S������dll�t�@�C����
			const std::string m_observer_dll_filename;
			// �V�~�����[�V�����S�̂̐ݒ�
			// @param number_of_trials:�V�~�����[�V�������s��
			// @param simulation_dll_filename:�V�~�����[�V�������@����`���ꂽdll�t�@�C����
			// @param output_dll_filenam:�V�~�����[�V�����̏󋵊Ď���S������dll�t�@�C����
			Config(
				const sim::Config& sim_config,
				const std::string& simulation_dll_filename,
				const std::string& observer_dll_filename) :
				m_sim_config(sim_config),
				m_simulation_dll_filename(simulation_dll_filename),
				m_observer_dll_filename(observer_dll_filename) {
			}
		};
	}
}