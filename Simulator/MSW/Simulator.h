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
				// �V�~�����[�V�����������֐��̌^
				// @param
				// param_map: �p�����[�^�̃n�b�V���}�b�v(key: �p�����[�^��, value: �p�����[�^�l(string))
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
				// �V�~�����[�^�J�n���Ɏ��s�����֐��̌^
				// @param
				// conf: �V�~�����[�^�̐ݒ�
				using ON_SIMULATOR_BEGIN_FUNC = void(*)(const Config& conf);
				// �����̃p�����[�^�����ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐��̌^
				// @param
				// param_name: ���s��������̖��O
				// param: ���s�������
				using ON_SIMULATIONS_BEGIN_FUNC = void(*)(const std::string& param_name, const std::unordered_map<std::string, std::string>& param);
				// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐��̌^
				// @param
				// current_trial_number: ���݂̎��s��
				using ON_SIMULATION_BEGIN_FUNC = void(*)(const unsigned int current_trial_number);
				// �V�~�����[�V�������I�����閈�Ɏ��s�����֐��̌^
				// @param
				// result: �V�~�����[�V��������
				using ON_SIMULATION_END_FUNC = void(*)(const std::unordered_map<std::string, std::string>& result);
				// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐��̌^
				// @param
				// results: ���s�񐔕��̃V�~�����[�V��������
				using ON_SIMULATIONS_END_FUNC = void(*)(const std::vector<std::unordered_map<std::string, std::string>>& results);
				// �V�~�����[�^�I�����Ɏ��s�����֐��̌^
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
				// �V�~�����[�^�J�n���Ɏ��s�����֐�
				// @param conf: �V�~�����[�^�̐ݒ�
				virtual void onSimulatorBegin(const Config& conf) override {
					m_simulator_begin_func(conf);
				}
				// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
				// @param param_name:	�V�~�����[�V�����ݒ�̖��O
				// @param param:		�V�~�����[�V�����ݒ�
				virtual void onSimulationsBegin(
					const std::string& param_name,
					const std::unordered_map<std::string, std::string>& param) override {
					m_simulations_begin_func(param_name, param);
				}
				// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
				// @param current_trial_number: ���݂̎��s��
				virtual void onSimulationBegin(const unsigned int current_trial_number) override {
					m_simulation_begin_func(current_trial_number);
				}
				// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
				// @param result: �V�~�����[�V��������
				virtual void onSimulationEnd(const std::unordered_map<std::string, std::string>& result) override {
					m_simulation_end_func(result);
				}
				// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
				// @param results: ���s�񐔕��̃V�~�����[�V��������
				virtual void onSimulationsEnd(const std::vector<std::unordered_map<std::string, std::string>>& results) override {
					m_simulations_end_func(results);
				}
				// �V�~�����[�^�I�����Ɏ��s�����֐�
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
				// �V�~�����[�^�J�n���Ɏ��s�����֐�
				// @param conf: �V�~�����[�^�̐ݒ�
				virtual void onSimulatorBegin(const Config& conf) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulatorBegin(conf);
					}
				}
				// �����̃V�~�����[�V�����ݒ艺�ł̃V�~�����[�V�������J�n����^�C�~���O�Ŏ��s�����֐�
				// @param param_name:	�V�~�����[�V�����ݒ�̖��O
				// @param param:		�V�~�����[�V�����ݒ�
				virtual void onSimulationsBegin(
					const std::string& param_name,
					const std::unordered_map<std::string, std::string>& param) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationsBegin(param_name, param);
					}
				}
				// �V�~�����[�V�������J�n���閈�Ɏ��s�����֐�
				// @param current_trial_number: ���݂̎��s��
				virtual void onSimulationBegin(const unsigned int current_trial_number) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationBegin(current_trial_number);
					}
				}
				// �V�~�����[�V�������I�����閈�Ɏ��s�����֐�
				// @param result: �V�~�����[�V��������
				virtual void onSimulationEnd(const std::unordered_map<std::string, std::string>& result) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationEnd(result);
					}
				}
				// �����̃p�����[�^�����ł̃V�~�����[�V�������I������^�C�~���O�Ŏ��s�����֐�
				// @param results: ���s�񐔕��̃V�~�����[�V��������
				virtual void onSimulationsEnd(const std::vector<std::unordered_map<std::string, std::string>>& results) override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulationsEnd(results);
					}
				}
				// �V�~�����[�^�I�����Ɏ��s�����֐�
				virtual void onSimulatorEnd() override {
					for (auto& viewer : m_viewers) {
						viewer.onSimulatorEnd();
					}
				}
				void init();
				void terminate();
			};
		public:
			// �V�~�����[�^�̃C���X�^���X
			// @param conf:�V�~�����[�^�[�S�̂Ɋւ��ݒ�
			// @param param_table:�V�~�����[�^�[�ōs���p�����[�^���ꗗ�ɂ����e�[�u���I�u�W�F�N�g
			Simulator(const Config& conf, const table::Table& param_table)
				: m_conf(conf), m_param_table(param_table) {

			}
			void run();
		};
	}
}