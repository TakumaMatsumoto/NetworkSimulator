#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Antenner.h"
#include "Battery.h"
#include "geo.h"
#include "INode.h"
#include "GeometryMap.h"

namespace sim {
	namespace swn {
		class SensorNode : public INode {
		private:
			// 固有ID
			const unsigned int m_UID;
			// 自身にメッセージを送信するノード
			std::weak_ptr<INode> mp_sender_node;
			// 自身のメッセージを送信するノード
			std::weak_ptr<INode> mp_receiver_node;
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
			// マップ情報
			std::weak_ptr<GeometryMap> mp_gmap;
		public:
			SensorNode(
				const unsigned int UID,
				const geo::Point<double>& position,
				const double transmission_range,
				const Battery& battery,
				const Antenner& antenner) : 
				m_UID(UID), m_initial_position(position), m_position(position),
				m_transmission_range(transmission_range), m_battery(battery), m_antenner(antenner){
			}
			virtual unsigned int getUID() const override {
				return m_UID;
			}
			virtual unsigned int getSegmentID() const override {
				return 1;
			}
			virtual geo::Point<double> getPosition() const override {
				return m_position;
			}
			virtual std::shared_ptr<IMessage> collectMessage() override {
				if (mp_sender_node.lock() == nullptr) {
					m_battery.consume(m_antenner.sendTo(m_position, mp_receiver_node.lock()->getPosition(), *mp_sensored_message));
					return mp_sensored_message;
				}
				// 自身にメッセージを送信するノードが存在するときは受信処理を行う
				// メッセージ受信
				const auto recv_msg = mp_sender_node.lock()->collectMessage();
				m_battery.consume(m_antenner.receive(*recv_msg));
				// メッセージ生成&送信
				const std::shared_ptr<IMessage> send_msg(new Messages({recv_msg, mp_sensored_message}));
				m_battery.consume(m_antenner.sendTo(m_position, mp_receiver_node.lock()->getPosition(), *send_msg));
				return send_msg;
			}
			// メッセージを取得する
			void sensing(){
				mp_sensored_message = std::shared_ptr<Message>(new Message(mp_gmap.lock()->fetchMessage(*this)));
			}
			// 元の位置に戻る
			void returnToInitialPosition() {
				// 最も近いレールを探索
				const auto my_rail = mp_gmap.lock()->searchTheClosestRail(*this);
				// 初期位置からみたレール上の最短距離となる点へ移動
				const auto new_position = my_rail.getClosestCoordinate(m_initial_position);
				m_position = new_position;
				// 初期位置へ戻る
				m_position = m_initial_position;
			}
			// 送信元ノードを探す
			virtual void searchSender() override {
				const auto p_gmap = mp_gmap.lock();
				// 最も近いレールを探索
				const auto my_rail = p_gmap->searchTheClosestRail(*this);
				// 自身のレールと同じレール上にあるノードを選び出す
				const auto nodes_on_my_rail = p_gmap->searchNodesCloseToRail(my_rail);
				mp_sender_node = [&nodes_on_my_rail, &p_gmap](const unsigned int myUID) {
					// nodesは基地局に近い順に並んでいるので
					// 走査中のノードのUIDが自身のUIDと同じかつiがlength-1の時は送信元は存在しない(自分自身を返すようにする)
					// 走査中のノードのUIDが自身のUIDと同じかつiがlength-1以外の時はi+1が送信元ノードになる
					for (int i = 0, length = nodes_on_my_rail.size(); i < length; i++)
					{
						const auto& node = nodes_on_my_rail[i];
						if (node.lock()->getUID() == myUID && i == length - 1) return node;
						if (node.lock()->getUID() == myUID) return nodes_on_my_rail[i + 1];
					}
					throw std::exception("can't find receiver");
				}(m_UID);

			}
			// 送信先ノードを探す(移動有)
			virtual void searchReceiver() override {
				const auto p_gmap = mp_gmap.lock();
				// 最も近いレールを探索
				const auto my_rail = p_gmap->searchTheClosestRail(*this);
				// レール上に移動する
				const auto new_position = my_rail.getClosestCoordinate(m_initial_position);
				m_position = new_position;
				// 自身のレールと同じレール上にあるノードを選び出す
				const auto nodes_on_my_rail = p_gmap->searchNodesCloseToRail(my_rail);
				mp_receiver_node = [&nodes_on_my_rail, &p_gmap](const unsigned int myUID) {
					// nodesは基地局に近い順に並んでいるので
					// 走査中のノードのUIDが自身のUIDと同じかつiが0以外の時はi-1が送信先ノードになる
					// 走査中のノードのUIDが自身のUIDと同じかつiが0の時はbasenodeが送信先ノードになる
					for (int i = 0, length = nodes_on_my_rail.size(); i < length; i++)
					{
						const auto& node = nodes_on_my_rail[i];
						if (node.lock()->getUID() == myUID && i == 0) return p_gmap->searchBaseNode();
						if (node.lock()->getUID() == myUID && i != 0) return nodes_on_my_rail[i - 1];
					}
					throw std::exception("can't find receiver");
				}(m_UID);
				// TODO::送信先ノードと接続できる範囲まで移動
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gps) {
				mp_gmap = p_gps;
			}
			// 生存フラグ
			virtual bool isAlive() const {
				return m_battery.isAlive();
			}
		};
		class SensorNodes {
		private:
			std::vector<std::shared_ptr<SensorNode>> mp_nodes;
		public:
			SensorNodes(const std::vector<std::shared_ptr<SensorNode>>& p_nodes)
				: mp_nodes(p_nodes) {

			}
			size_t getSize() const {
				return mp_nodes.size();
			}
			std::vector<std::weak_ptr<INode>> getNodes() const {
				std::vector<std::weak_ptr<INode>> ret;
				for (const auto& p_node : mp_nodes)
				{
					ret.push_back(p_node);
				}
				return ret;
			}
			// 全ノードが生きているかを判定
			bool areAlive() const {
				return !includeDeadOne();
			}
			// 空間情報からメッセージのコピーを取得する
			void sensing() {
				for (const auto& p_node : mp_nodes)
				{
					p_node->sensing();
				}
			}
			void returnToInitialPosition() {
				for (const auto& p_node : mp_nodes)
				{
					p_node->returnToInitialPosition();
				}
			}
			// 送信元ノードを探す
			virtual void searchSender() {
				for (const auto& p_node : mp_nodes)
				{
					p_node->searchSender();
				}
			}
			// 送信先ノードを探す
			virtual void searchReceiver() {
				for (const auto& p_node : mp_nodes)
				{
					p_node->searchReceiver();
				}
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gps){
				for (const auto& p_node : mp_nodes)
				{
					p_node->equip(p_gps);
				}
			}
			// 一つのノードが死んでいるかを判定
			bool includeDeadOne() const {
				return std::any_of(mp_nodes.begin(), mp_nodes.end(), [](const std::shared_ptr<INode>& node) { return !node->isAlive(); });
			}
			// あるノードが生きているかを判定
			bool includeAliveOne() const {
				return std::any_of(mp_nodes.begin(), mp_nodes.end(), [](const std::shared_ptr<INode>& node) { return node->isAlive(); });
			}
		};
		class BaseNode : public INode {
		private:
			// 固有ID
			const unsigned int m_UID;
			// 現在位置
			const geo::Point<double> m_position;
			// 送信元ノード
			std::vector<std::weak_ptr<INode>> mp_sender_nodes;
			// 送信先ノード
			std::vector<std::weak_ptr<INode>> mp_receiver_nodes;
			// マップ情報
			std::weak_ptr<GeometryMap> mp_gmap;
		public:
			BaseNode(const unsigned int UID, 
				const geo::Point<double>& position)
				: m_UID(UID), m_position(position) {
			}
			virtual unsigned int getSegmentID() const override {
				return 0;
			}
			virtual unsigned int getUID() const override {
				return m_UID;
			}
			virtual geo::Point<double> getPosition() const override {
				return m_position;
			}
			virtual std::shared_ptr<IMessage> collectMessage() override {
				std::vector<std::shared_ptr<IMessage>> p_msgs;
				for (auto& p_sender_node : mp_sender_nodes)
				{
					p_msgs.push_back(p_sender_node.lock()->collectMessage());
				}
				return std::make_shared<Messages>(p_msgs);
			}
			// 送信元ノードを探す
			virtual void searchSender() override {
				const auto p_gmap = mp_gmap.lock();
				mp_sender_nodes.clear();
				// 各レールごとにベースノードから見て最も近いノードを取得する
				for (const auto& rail : p_gmap->getRails())
				{
					auto nodes = p_gmap->searchNodesCloseToRail(rail);
					if (nodes.empty()) continue;
					const auto my_pos = m_position;
					const auto sort_func = [&my_pos](const std::weak_ptr<INode>& l, const std::weak_ptr<INode>& r) {
						return l.lock()->getPosition().distanceTo(my_pos) < r.lock()->getPosition().distanceTo(my_pos);
					};
					std::sort(nodes.begin(), nodes.end(), sort_func);
					mp_sender_nodes.push_back(nodes[0]);
				}
			}
			// 送信先ノードを探す
			virtual void searchReceiver() override {
				throw std::exception("searchingReceiver of base node not implemented");
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gmap) {
				mp_gmap = p_gmap;
			}
			// 生存フラグ
			virtual bool isAlive() const {
				return true;
			}
		};
	}
}