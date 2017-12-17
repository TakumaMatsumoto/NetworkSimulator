#pragma once
#include <Windows.h>
#include "Table.h"
#include "Config.h"
#include "ISimulation.h"
#include "ISimulationObserver.h"
#include "MSWConfig.h"
#include "IFactory.h"

namespace sim
{
	namespace msw {
		class Simulator{
		private:
			const msw::Config m_conf;
			/*
				DLL����֐����Ăяo���ăC���X�^���X�𐶐�����S��
			*/
			template<typename T>
			class DLLInstanceFactory : public IFactory<T> {
			private:
				HMODULE m_lib_handle;
				const std::string m_dll_filename;
				// �C���X�^���X������DLL�֐�
				// @param
				// param_map: �p�����[�^�̃n�b�V���}�b�v(key: �p�����[�^��, value: �p�����[�^�l(string))
				using CREATE_INSTANCE_FUNC = T*(*)(const std::unordered_map<std::string, std::string>& param_map);
				CREATE_INSTANCE_FUNC m_func;
			public:
				DLLInstanceFactory(const std::string& dll_filename) : m_dll_filename(dll_filename) {

				}
				T* createInstance(const std::unordered_map<std::string, std::string>& param_map) override {
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
			// �V�~�����[�^�̃C���X�^���X
			// @param conf:�V�~�����[�^�[�S�̂Ɋւ��ݒ�
			Simulator(const msw::Config& conf) : m_conf(conf){
			}
			int run() const;
		};
	}
}