#pragma once
namespace sim {
	namespace swn {
		/*
			バッテリークラス
			燃料を入れたり消費したりできる
		*/
		class Battery {
		private:
			// 初期エネルギー[J]
			double m_initial_energy;
			// 残りエネルギー[J]
			double m_left_energy;
		public:

			Battery(const double initial_energy)
				: m_initial_energy(initial_energy), m_left_energy(initial_energy) {

			}
			// 燃料を投入する
			// @param energy: 投入量[J]
			void fuel(const double energy) {
				m_left_energy += energy;
			}
			// 燃料を消費する
			// @param energy: 消費量[J]
			void consume(const double energy) {
				m_left_energy -= energy;
			}
			double getLeftEnergy() const { return m_left_energy; }
			double getInitialEnergy() const { return m_initial_energy; }
			bool isAlive() const {
				return m_left_energy > 0.0;
			}
			bool isDead() const {
				return !isAlive();
			}
		};
	}
}
