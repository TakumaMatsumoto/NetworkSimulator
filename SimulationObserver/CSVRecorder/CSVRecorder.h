#pragma once
#include "ISimulationObserver.h"
#include "Table.h"

namespace sim {
	namespace observer {
		class CSVRecorder : public ISimulationObserver {
			std::string m_param_name;
		public:
			class Config {
			public:
				// [required]
				const std::string m_filename;
				// [option]
				const bool m_verbose = false;
				Config(const std::string& filename, const bool verbose = false) 
					: m_filename(filename), m_verbose(verbose) {
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
			virtual void onSimulationsBegin(const std::string& param_name, const sim::Parameter& param) override;
			// シミュレーションが開始する毎に実行される関数
			// @param current_trial_number: 現在の試行回数
			virtual void onSimulationBegin(const unsigned int current_trial_number) override;
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
			virtual void onSimulatorEnd() override;
		private:
			// テーブルの更新
			// @param rup: sim::Resultに関わるユニークなペア
			// rup first:  name
			// rup second: type
			void updateTable(const sim::ResultNameTypePair& ntp, const std::string& param_name, const sim::Results& results);
			const Config m_conf;
			// 配列型の値を記録したテーブル
			// first: カラム名
			// second: テーブル
			std::unordered_map<std::string, table::Table> m_tables_for_array_values;
			table::Table& searchTableForColumn(const std::string& column) {
				if (m_tables_for_array_values.find(column) == m_tables_for_array_values.end()) {
					m_tables_for_array_values.insert({ column, table::Table() });
				}
				return m_tables_for_array_values.at(column);
			}
			table::Table m_table_for_primitive_values;
		};
	}
}