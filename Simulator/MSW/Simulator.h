#pragma once
#include <Windows.h>
#include "Table.h"
#include "Config.h"
#include "ISimulation.h"
#include "IViewer.h"

namespace sim
{
	namespace msw {
		class Simulator {
		private:
			const Config m_conf;
			const table::Table m_param_table;
			class Simulation : public ISimulation {
			private:
				HMODULE m_lib_handle;
				const std::string m_dll_filename;
				// シミュレーション環境生成関数の型
				// @param
				// param_map: パラメータのハッシュマップ(key: パラメータ名, value: パラメータ値(string))
				using CREATE_SIMULATION_INSTANCE_FUNC = sim::IRunnable*(*)(const std::unordered_map<std::string, std::string>& param_map);
				CREATE_SIMULATION_INSTANCE_FUNC m_func;
			public:
				Simulation(const std::string& dll_filename)
					: m_dll_filename(dll_filename) {

				}
				sim::IRunnable* createInstance(const std::unordered_map<std::string, std::string>& param_map) override { return m_func(param_map); }
				void init();
				void terminate();
			};
			class Viewer : public IViewer {
			private:
				// シミュレータ開始時に実行される関数の型
				// @param
				// conf: シミュレータの設定
				using ON_SIMULATOR_BEGIN_FUNC = void(*)(const Config& conf);
				// ある一つのパラメータ環境下でのシミュレーションが開始するタイミングで実行される関数の型
				// @param
				// param_name: 試行する条件の名前
				// param: 試行する条件
				using ON_SIMULATIONS_BEGIN_FUNC = void(*)(const std::string& param_name, const std::unordered_map<std::string, std::string>& param);
				// シミュレーションが開始する毎に実行される関数の型
				// @param
				// current_trial_number: 現在の試行回数
				using ON_SIMULATION_BEGIN_FUNC = void(*)(const unsigned int current_trial_number);
				// シミュレーションが終了する毎に実行される関数の型
				// @param
				// result: シミュレーション結果
				using ON_SIMULATION_END_FUNC = void(*)(const std::unordered_map<std::string, std::string>& result);
				// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数の型
				// @param
				// results: 試行回数分のシミュレーション結果
				using ON_SIMULATIONS_END_FUNC = void(*)(const std::vector<std::unordered_map<std::string, std::string>>& results);
				// シミュレータ終了時に実行される関数の型
				using ON_SIMULATOR_END_FUNC = void(*)();
				const std::string m_dll_filename;
				HMODULE m_lib_handle;
				ON_SIMULATOR_BEGIN_FUNC m_simulator_begin_func;
				ON_SIMULATIONS_BEGIN_FUNC m_simulations_begin_func;
				ON_SIMULATION_BEGIN_FUNC m_simulation_begin_func;
				ON_SIMULATION_END_FUNC m_simulation_end_func;
				ON_SIMULATIONS_END_FUNC m_simulations_end_func;
				ON_SIMULATOR_END_FUNC m_simulator_end_func;
			public:
				Viewer(const std::string& dll_filename) : m_dll_filename(dll_filename) {

				}
				// シミュレータ開始時に実行される関数
				// @param conf: シミュレータの設定
				virtual void onSimulatorBegin(const Config& conf) override {
					m_simulator_begin_func(conf);
				}
				// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
				// @param param_name:	シミュレーション設定の名前
				// @param param:		シミュレーション設定
				virtual void onSimulationsBegin(
					const std::string& param_name,
					const std::unordered_map<std::string, std::string>& param) override {
					m_simulations_begin_func(param_name, param);
				}
				// シミュレーションが開始する毎に実行される関数
				// @param current_trial_number: 現在の試行回数
				virtual void onSimulationBegin(const unsigned int current_trial_number) override {
					m_simulation_begin_func(current_trial_number);
				}
				// シミュレーションが終了する毎に実行される関数
				// @param result: シミュレーション結果
				virtual void onSimulationEnd(const std::unordered_map<std::string, std::string>& result) override {
					m_simulation_end_func(result);
				}
				// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
				// @param results: 試行回数分のシミュレーション結果
				virtual void onSimulationsEnd(const std::vector<std::unordered_map<std::string, std::string>>& results) override {
					m_simulations_end_func(results);
				}
				// シミュレータ終了時に実行される関数
				virtual void onSimulatorEnd() override {
					m_simulator_end_func();
				}
				void init();
				void terminate();
			};
			class Viewers : public IViewer {
			private:
				std::vector<Viewer> m_viewers;
			public:
				Viewers(const Config& conf)
				{
					for (const auto& dll_filename : conf.m_output_dlls_filename)
					{
						m_viewers.emplace_back(dll_filename);
					}
				}
				// シミュレータ開始時に実行される関数
				// @param conf: シミュレータの設定
				virtual void onSimulatorBegin(const Config& conf) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulatorBegin(conf);
					}
				}
				// ある一つのシミュレーション設定下でのシミュレーションが開始するタイミングで実行される関数
				// @param param_name:	シミュレーション設定の名前
				// @param param:		シミュレーション設定
				virtual void onSimulationsBegin(
					const std::string& param_name,
					const std::unordered_map<std::string, std::string>& param) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationsBegin(param_name, param);
					}
				}
				// シミュレーションが開始する毎に実行される関数
				// @param current_trial_number: 現在の試行回数
				virtual void onSimulationBegin(const unsigned int current_trial_number) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationBegin(current_trial_number);
					}
				}
				// シミュレーションが終了する毎に実行される関数
				// @param result: シミュレーション結果
				virtual void onSimulationEnd(const std::unordered_map<std::string, std::string>& result) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationEnd(result);
					}
				}
				// ある一つのパラメータ環境下でのシミュレーションが終了するタイミングで実行される関数
				// @param results: 試行回数分のシミュレーション結果
				virtual void onSimulationsEnd(const std::vector<std::unordered_map<std::string, std::string>>& results) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationsEnd(results);
					}
				}
				// シミュレータ終了時に実行される関数
				virtual void onSimulatorEnd() override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulatorEnd();
					}
				}
				void init();
				void terminate();
			};
		public:
			// シミュレータのインスタンス
			// @param conf:シミュレーター全体に関わる設定
			// @param param_table:シミュレーターで行うパラメータを一覧にしたテーブルオブジェクト
			Simulator(const Config& conf, const table::Table& param_table)
				: m_conf(conf), m_param_table(param_table) {

			}
			void run();
		};
	}
}