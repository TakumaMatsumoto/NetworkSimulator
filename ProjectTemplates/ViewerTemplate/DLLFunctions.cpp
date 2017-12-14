#include <iostream>
#include "DLLFunctions.h"
using namespace std;

// シミュレータ開始時に実行される関数
// @param conf: シミュレータの設定
void OnSimulatorBegin(const Config& conf) {

}
// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
// @param param_name:	シミュレーション設定の名前
// @param param:		シミュレーション設定
void OnSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param) {

}
// シミュレーションが開始する毎に実行される関数
// @param current_trial_number: 現在の試行回数
void OnSimulationBegin(const unsigned int current_trial_number) {

}
// シミュレーションが終了する毎に実行される関数
// @param result: シミュレーション結果
void OnSimulationEnd(const std::unordered_map<std::string, std::string>& result) {

}
// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
// @param results: 試行回数分のシミュレーション結果
void OnSimulationsEnd(const std::vector<std::unordered_map<std::string, std::string>>& results) {

}
// シミュレータ終了時に実行される関数
void OnSimulatorEnd() {

}
