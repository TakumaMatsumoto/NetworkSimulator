#pragma once
#include <memory>
#include "Config.h"
#include "ISimulation.h"
#include "IViewer.h"
#include "IFactory.h"
#include "Table.h"
#include <functional>

namespace sim {
	/*
		シミュレーションオブジェクトやビューアオブジェクトを生成するためのオブジェクトを作る役割を担当する

	*/
	class RunnableEnvironmentFactory {
		const std::unique_ptr<IFactory<ISimulation>> mp_simulation_factory;
		const std::unique_ptr<IFactory<IViewer>> mp_viewer_factory;
	public:
		RunnableEnvironmentFactory(
			IFactory<ISimulation>* const p_simulation_factory,
			IFactory<IViewer>* const p_viewer_factory):
		mp_simulation_factory(p_simulation_factory), mp_viewer_factory(p_viewer_factory){

		}
		ISimulation* createSimulationInstance(const std::unordered_map<std::string, std::string>& param_map) const {
			return mp_simulation_factory->createInstance(param_map);
		}
		IViewer* createViewerInstance(const std::unordered_map<std::string, std::string>& param_map) const {
			return mp_viewer_factory->createInstance(param_map);
		}
		void init() {
			mp_simulation_factory->init();
			mp_viewer_factory->init();
		}
		void terminate() {
			mp_simulation_factory->terminate();
			mp_viewer_factory->terminate();
		}
	};

	/*
		シミュレーションの実行から結果表示までを担当する
	*/
	class Simulator{
	private:
		using SuccessNumber = int;
		using ErrorNumber = int;
		const std::unique_ptr<RunnableEnvironmentFactory> mp_runnable_environment_factory;
		const Config m_conf;
		const std::pair<SuccessNumber, ErrorNumber> m_return_numbers;
		const std::function<void(const std::exception& ex)> m_exception_function;
	public:
		Simulator(
			RunnableEnvironmentFactory* const p_runnable_environment_factory, 
			const Config& conf,
			const std::pair<SuccessNumber, ErrorNumber>& return_numbers,
			const std::function<void(const std::exception& ex)>& exception_function = [](const std::exception& ex){}) :
			mp_runnable_environment_factory(p_runnable_environment_factory), 
			m_conf(conf), m_return_numbers(return_numbers),
			m_exception_function(exception_function){
		}
		int run() const{
			try {
				// シミュレータ、ビューアファクトリーの初期化処理
				mp_runnable_environment_factory->init();

				const std::unique_ptr<IViewer> p_viewer(mp_runnable_environment_factory->createViewerInstance(m_conf.toMap()));
				// シミュレータを動かす
				p_viewer->onSimulatorBegin(m_conf);
				// パラメータ表から一行ずつパラメータを取り出す
				for (const auto& row_head : m_conf.m_param_table.getRowHeaders())
				{
					const auto param = m_conf.m_param_table.getRow(row_head);
					p_viewer->onSimulationsBegin(row_head, param);
					std::vector<std::unordered_map<std::string, std::string>> results(m_conf.m_number_of_trials);
					// 試行回数分、シミュレーションを行い、結果を出力する
					for (unsigned int i = 0; i < m_conf.m_number_of_trials; i++)
					{
						p_viewer->onSimulationBegin(i);
						const auto result = std::unique_ptr<sim::ISimulation>(
							mp_runnable_environment_factory->
							createSimulationInstance(param))->run();
						results.at(i) = result;
						p_viewer->onSimulationEnd(result);
					}
					p_viewer->onSimulationsEnd(results);
				}
				p_viewer->onSimulatorEnd();
			}
			catch (const std::exception& ex) {
				m_exception_function(ex);
				mp_runnable_environment_factory->terminate();
				return m_return_numbers.second;
			}
			mp_runnable_environment_factory->terminate();
			return m_return_numbers.first;
		}
	};
}