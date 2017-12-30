#pragma once
#include "ISimulationObserver.h"
#include "Table.h"

namespace sim {
	namespace observer {
		class CSVRecorder : public ISimulationObserver {
		public:
			class Config {
			public:
				const bool m_log = false;
				const std::string m_filename;
				Config(const std::string& filename) : m_filename(filename) {
				}
				static Config createFromConfigFile();
			};
			CSVRecorder(const Config& conf) : m_conf(conf) {
			}
			// シミュレータ開始時に実行される関数
			// @param conf: シミュレータの設定
			virtual void onSimulatorBegin(const sim::Config& conf) override {
			}
			// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
			// @param param_name:	シミュレーション設定の名前
			// @param param:		シミュレーション設定
			virtual void onSimulationsBegin(const std::string& param_name, const sim::Parameter& param) override {

			}
			// シミュレーションが開始する毎に実行される関数
			// @param current_trial_number: 現在の試行回数
			virtual void onSimulationBegin(const unsigned int current_trial_number) override {

			}
			// シミュレーションが終了する毎に実行される関数
			// @param current_trial_number: 現在の試行回数
			// @param result: シミュレーション結果
			virtual void onSimulationEnd(const unsigned int current_trial_number, const sim::Result& result) override {

			}
			// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
			// @param param_name:	シミュレーション設定の名前
			// @param results: 試行回数分のシミュレーション結果
			virtual void onSimulationsEnd(const std::string& param_name, const sim::Results& results) override;
			// シミュレータ終了時に実行される関数
			virtual void onSimulatorEnd() override {
				table::FileStorage(m_conf.m_filename).save(m_table);
			}
		private:
			const Config m_conf;
			table::Table m_table;
		};
	}
}