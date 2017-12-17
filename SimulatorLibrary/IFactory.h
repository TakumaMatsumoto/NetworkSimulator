#pragma once
#include <unordered_map>
#include <string>

namespace sim {
	template<typename T>
	class IFactory {
	public:
		virtual ~IFactory() = default;
		// �C���X�^���X���쐬����
		// @param param_map: �p�����[�^����key,�l��value�Ƃ����n�b�V���}�b�v
		virtual T* createInstance(const std::unordered_map<std::string, std::string>& param_map) = 0;
		virtual void init() = 0;
		virtual void terminate() = 0;
	};
}