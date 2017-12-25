#include "Viewer.h"
#include <iostream>
using namespace sim::viewer;
using namespace std;

// シミュレータ開始時に実行される関数
// @param conf: シミュレータの設定
void Console::onSimulatorBegin(const sim::Config& conf){

}

// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
// @param param_name:	シミュレーション設定の名前
// @param param:		シミュレーション設定
void Console::onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param){
	cout << "name of current simulation parameter:" << param_name << endl;
}

// シミュレーションが開始する毎に実行される関数
// @param current_trial_number: 現在の試行回数
void Console::onSimulationBegin(const unsigned int current_trial_number) {
	cout << "current trial:" << current_trial_number << endl;
}

// シミュレーションが終了する毎に実行される関数
// @param current_trial_number: 現在の試行回数
// @param result: シミュレーション結果
void Console::onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) {

}

// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
// @param param_name:	シミュレーション設定の名前
// @param results: 試行回数分のシミュレーション結果
void Console::onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) {

}

// シミュレータ終了時に実行される関数
void Console::onSimulatorEnd() {

}
