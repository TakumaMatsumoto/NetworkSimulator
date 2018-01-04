#pragma once
#include <stack>
#include "Message.h"
#include "geo.h"

namespace sim {
	namespace swn {
		class INode {
		public:
			virtual ~INode() = default;
			// 固有IDを取得する
			virtual unsigned int getUID() const = 0;
			// 
			virtual INode& getReceiver() = 0;
			// 現在位置を取得する
			virtual geo::Point<double> getPosition() const = 0;
			// 送信元ノードを探す
			virtual void searchSender() = 0;
			// 送信先ノードを探す
			virtual void searchReceiver() = 0;
			// メッセージを収集する
			// return: メッセージ
			virtual std::shared_ptr<IMessage> collectMessage() = 0;
			// 生存フラグ
			virtual bool isAlive() const = 0;
			// セグメント番号を取得する
			virtual unsigned int getSegmentID() const = 0;
			// 通信可能領域を取得する
			virtual geo::Circle<double> getTransmittableArea() const = 0;
		};
	}
}