#include <vector>
#pragma once
namespace sim {
	// �V�~�����[�V�����̐ݒ�p�����[�^�N���X
	class Config {
	public:
		// ���s��
		const unsigned int m_number_of_trials;
		// ���s����V�~�����[�V������dll�t�@�C����
		const std::string m_simulation_dll_filename;
		// ���ʏo�͂�S������dll�t�@�C����
		const std::vector<std::string> m_output_dlls_filename;
		Config(
			const unsigned int number_of_trials, 
			const std::string& simulation_dll_filename,
			const std::vector<std::string>& output_dlls_filename) : 
			m_number_of_trials(number_of_trials),
			m_simulation_dll_filename(simulation_dll_filename),
			m_output_dlls_filename(output_dlls_filename){
		}
	};
}