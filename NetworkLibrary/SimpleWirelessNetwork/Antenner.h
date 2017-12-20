#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include "geo.h"
#include "Message.h"

namespace sim {
	namespace swn {
		/*
			端末に付属するアンテナを表す
			消費電力量を算出する
		*/
		class Antenner {
		private:
			// 1bitのデータを通信する際の消費電力(J/bit)
			double m_Eelec;
			// 1bitのデータを1mだけ送信する際に使用される増幅器の消費電力(J/bit・m^2)
			double m_Emp;
		public:
			// @param Eelec: 1bitのデータを通信する際の消費電力(J/bit)
			// @param Emp:   1bitのデータを1mだけ送信する際に使用される増幅器の消費電力(J/bit・m^2)
			Antenner(const double Eelec, const double Emp) 
				: m_Eelec(Eelec), m_Emp(Emp) {

			}
			// 送信
			// 戻り値：消費エネルギー[J]
			// @param source: 送信元の位置
			// @param target: 送信先の位置
			// @param message: 送信するメッセージ
			double sendTo(
				const geo::Point<double>& source,
				const geo::Point<double>& target,
				const IMessage& message) {
				return 
					m_Eelec * message.getSize() + 
					m_Emp	* message.getSize() * pow(source.distanceTo(target), 2.0);
			}
			// 受信
			// 戻り値：消費エネルギー[J]
			// @param message: 受信するメッセージ
			double receive(const IMessage& message) {
				return m_Eelec * message.getSize();
			}
		};
	}
}