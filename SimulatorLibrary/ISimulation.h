#pragma once
#include <unordered_map>
#include <string>
#include "IRunnable.h"

namespace sim
{
	class ISimulation {
	public:
		virtual ~ISimulation() = default;
		// �V�~�����[�V�����̃C���X�^���X���쐬���܂�
		// @param param_map: �p�����[�^����key,�l��value�Ƃ����n�b�V���}�b�v
		virtual sim::IRunnable* createInstance(const std::unordered_map<std::string, std::string>& param_map) = 0;
	};
}