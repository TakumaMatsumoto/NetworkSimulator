#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
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
				// �o�b�e���[
				Battery m_battery;
			public:
				EnergyManager(const Battery& battery) : m_battery(battery) {
				}
				class IOperation {
				public:
					virtual ~IOperation() = default;
					// ����d�͂��v�Z����
					virtual double calcPowerConsumption() const = 0;
				};
				// ���b�Z�[�W�𑗐M����ۂ̑���
				class SendMessageOperation : public IOperation {
				private:
					// 1bit�̃f�[�^��ʐM����ۂ̏���d��[J/bit]
					const double m_Eelec;
					// 1bit�̃f�[�^��1m�������M����ۂɎg�p����鑝����̏���d��[J/bit�Em^2]
					const double m_Eamp;
					// ����M�Ԃ̓_
					const std::pair<geo::Point<double>, geo::Point<double>> m_points;
					// ���M���郁�b�Z�[�W
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
				// ���b�Z�[�W����M����ۂ̑���
				class ReceiveMessageOperation : public IOperation {
					// 1bit�̃f�[�^��ʐM����ۂ̏���d��[J/bit]
					const double m_Eelec;
					// ��M���郁�b�Z�[�W
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
				// �ړ�����ۂ̑���
				class MoveOperation : public IOperation {
					// 1m�ړ�����ۂ̏���d��[J/m]
					const double m_Emov;
					// �ړ�����|�C���g
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
				// �����ŗ^����ꂽ���상�b�Z�[�W�����Ƀo�b�e���[�𑀍삷��
				void exec(const IOperation& opt) {
					m_battery.consume(opt.calcPowerConsumption());
				}
				// �o�b�e���[�������Ă���ꍇ�A�L���Ƃ���
				bool isValid() const {
					return m_battery.isAlive();
				}
				// �o�b�e���[������ł���ꍇ�A�����Ƃ���
				bool isInvalid() const {
					return !isValid();
				}
			};
			// �ŗLID
			const unsigned int m_UID;
			// ���g�Ƀ��b�Z�[�W�𑗐M����m�[�h
			std::vector<std::weak_ptr<INode>> mp_sender_nodes;
			// ���g�̃��b�Z�[�W�𑗐M����m�[�h
			std::weak_ptr<INode> mp_receiver_node;
			// �Z���V���O�ɂ�蓾��ꂽ���b�Z�[�W
			std::shared_ptr<IMessage> mp_sensored_message;
			// �����ʒu
			const geo::Point<double> m_initial_position;
			// ���݈ʒu
			geo::Point<double> m_position;
			// �ړ��\��ʒu
			std::queue<geo::Point<double>> m_points_to_move;
			// �ʐM�\�͈�
			double m_transmittable_range;
			// �}�b�v���
			std::weak_ptr<GeometryMap> mp_gmap;
			// �G�l���M�[���Ǘ�����
			EnergyManager m_energy_manager;
			// �G�l���M�[�����
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
			// ���b�Z�[�W���W�߂�(����M�E�ړ����܂߂�)
			virtual std::shared_ptr<IMessage> collectMessage() override {
				// ���M���b�Z�[�W
				std::shared_ptr<Messages> send_msg = std::make_shared<Messages>();
				// ���g���Z���T�������b�Z�[�W�𑗐M���b�Z�[�W�Ƃ��Ēǉ�
				send_msg->add(mp_sensored_message);
				// ���g�Ƀ��b�Z�[�W�𑗐M����m�[�h�����݂���Ƃ��͎�M�������s��
				for (const auto& p_sender_node : mp_sender_nodes)
				{
					// ���b�Z�[�W��M
					const auto recv_msg = p_sender_node.lock()->collectMessage();
					// ��M���̃G�l���M�[������
					m_energy_manager.exec(EnergyManager::ReceiveMessageOperation(m_energy_consumption.m_communication_per_bit, *recv_msg));
					// ��M�������b�Z�[�W�𑗐M���b�Z�[�W�Ƃ��Ēǉ�
					send_msg->add(recv_msg);
				}
				// ���M��m�[�h����������ۂɋL�^�������[�g�����Ɉړ�����
				while (!m_points_to_move.empty()) {
					moveTo(m_points_to_move.front());
					m_points_to_move.pop();
				}
				// ���M���̃G�l���M�[������
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
			// ���b�Z�[�W���擾����
			void sensing(){
				mp_sensored_message = std::shared_ptr<Message>(new Message(mp_gmap.lock()->fetchMessage(m_position)));
			}
			// ���[���ֈړ�����
			void moveToRail() {
				const auto p_gmap = mp_gmap.lock();
				// �ł��߂����[����T��
				const auto my_rail = p_gmap->orderRailsByDistance(m_position)[0];
				// ���[���ֈړ�
				const auto new_pos = my_rail.getClosestCoordinate(m_position);
				moveTo(new_pos);
			}
			// ���̈ʒu�ɖ߂�
			void returnToInitialPosition() {
				moveTo(m_initial_position);
			}
			// ���M���m�[�h��T��
			virtual void searchSender() override {
				mp_sender_nodes.clear();
				const auto p_gmap = mp_gmap.lock();
				// �S�m�[�h�̂����A���肩��݂Ď�M�҂�ID�����g�̏ꍇ
				// ���M���Ƃ��ēo�^
				for (const auto& node : p_gmap->getNodes()) {
					if (node.lock()->getUID() == m_UID) continue;
					if (node.lock()->getReceiver().getUID() == m_UID) {
						mp_sender_nodes.push_back(node);
					}
				}
			}
			// ���M��m�[�h��T��(���[�g�T����)
			virtual void searchReceiver() override {
				const auto p_gmap = mp_gmap.lock();
				auto pos = m_position;
				while (true)
				{
					// �ł��߂����[����T��
					const auto my_rail = p_gmap->orderRailsByDistance(pos)[0];
					const auto nodes = p_gmap->searchNodesBetween(my_rail, {p_gmap->searchBaseNode().lock()->getPosition(), pos});
					const auto p_receiver = nodes.empty() ? p_gmap->searchBaseNode() : nodes.back();
					// ���M��m�[�h�Ƃ̊Ԃɂ����Q����T��
					const auto obstacles = p_gmap->searchObstaclesBetween(my_rail, { p_receiver.lock()->getPosition(), pos });
					// ���M��m�[�h�Ƃ̊Ԃɏ�Q�������݂��Ȃ��ꍇ�Ap_receiver�𑗐M��m�[�h�Ƃ��ďI��
					if (obstacles.empty()) {
						// ���M��m�[�h���ʐM�\�͈͓��ɑ��݂��Ȃ��Ƃ��A�ʐM�\�ɂȂ�܂ňړ�����
						if (!geo::Circle<double>(pos, m_transmittable_range).include(p_receiver.lock()->getPosition())) {
							const auto intercepts = p_receiver.lock()->getTransmittableArea().calcIntercepts(my_rail.getLine());
							const auto new_pos = intercepts.first.distanceTo(pos) < intercepts.second.distanceTo(pos) ? intercepts.first : intercepts.second;
							m_points_to_move.push(new_pos);
						}
						mp_receiver_node = p_receiver;
						break;
					}
					// ���M��Ƃ̊Ԃɏ�Q�������݂���ꍇ�A��Q���ƏՓ˂���n�_���L�^���A�ʂ̃��[���Ɉړ�����
					const auto target_obstacle = obstacles.back();
					// ��Q���Ƃ��łɏՓ˂��Ă���ꍇ�A���݂̈ʒu���ړ��ʒu�Ƃ���
					if (target_obstacle.getCollisionArea().include(pos)) {
						m_points_to_move.push(pos);
					}
					else {
						const auto intercepts = target_obstacle.getCollisionArea().calcIntercepts(my_rail.getLine());
						const auto col_pos = intercepts.first.distanceTo(pos) < intercepts.second.distanceTo(pos) ? intercepts.first : intercepts.second;
						m_points_to_move.push(col_pos);
					}
					const auto new_rail = mp_gmap.lock()->orderRailsByDistance(pos)[1];
					const auto new_pos = new_rail.getClosestCoordinate(m_points_to_move.back());
					m_points_to_move.push(new_pos);
					// �ʒu��ʂ̃��[���ɓ��������Ƃ��̈ʒu�ɍX�V
					pos = new_pos;
				}
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gps) {
				mp_gmap = p_gps;
			}
			virtual INode& getReceiver() override {
				return *mp_receiver_node.lock();
			}
			// �����t���O
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
			// �S�m�[�h�������Ă��邩�𔻒�
			bool areAlive() const {
				return !includeDeadOne();
			}
			// ��ԏ�񂩂烁�b�Z�[�W�̃R�s�[���擾����
			void sensing() {
				for (const auto& p_node : mp_nodes)
				{
					if (p_node->isAlive()) p_node->sensing();
				}
			}
			// ���[���ֈړ�����
			void moveToRail() {
				for (const auto& p_node : mp_nodes)
				{
					if (p_node->isAlive()) p_node->moveToRail();
				}
			}
			// �����ʒu�ɖ߂�
			void returnToInitialPosition() {
				for (const auto& p_node : mp_nodes)
				{
					if (p_node->isAlive()) p_node->returnToInitialPosition();
				}
			}
			// ���M���m�[�h��T��
			virtual void searchSender() {
				for (const auto& p_node : mp_nodes)
				{
					if (p_node->isAlive()) p_node->searchSender();
				}
			}
			// ���M��m�[�h��T��
			virtual void searchReceiver() {
				for (const auto& p_node : mp_nodes)
				{
					if (p_node->isAlive()) p_node->searchReceiver();
				}
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gps){
				for (const auto& p_node : mp_nodes)
				{
					p_node->equip(p_gps);
				}
			}
			// ��̃m�[�h������ł��邩�𔻒�
			bool includeDeadOne() const {
				return std::any_of(mp_nodes.begin(), mp_nodes.end(), [](const std::shared_ptr<INode>& node) { return !node->isAlive(); });
			}
			// ����m�[�h�������Ă��邩�𔻒�
			bool includeAliveOne() const {
				return std::any_of(mp_nodes.begin(), mp_nodes.end(), [](const std::shared_ptr<INode>& node) { return node->isAlive(); });
			}
		};
		class BaseNode : public INode {
		private:
			// �ŗLID
			const unsigned int m_UID;
			// ���݈ʒu
			const geo::Point<double> m_position;
			// ���M���m�[�h
			std::vector<std::weak_ptr<INode>> mp_sender_nodes;
			// ���M��m�[�h
			std::vector<std::weak_ptr<INode>> mp_receiver_nodes;
			// �}�b�v���
			std::weak_ptr<GeometryMap> mp_gmap;
			// �ʐM�\�͈�
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
			// ���M���m�[�h��T��
			virtual void searchSender() override {
				const auto p_gmap = mp_gmap.lock();
				mp_sender_nodes.clear();
				// �e���[�����ƂɃx�[�X�m�[�h���猩�čł��߂��m�[�h���擾����
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
			// ���M��m�[�h��T��
			virtual void searchReceiver() override {
				throw std::exception("searchingReceiver of base node not implemented");
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gmap) {
				mp_gmap = p_gmap;
			}
			// �����t���O
			virtual bool isAlive() const {
				return true;
			}
			virtual INode& getReceiver() override {
				return *this;
			}
			virtual geo::Circle<double> getTransmittableArea() const override {
				return geo::Circle<double>(m_position, m_transmittable_range);
			}
		};
	}
}