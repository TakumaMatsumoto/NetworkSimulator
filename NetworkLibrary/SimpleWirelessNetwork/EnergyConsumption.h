#pragma once
namespace sim {
	namespace swn {
		// 各主動作に必要な電力量を定めたクラス
		class EnergyConsumption {
		public:
			// 1mあたりの消費電力[J/m]
			double m_moving = 0.0;
			// 1bitのデータを通信する際の消費電力[J/bit]
			double m_communication_per_bit = 0.0;
			// 1bitのデータを1mだけ送信する際に使用される増幅器の消費電力[J/(bit・m^2)]
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