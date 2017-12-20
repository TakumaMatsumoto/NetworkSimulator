#pragma once
#include <memory>
#include <vector>
#include "Message.h"
#include "geo.h"

namespace sim {
	namespace swn {
		class INode {
		public:
			virtual ~INode() = default;
			// 現在位置を取得する
			virtual geo::Point<double> getPosition() const = 0;
			// 引数で与えられたノードのリストから送信元ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes) = 0;
			// 引数で与えられたノードのリストから送信先ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes) = 0;
			// メッセージを収集する
			// return: メッセージ
			virtual IMessage& collectMessage() = 0;
			// 生存フラグ
			virtual bool isAlive() const = 0;
		};
	}
}