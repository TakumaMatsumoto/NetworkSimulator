#pragma once
namespace sim {
	namespace swn {
		/*
			�o�b�e���[�N���X
			�R������ꂽ��������ł���
		*/
		class Battery {
		private:
			// �����G�l���M�[[J]
			double m_initial_energy;
			// �c��G�l���M�[[J]
			double m_left_energy;
		public:

			Battery(const double initial_energy)
				: m_initial_energy(initial_energy), m_left_energy(initial_energy) {

			}
			// �R���𓊓�����
			// @param energy: ������[J]
			void fuel(const double energy) {
				m_left_energy += energy;
			}
			// �R���������
			// @param energy: �����[J]
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
