#include "Viewer.h"
#include <iostream>
using namespace sim::viewer;
using namespace std;

// �V�~�����[�^�J�n���Ɏ��s�����֐�
// @param conf: �V�~�����[�^�̐ݒ�
void Console::onSimulatorBegin(const sim::Config& conf){

}

// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
// @param param_name:	�V�~�����[�V�����ݒ�̖��O
// @param param:		�V�~�����[�V�����ݒ�
void Console::onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param){
	cout << "name of current simulation parameter:" << param_name << endl;
}

// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
// @param current_trial_number: ���݂̎��s��
void Console::onSimulationBegin(const unsigned int current_trial_number) {
	cout << "current trial:" << current_trial_number << endl;
}

// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
// @param current_trial_number: ���݂̎��s��
// @param result: �V�~�����[�V��������
void Console::onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) {

}

// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
// @param param_name:	�V�~�����[�V�����ݒ�̖��O
// @param results: ���s�񐔕��̃V�~�����[�V��������
void Console::onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) {

}

// �V�~�����[�^�I�����Ɏ��s�����֐�
void Console::onSimulatorEnd() {

}
