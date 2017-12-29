#pragma once
namespace sim {
	namespace swn {
		// �e�哮��ɕK�v�ȓd�͗ʂ��߂��N���X
		class EnergyConsumption {
		public:
			// 1m������̏���d��[J/m]
			double m_moving = 0.0;
			// 1bit�̃f�[�^��ʐM����ۂ̏���d��[J/bit]
			double m_communication_per_bit = 0.0;
			// 1bit�̃f�[�^��1m�������M����ۂɎg�p����鑝����̏���d��[J/(bit�Em^2)]
			double m_transmission_per_bit = 0.0;
			EnergyConsumption(
				const double moving,
				const double communication_per_bit,
				const double transmission_per_bit)
				: m_moving(moving), m_communication_per_bit(communication_per_bit), m_transmission_per_bit(transmission_per_bit) {

			}
			EnergyConsumption() = default;
		};
	}
}