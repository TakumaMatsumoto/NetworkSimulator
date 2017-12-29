#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Battery.h"
#include "geo.h"
#include "INode.h"
#include "GeometryMap.h"
#include "EnergyConsumption.h"

namespace sim {
	namespace swn {
		class SensorNode : public INode {
		private:
			class EnergyManager {
				// バッテリー
				Battery m_battery;
			public:
				EnergyManager(const Battery& battery) : m_battery(battery) {
				}
				class IOperation {
				public:
					virtual ~IOperation() = default;
					// 消費電力を計算する
					virtual double calcPowerConsumption() const = 0;
				};
				// メッセージを送信する際の操作
				class SendMessageOperation : public IOperation {
				private:
					// 1bitのデータを通信する際の消費電力[J/bit]
					const double m_Eelec;
					// 1bitのデータを1mだけ送信する際に使用される増幅器の消費電力[J/bit・m^2]
					const double m_Eamp;
					// 送受信間の点
					const std::pair<geo::Point<double>, geo::Point<double>> m_points;
					// 送信するメッセージ
					const IMessage& m_message;
				public:
					SendMessageOperation(
						const double Eelec, const double Eamp,
						const std::pair<geo::Point<double>, geo::Point<double>>& points,
						const IMessage& message) :
						m_Eelec(Eelec), m_Eamp(Eamp),
						m_points(points), m_message(message) {
					}
					double calcPowerConsumption() const override {
						return
							m_Eelec * m_message.getSize() +
							m_Eamp * m_message.getSize() * pow(m_points.first.distanceTo(m_points.second), 2.0);
					}
				};
				// メッセージを受信する際の操作
				class ReceiveMessageOperation : public IOperation {
					// 1bitのデータを通信する際の消費電力[J/bit]
					const double m_Eelec;
					// 受信するメッセージ
					const IMessage& m_message;
				public:
					ReceiveMessageOperation(
						const double Eelec,
						const IMessage& message) :
						m_Eelec(Eelec), m_message(message) {

					}
					double calcPowerConsumption() const {
						return m_Eelec * m_message.getSize();
					}
				};
				// 移動する際の操作
				class MoveOperation : public IOperation {
					// 1m移動する際の消費電力[J/m]
					const double m_Emov;
					// 移動するポイント
					const std::pair<geo::Point<double>, geo::Point<double>> m_points;
				public:
					MoveOperation(
						const double Emov,
						const std::pair<geo::Point<double>, geo::Point<double>>& points)
						: m_Emov(Emov), m_points(points) {
					}
					double calcPowerConsumption() const {
						return m_Emov * m_points.first.distanceTo(m_points.second);
					}
				};
				// 引数で与えられた操作メッセージを元にバッテリーを操作する
				void exec(const IOperation& opt) {
					m_battery.consume(opt.calcPowerConsumption());
				}
				// バッテリーが生きている場合、有効とする
				bool isValid() const {
					return m_battery.isAlive();
				}
				// バッテリーが死んでいる場合、無効とする
				bool isInvalid() const {
					return !isValid();
				}
			};
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
			double m_transmittable_range;
			// マップ情報
			std::weak_ptr<GeometryMap> mp_gmap;
			// エネルギーを管理する
			EnergyManager m_energy_manager;
			// エネルギー消費量
			EnergyConsumption m_energy_consumption;
			void moveTo(const geo::Point<double>& dst) {
				m_energy_manager.exec(EnergyManager::MoveOperation(m_energy_consumption.m_moving, { m_position, dst }));
				m_position = dst;
			}
		public:
			SensorNode(
				const unsigned int UID,
				const geo::Point<double>& position,
				const double transmittable_range,
				const Battery& battery,
				const EnergyConsumption& energy_consumption) : 
				m_UID(UID), m_initial_position(position), m_position(position),
				m_transmittable_range(transmittable_range), m_energy_manager(EnergyManager(battery)),
				m_energy_consumption(energy_consumption){
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
			// メッセージを集める(送受信・移動を含める)
			virtual std::shared_ptr<IMessage> collectMessage() override {
				// 送信メッセージ
				std::shared_ptr<Messages> send_msg = std::make_shared<Messages>();
				// 自身がセンサしたメッセージを送信メッセージとして追加
				send_msg->add(mp_sensored_message);
				// 自身にメッセージを送信するノードが存在するときは受信処理を行う
				if (mp_sender_node.lock()->getUID() != m_UID) {
					// メッセージ受信
					const auto recv_msg = mp_sender_node.lock()->collectMessage();
					// 受信分のエネルギーを消費
					m_energy_manager.exec(EnergyManager::ReceiveMessageOperation(m_energy_consumption.m_communication_per_bit, *recv_msg));
					// 受信したメッセージを送信メッセージとして追加
					send_msg->add(recv_msg);
				}
				// 通信先ノードと通信不可能の時、通信可能範囲まで移動
				if (!mp_receiver_node.lock()->getTransmittableArea().include(m_position)) {
					const auto my_rail = mp_gmap.lock()->searchTheClosestRail(*this);
					const auto intercepts = mp_receiver_node.lock()->getTransmittableArea().calcIntercepts(my_rail.getLine());
					const auto new_pos = intercepts.first.distanceTo(m_position) < intercepts.second.distanceTo(m_position) ? intercepts.first : intercepts.second;
					moveTo(new_pos);
				}
				// 送信分のエネルギーを消費
				m_energy_manager.exec(EnergyManager::SendMessageOperation(
					m_energy_consumption.m_communication_per_bit,
					m_energy_consumption.m_transmission_per_bit,
					{ m_position, mp_receiver_node.lock()->getPosition() },
					*send_msg));
				return send_msg;
			}
			virtual geo::Circle<double> getTransmittableArea() const override {
				return geo::Circle<double>(m_position, m_transmittable_range);
			}
			// メッセージを取得する
			void sensing(){
				mp_sensored_message = std::shared_ptr<Message>(new Message(mp_gmap.lock()->fetchMessage(*this)));
			}
			// レールへ移動する
			void moveToRail() {
				const auto p_gmap = mp_gmap.lock();
				// 最も近いレールを探索
				const auto my_rail = p_gmap->searchTheClosestRail(*this);
				// レールへ移動
				const auto new_pos = my_rail.getClosestCoordinate(m_position);
				moveTo(new_pos);
			}
			// 元の位置に戻る
			void returnToInitialPosition() {
				moveTo(m_initial_position);
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
					for (unsigned int i = 0, length = static_cast<unsigned int>(nodes_on_my_rail.size()); i < length; i++)
					{
						const auto& node = nodes_on_my_rail[i];
						if (node.lock()->getUID() == myUID && i == length - 1) return node;
						if (node.lock()->getUID() == myUID) return nodes_on_my_rail[i + 1];
					}
					throw std::exception("can't find receiver");
				}(m_UID);
			}
			// 送信先ノードを探す
			virtual void searchReceiver() override {
				const auto p_gmap = mp_gmap.lock();
				// 最も近いレールを探索
				const auto my_rail = p_gmap->searchTheClosestRail(*this);
				// 最も近いレールと同じレール上にあるノードを選び出す
				const auto nodes_on_my_rail = p_gmap->searchNodesCloseToRail(my_rail);
				mp_receiver_node = [&nodes_on_my_rail, &p_gmap](const unsigned int myUID) {
					// nodesは基地局に近い順に並んでいるので
					// 走査中のノードのUIDが自身のUIDと同じかつiが0以外の時はi-1が送信先ノードになる
					// 走査中のノードのUIDが自身のUIDと同じかつiが0の時はbasenodeが送信先ノードになる
					for (unsigned int i = 0, length = static_cast<unsigned int>(nodes_on_my_rail.size()); i < length; i++)
					{
						const auto& node = nodes_on_my_rail[i];
						if (node.lock()->getUID() == myUID && i == 0) return p_gmap->searchBaseNode();
						if (node.lock()->getUID() == myUID && i != 0) return nodes_on_my_rail[i - 1];
					}
					throw std::exception("can't find receiver");
				}(m_UID);
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gps) {
				mp_gmap = p_gps;
			}
			// 生存フラグ
			virtual bool isAlive() const {
				return m_energy_manager.isValid();
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
			// レールへ移動する
			void moveToRail() {
				for (const auto& p_node : mp_nodes)
				{
					p_node->moveToRail();
				}
			}
			// 初期位置に戻る
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
			// 通信可能範囲
			double m_transmittable_range;
		public:
			BaseNode(const unsigned int UID, 
				const geo::Point<double>& position,
				const double transmittable_range)
				: m_UID(UID), m_position(position), m_transmittable_range(transmittable_range) {
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
			virtual geo::Circle<double> getTransmittableArea() const override {
				return geo::Circle<double>(m_position, m_transmittable_range);
			}
		};
	}
}