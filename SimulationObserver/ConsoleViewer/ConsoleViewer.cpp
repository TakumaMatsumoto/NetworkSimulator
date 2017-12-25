#include "ConsoleViewer.h"
#include <iostream>
using namespace sim::observer;
using namespace std;

// �V�~�����[�^�J�n���Ɏ��s�����֐�
// @param conf: �V�~�����[�^�̐ݒ�
void ConsoleViewer::onSimulatorBegin(const sim::Config& conf){

}

// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
// @param param_name:	�V�~�����[�V�����ݒ�̖��O
// @param param:		�V�~�����[�V�����ݒ�
void ConsoleViewer::onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param){
	cout << "name of current simulation parameter:" << param_name << endl;
}

// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
// @param current_trial_number: ���݂̎��s��
void ConsoleViewer::onSimulationBegin(const unsigned int current_trial_number) {
	cout << "current trial:" << current_trial_number << endl;
}

// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
// @param current_trial_number: ���݂̎��s��
// @param result: �V�~�����[�V��������
void ConsoleViewer::onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) {

}

// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
// @param param_name:	�V�~�����[�V�����ݒ�̖��O
// @param results: ���s�񐔕��̃V�~�����[�V��������
void ConsoleViewer::onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) {

}

// �V�~�����[�^�I�����Ɏ��s�����֐�
void ConsoleViewer::onSimulatorEnd() {

}
