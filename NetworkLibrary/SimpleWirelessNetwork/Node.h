#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Space.h"
#include "Antenner.h"
#include "Battery.h"
#include "geo.h"
#include "INode.h"

namespace sim {
	namespace swn {
		class SensorNode : public INode {
		private:
			// センシングにより得られたメッセージ
			std::shared_ptr<IMessage> mp_sensored_message;
			// 初期位置
			const geo::Point<double> m_initial_position;
			// 現在位置
			geo::Point<double> m_position;
			// 通信可能範囲
			double m_transmission_range;
			// バッテリー
			Battery m_battery;
			// アンテナ
			Antenner m_antenner;
		public:
			SensorNode(
				const geo::Point<double>& position,
				const double transmission_range,
				const Battery& battery,
				const Antenner& antenner) : 
				m_initial_position(position), m_position(position),
				m_transmission_range(transmission_range), m_battery(battery), m_antenner(antenner){
			}
			virtual geo::Point<double> getPosition() const {
				return m_position;
			}
			virtual IMessage& collectMessage() override {

			}
			// 空間情報からメッセージのコピーを取得する
			void sensing(const Space& space){
				mp_sensored_message.reset(space.getMessage().createClone());
			}
			// 引数で与えられたノードのリストから送信元ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// 引数で与えられたノードのリストから送信先ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// 生存フラグ
			virtual bool isAlive() const {
				return m_battery.isAlive();
			}
		};
		class SensorNodes {
		private:
			std::vector<std::shared_ptr<SensorNode>> m_nodes;
		public:
			std::vector<std::shared_ptr<INode>> getNodes() const {
				std::vector<std::shared_ptr<INode>> ret;
				for (const auto& node : m_nodes)
				{
					ret.push_back(node);
				}
				return ret;
			}
			void add(const std::shared_ptr<SensorNode>& node) { m_nodes.push_back(node); }
			// 全ノードが生きているかを判定
			bool areAlive() const {
				return !includeDeadOne();
			}
			// 空間情報からメッセージのコピーを取得する
			void sensing(const Space& space) {
				for (const auto& snode : m_nodes)
				{
					snode->sensing(space);
				}
			}
			// 引数で与えられたノードのリストから送信元ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes){
				for (const auto& node : m_nodes)
				{
					node->searchSender(nodes);
				}
			}
			// 引数で与えられたノードのリストから送信先ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes){
				for (const auto& node : m_nodes)
				{
					node->searchReceiver(nodes);
				}
			}
			// 一つのノードが死んでいるかを判定
			bool includeDeadOne() const {
				return std::any_of(m_nodes.begin(), m_nodes.end(), [](const std::shared_ptr<INode>& node) { return !node->isAlive(); });
			}
			// あるノードが生きているかを判定
			bool includeAliveOne() const {
				return std::any_of(m_nodes.begin(), m_nodes.end(), [](const std::shared_ptr<INode>& node) { return node->isAlive(); });
			}
		};
		class BaseNode : public INode {
		private:

			// 現在位置
			const geo::Point<double> m_position;
		public:
			BaseNode(const geo::Point<double>& position)
				: m_position(position) {
			}
			virtual geo::Point<double> getPosition() const {
				return m_position;
			}
			virtual IMessage& collectMessage() override {

			}
			// 引数で与えられたノードのリストから送信元ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// 引数で与えられたノードのリストから送信先ノードを探す
			// @param nodes: 捜査対象のノードリスト
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// 生存フラグ
			virtual bool isAlive() const {
				return true;
			}
		};
	}
}