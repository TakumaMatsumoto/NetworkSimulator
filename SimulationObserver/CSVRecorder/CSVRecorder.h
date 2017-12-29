#pragma once
#include "ISimulationObserver.h"
#include "Table.h"
template <typename List>
void split(const std::string& s, const std::string& delim, List& result)
{
	result.clear();

	using string = std::string;
	string::size_type pos = 0;

	while (pos != string::npos)
	{
		string::size_type p = s.find(delim, pos);

		if (p == string::npos)
		{
			result.push_back(s.substr(pos));
			break;
		}
		else {
			result.push_back(s.substr(pos, p - pos));
		}

		pos = p + delim.size();
	}
}

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
				static Config createFromConfigFile() {
					const std::string fname = "config.txt";
					std::ifstream ifs(fname);
					std::string str;
					std::unordered_map<std::string, std::string> umap;
					while (getline(ifs, str))
					{
						std::vector<std::string> map;
						split(str, "=", map);
						umap.insert({ map[0], map[1] });
					}
					return Config(umap.at("filename"));
				}
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
				const auto chead = table::ColumnHeader(param_name);
				const auto keys = [&results]() {
					std::vector<std::string> ret;
					for (const auto& map : results[0])
					{
						ret.push_back(map.first);
					}
					return ret;
				}();
				// 各キーの値を取得して平均値を算出する
				for (const auto& key : keys)
				{
					const auto rhead = table::RowHeader(key);
					double ave = 0.0;
					for (const auto& result : results)
					{
						ave += std::stod(result.at(key));
					}
					m_table.insert(
						table::Index(chead, rhead), 
						table::Cell(std::to_string(ave)));
				}
			}
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