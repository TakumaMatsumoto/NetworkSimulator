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
		�V�~�����[�V�����I�u�W�F�N�g��r���[�A�I�u�W�F�N�g�𐶐����邽�߂̃I�u�W�F�N�g����������S������

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
		�V�~�����[�V�����̎��s���猋�ʕ\���܂ł�S������
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
				// �V�~�����[�^�A�r���[�A�t�@�N�g���[�̏���������
				mp_runnable_environment_factory->init();

				const std::unique_ptr<IViewer> p_viewer(mp_runnable_environment_factory->createViewerInstance(m_conf.toMap()));
				// �V�~�����[�^�𓮂���
				p_viewer->onSimulatorBegin(m_conf);
				// �p�����[�^�\�����s���p�����[�^�����o��
				for (const auto& row_head : m_conf.m_param_table.getRowHeaders())
				{
					const auto param = m_conf.m_param_table.getRow(row_head);
					p_viewer->onSimulationsBegin(row_head, param);
					std::vector<std::unordered_map<std::string, std::string>> results(m_conf.m_number_of_trials);
					// ���s�񐔕��A�V�~�����[�V�������s���A���ʂ��o�͂���
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