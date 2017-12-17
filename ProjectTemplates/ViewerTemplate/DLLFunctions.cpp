#include <iostream>
#include "DLLFunctions.h"
using namespace std;

namespace sim {
	namespace sample {
		class Viewer : public ISimulationObserver {
		public:
			// シミュレータ開始時に実行される関数
			// @param conf: シミュレータの設定
			virtual void onSimulatorBegin(const Config& conf) override {

			}
			// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
			// @param param_name:	シミュレーション設定の名前
			// @param param:		シミュレーション設定
			virtual void onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param) override {

			}
			// シミュレーションが開始する毎に実行される関数
			// @param current_trial_number: 現在の試行回数
			virtual void onSimulationBegin(const unsigned int current_trial_number) override {

			}
			// シミュレーションが終了する毎に実行される関数
			// @param current_trial_number: 現在の試行回数
			// @param result: シミュレーション結果
			virtual void onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) override {

			}
			// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
			// @param param_name:	シミュレーション設定の名前
			// @param results: 試行回数分のシミュレーション結果
			virtual void onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) override {

			}
			// シミュレータ終了時に実行される関数
			virtual void onSimulatorEnd() override {

			}
		};
	}
}

sim::IViewer* CreateInstance(const std::unordered_map<std::string, std::string>& param_map) {
	return new sim::sample::Viewer();
}