#include <iostream>
#include "DLLFunctions.h"
using namespace std;

// �V�~�����[�^�J�n���Ɏ��s�����֐�
// @param conf: �V�~�����[�^�̐ݒ�
void OnSimulatorBegin(const Config& conf) {

}
// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
// @param param_name:	�V�~�����[�V�����ݒ�̖��O
// @param param:		�V�~�����[�V�����ݒ�
void OnSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param) {

}
// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
// @param current_trial_number: ���݂̎��s��
void OnSimulationBegin(const unsigned int current_trial_number) {

}
// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
// @param result: �V�~�����[�V��������
void OnSimulationEnd(const std::unordered_map<std::string, std::string>& result) {

}
// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
// @param results: ���s�񐔕��̃V�~�����[�V��������
void OnSimulationsEnd(const std::vector<std::unordered_map<std::string, std::string>>& results) {

}
// �V�~�����[�^�I�����Ɏ��s�����֐�
void OnSimulatorEnd() {

}
