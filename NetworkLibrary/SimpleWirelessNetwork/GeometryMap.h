#pragma once
#include <memory>
#include "INode.h"

namespace sim {
	namespace swn {
		/*
			全ノードの位置、レールの情報、センシングメッセージ
			などの空間情報を集めたマップ
		*/
		class GeometryMap {
		private:
			const Message m_default_message;
			std::vector<Rail> m_rails;
			std::vector<std::weak_ptr<INode>> m_nodes;
		public:
			GeometryMap(
				const Message& default_message,
				const std::vector<Rail>& rails,
				const std::vector<std::weak_ptr<INode>>& nodes) : 
				m_default_message(default_message), m_rails(rails), m_nodes(nodes) {
			}
			void update() {

			}
			std::vector<Rail> getRails() const {
				return m_rails;
			}
			// 引数で与えられたノードからみて最も近いレールを取得する
			// @param node: ノード
			Rail searchTheClosestRail(const INode& node) const {
				unsigned int ret = 0;
				double min_distance = DBL_MAX;
				for (unsigned int i = 0, length = static_cast<unsigned int>(m_rails.size()); i < length; i++)
				{
					const double dis = m_rails[i].distanceTo(node.getPosition());
					if (min_distance < dis) continue;
					min_distance = dis;
					ret = i;
				}
				return m_rails[ret];
			}
			std::weak_ptr<INode> searchBaseNode() const {
				for (const auto& node : m_nodes)
				{
					if (node.lock()->getSegmentID() == 0) return node;
				}
				throw std::exception("can't find base node");
			}

			// 引数で与えられたレールと距離が近いノードのリストを取得する
			// @param rail: レール
			std::vector<std::weak_ptr<INode>> searchNodesCloseToRail(const Rail& rail) const {
				std::vector<std::weak_ptr<INode>> ret;
				for (const auto& node : m_nodes)
				{
					// セグメントIDが0のとき基地局なのでスルー
					if (node.lock()->getSegmentID() == 0) continue;
					if (rail.getUID() == searchTheClosestRail(*node.lock()).getUID()) ret.push_back(node);
				}
				return ret;
			}
			// 引数で与えられたノードがセンシング可能な範囲内にメッセージが存在する場合、メッセージをとってくる
			// 現在はどの場合であってもメッセージを取得するようにしてある
			Message fetchMessage(const INode& node) const {
				return m_default_message.clone();
			}
		};
	}
}