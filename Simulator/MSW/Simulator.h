#pragma once
#include <Windows.h>
#include "SimulatorLibrary\Table.h"
#include "SimulatorLibrary\Config.h"
#include "SimulatorLibrary\ISimulation.h"
#include "SimulatorLibrary\ISimulationObserver.h"
#include "Config.h"
#include "SimulatorLibrary\IFactory.h"

namespace sim
{
	namespace msw {
		class Simulator{
		private:
			const msw::Config m_conf;
			/*
				DLLから関数を呼び出してインスタンスを生成する担当
			*/
			template<typename T>
			class DLLInstanceFactory : public IFactory<T> {
			private:
				HMODULE m_lib_handle;
				const std::string m_dll_filename;
				// インスタンス生成のDLL関数
				// @param
				// param_map: パラメータのハッシュマップ(key: パラメータ名, value: パラメータ値(string))
				using CREATE_INSTANCE_FUNC = T*(*)(const sim::Parameter& param_map);
				CREATE_INSTANCE_FUNC m_func;
			public:
				DLLInstanceFactory(const std::string& dll_filename) : m_dll_filename(dll_filename) {

				}
				T* createInstance(const sim::Parameter& param_map) override {
					return m_func(param_map);
				}
				void init() override {
					m_lib_handle = LoadLibraryA(m_dll_filename.c_str());
					if (m_lib_handle == NULL) {
						throw std::exception(std::string(m_dll_filename + "\n" + "DLL file for simulation not found").c_str());
					}
					m_func = reinterpret_cast<CREATE_INSTANCE_FUNC>(GetProcAddress(m_lib_handle, "CreateInstance"));
					if (m_func == NULL) {
						throw std::exception(std::string(m_dll_filename + "\n" + "CreateInstance function not found").c_str());
					}
				}
				void terminate() override {
					if (m_lib_handle != NULL) FreeLibrary(m_lib_handle);
				}
			};
		public:
			// シミュレータのインスタンス
			// @param conf:シミュレーター全体に関わる設定
			Simulator(const msw::Config& conf) : m_conf(conf){
			}
			int run() const;
		};
	}
}