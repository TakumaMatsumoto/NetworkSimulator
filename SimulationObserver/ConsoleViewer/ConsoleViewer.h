#pragma once
#include "ISimulationObserver.h"

namespace sim {
	namespace observer {
		class ConsoleViewer : public ISimulationObserver {
		public:
			// �V�~�����[�^�J�n���Ɏ��s�����֐�
			// @param conf: �V�~�����[�^�̐ݒ�
			virtual void onSimulatorBegin(const Config& conf) override;
			// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
			// @param param_name:	�V�~�����[�V�����ݒ�̖��O
			// @param param:		�V�~�����[�V�����ݒ�
			virtual void onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param) override;
			// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			virtual void onSimulationBegin(const unsigned int current_trial_number) override;
			// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
			// @param current_trial_number: ���݂̎��s��
			// @param result: �V�~�����[�V��������
			virtual void onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) override;
			// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
			// @param param_name:	�V�~�����[�V�����ݒ�̖��O
			// @param results: ���s�񐔕��̃V�~�����[�V��������
			virtual void onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) override;
			// �V�~�����[�^�I�����Ɏ��s�����֐�
			virtual void onSimulatorEnd() override;
		};
	}
}