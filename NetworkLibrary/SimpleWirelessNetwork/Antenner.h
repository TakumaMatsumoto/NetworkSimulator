#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include "geo.h"
#include "Message.h"

namespace sim {
	namespace swn {
		/*
			�[���ɕt������A���e�i��\��
			����d�͗ʂ��Z�o����
		*/
		class Antenner {
		private:
			// 1bit�̃f�[�^��ʐM����ۂ̏���d��(J/bit)
			double m_Eelec;
			// 1bit�̃f�[�^��1m�������M����ۂɎg�p����鑝����̏���d��(J/bit�Em^2)
			double m_Emp;
		public:
			// @param Eelec: 1bit�̃f�[�^��ʐM����ۂ̏���d��(J/bit)
			// @param Emp:   1bit�̃f�[�^��1m�������M����ۂɎg�p����鑝����̏���d��(J/bit�Em^2)
			Antenner(const double Eelec, const double Emp) 
				: m_Eelec(Eelec), m_Emp(Emp) {

			}
			// ���M
			// �߂�l�F����G�l���M�[[J]
			// @param source: ���M���̈ʒu
			// @param target: ���M��̈ʒu
			// @param message: ���M���郁�b�Z�[�W
			double sendTo(
				const geo::Point<double>& source,
				const geo::Point<double>& target,
				const IMessage& message) {
				return 
					m_Eelec * message.getSize() + 
					m_Emp	* message.getSize() * pow(source.distanceTo(target), 2.0);
			}
			// ��M
			// �߂�l�F����G�l���M�[[J]
			// @param message: ��M���郁�b�Z�[�W
			double receive(const IMessage& message) {
				return m_Eelec * message.getSize();
			}
		};
	}
}