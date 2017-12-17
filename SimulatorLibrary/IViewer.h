#pragma once
#include <unordered_map>
#include <string>
#include "Config.h"

namespace sim
{
	class IViewer {
	public:
		virtual ~IViewer() = default;
		// シミュレータ開始時に実行される関数
		// @param conf: シミュレータの設定
		virtual void onSimulatorBegin(const Config& conf) = 0;
		// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
		// @param param_name:	シミュレーション設定の名前
		// @param param:		シミュレーション設定
		virtual void onSimulationsBegin(const std::string& param_name, const std::unordered_map<std::string, std::string>& param) = 0;
		// シミュレーションが開始する毎に実行される関数
		// @param current_trial_number: 現在の試行回数
		virtual void onSimulationBegin(const unsigned int current_trial_number) = 0;
		// シミュレーションが終了する毎に実行される関数
		// @param current_trial_number: 現在の試行回数
		// @param result: シミュレーション結果
		virtual void onSimulationEnd(const unsigned int current_trial_number, const std::unordered_map<std::string, std::string>& result) = 0;
		// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
		// @param param_name:	シミュレーション設定の名前
		// @param results: 試行回数分のシミュレーション結果
		virtual void onSimulationsEnd(const std::string& param_name, const std::vector<std::unordered_map<std::string, std::string>>& results) = 0;
		// シミュレータ終了時に実行される関数
		virtual void onSimulatorEnd() = 0;
	};
}