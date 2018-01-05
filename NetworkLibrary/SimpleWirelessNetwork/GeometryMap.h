#pragma once
#include <memory>
#include <algorithm>
#include "INode.h"
#include "Obstacle.h"

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
			std::vector<Obstacle> m_obstacles;
			std::vector<std::weak_ptr<INode>> m_nodes;
		public:
			GeometryMap(
				const Message& default_message,
				const std::vector<Rail>& rails,
				const std::vector<Obstacle>& obstacles,
				const std::vector<std::weak_ptr<INode>>& nodes) : 
				m_default_message(default_message), m_rails(rails), m_obstacles(obstacles), m_nodes(nodes) {
			}
			void update() {
				m_nodes.erase(std::remove_if(m_nodes.begin(), m_nodes.end(),
					[](const std::weak_ptr<INode>& p_node) { return !p_node.lock()->isAlive(); }), m_nodes.end());
			}
			size_t getNumberOfNodes() const {
				return m_nodes.size();
			}
			std::vector<Rail> getRails() const {
				return m_rails;
			}
			// 引数で与えられた位置からみて近い順にしてレールを取得する
			// @param pos: 位置情報
			std::vector<Rail> orderRailsByDistance(const geo::Point<double>& pos) const {
				auto ret = getRails();
				const auto sort_func = [&pos](const Rail& l, const Rail& r) {
					return l.distanceTo(pos) < r.distanceTo(pos);
				};
				std::sort(ret.begin(), ret.end(), sort_func);
				return ret;
			}
			std::vector<Obstacle> searchObstaclesOnRail(const Rail& rail) const {
				std::vector<Obstacle> ret;
				const auto line = rail.getLine();
				for (const auto& target : m_obstacles)
				{
					if(target.closeTo(line)) ret.push_back(target);
				}
				return ret;
			}
			std::weak_ptr<INode> searchBaseNode() const {
				for (const auto& node : m_nodes)
				{
					if (node.lock()->getSegmentID() == 0) return node;
				}
				throw std::exception("can't find base node");
			}

			// 引数で与えられたレールと距離が近いノードのリストを取得する
			// なお、基地局は除かれる
			// @param rail: レール
			std::vector<std::weak_ptr<INode>> searchNodesCloseToRail(const Rail& rail) const {
				std::vector<std::weak_ptr<INode>> ret;
				for (const auto& node : m_nodes)
				{
					const auto closest_rail = orderRailsByDistance(node.lock()->getPosition())[0];
					// セグメントIDが0のとき基地局なのでスルー
					if (node.lock()->getSegmentID() == 0) continue;
					if (rail.getUID() == closest_rail.getUID()) ret.push_back(node);
				}
				return ret;
			}
			std::vector<std::weak_ptr<INode>> searchNodesBetween(const Rail& rail, const std::pair<geo::Point<double>, geo::Point<double>>& p_pair) const {
				std::vector<std::weak_ptr<INode>> ret;
				geo::Rectangle<double> rect(p_pair.first, p_pair.second.x - p_pair.first.x, p_pair.second.y - p_pair.first.y);
				for (const auto& node : searchNodesCloseToRail(rail))
				{
					if (rect.include(node.lock()->getPosition())) ret.push_back(node);
				}
				return ret;
			}
			std::vector<Obstacle> searchObstaclesBetween(const Rail& rail, const std::pair<geo::Point<double>, geo::Point<double>>& p_pair) const {
				std::vector<Obstacle> ret;
				geo::Rectangle<double> rect(p_pair.first, p_pair.second.x - p_pair.first.x, p_pair.second.y - p_pair.first.y);
				for (const auto& obstacle : searchObstaclesOnRail(rail)){
					if (rect.include(obstacle.getPosition())) {
						ret.push_back(obstacle);
					}
				}
				return ret;
			}
			std::vector<std::weak_ptr<INode>> getNodes() const {
				return m_nodes;
			}
			// 引数で与えられたノードがセンシング可能な範囲内にメッセージが存在する場合、メッセージをとってくる
			// 現在はどの場合であってもメッセージを取得するようにしてある
			Message fetchMessage(const geo::Point<double>& pos) const {
				return m_default_message.clone();
			}
		};
	}
}