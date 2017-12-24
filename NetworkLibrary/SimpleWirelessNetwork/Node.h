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
			// �ŗLID
			const unsigned int m_UID;
			// ���g�Ƀ��b�Z�[�W�𑗐M����m�[�h
			std::weak_ptr<INode> mp_sender_node;
			// ���g�̃��b�Z�[�W�𑗐M����m�[�h
			std::weak_ptr<INode> mp_receiver_node;
			// �Z���V���O�ɂ�蓾��ꂽ���b�Z�[�W
			std::shared_ptr<IMessage> mp_sensored_message;
			// �����ʒu
			const geo::Point<double> m_initial_position;
			// ���݈ʒu
			geo::Point<double> m_position;
			// �ʐM�\�͈�
			double m_transmission_range;
			// �o�b�e���[
			Battery m_battery;
			// �A���e�i
			Antenner m_antenner;
			// �}�b�v���
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
				// ���g�Ƀ��b�Z�[�W�𑗐M����m�[�h�����݂���Ƃ��͎�M�������s��
				// ���b�Z�[�W��M
				const auto recv_msg = mp_sender_node.lock()->collectMessage();
				m_battery.consume(m_antenner.receive(*recv_msg));
				// ���b�Z�[�W����&���M
				const std::shared_ptr<IMessage> send_msg(new Messages({recv_msg, mp_sensored_message}));
				m_battery.consume(m_antenner.sendTo(m_position, mp_receiver_node.lock()->getPosition(), *send_msg));
				return send_msg;
			}
			// ���b�Z�[�W���擾����
			void sensing(){
				mp_sensored_message = std::shared_ptr<Message>(new Message(mp_gmap.lock()->fetchMessage(*this)));
			}
			// ���̈ʒu�ɖ߂�
			void returnToInitialPosition() {
				// �ł��߂����[����T��
				const auto my_rail = mp_gmap.lock()->searchTheClosestRail(*this);
				// �����ʒu����݂����[����̍ŒZ�����ƂȂ�_�ֈړ�
				const auto new_position = my_rail.getClosestCoordinate(m_initial_position);
				m_position = new_position;
				// �����ʒu�֖߂�
				m_position = m_initial_position;
			}
			// ���M���m�[�h��T��
			virtual void searchSender() override {
				const auto p_gmap = mp_gmap.lock();
				// �ł��߂����[����T��
				const auto my_rail = p_gmap->searchTheClosestRail(*this);
				// ���g�̃��[���Ɠ������[����ɂ���m�[�h��I�яo��
				const auto nodes_on_my_rail = p_gmap->searchNodesCloseToRail(my_rail);
				mp_sender_node = [&nodes_on_my_rail, &p_gmap](const unsigned int myUID) {
					// nodes�͊�n�ǂɋ߂����ɕ���ł���̂�
					// �������̃m�[�h��UID�����g��UID�Ɠ�������i��length-1�̎��͑��M���͑��݂��Ȃ�(�������g��Ԃ��悤�ɂ���)
					// �������̃m�[�h��UID�����g��UID�Ɠ�������i��length-1�ȊO�̎���i+1�����M���m�[�h�ɂȂ�
					for (int i = 0, length = nodes_on_my_rail.size(); i < length; i++)
					{
						const auto& node = nodes_on_my_rail[i];
						if (node.lock()->getUID() == myUID && i == length - 1) return node;
						if (node.lock()->getUID() == myUID) return nodes_on_my_rail[i + 1];
					}
					throw std::exception("can't find receiver");
				}(m_UID);

			}
			// ���M��m�[�h��T��(�ړ��L)
			virtual void searchReceiver() override {
				const auto p_gmap = mp_gmap.lock();
				// �ł��߂����[����T��
				const auto my_rail = p_gmap->searchTheClosestRail(*this);
				// ���[����Ɉړ�����
				const auto new_position = my_rail.getClosestCoordinate(m_initial_position);
				m_position = new_position;
				// ���g�̃��[���Ɠ������[����ɂ���m�[�h��I�яo��
				const auto nodes_on_my_rail = p_gmap->searchNodesCloseToRail(my_rail);
				mp_receiver_node = [&nodes_on_my_rail, &p_gmap](const unsigned int myUID) {
					// nodes�͊�n�ǂɋ߂����ɕ���ł���̂�
					// �������̃m�[�h��UID�����g��UID�Ɠ�������i��0�ȊO�̎���i-1�����M��m�[�h�ɂȂ�
					// �������̃m�[�h��UID�����g��UID�Ɠ�������i��0�̎���basenode�����M��m�[�h�ɂȂ�
					for (int i = 0, length = nodes_on_my_rail.size(); i < length; i++)
					{
						const auto& node = nodes_on_my_rail[i];
						if (node.lock()->getUID() == myUID && i == 0) return p_gmap->searchBaseNode();
						if (node.lock()->getUID() == myUID && i != 0) return nodes_on_my_rail[i - 1];
					}
					throw std::exception("can't find receiver");
				}(m_UID);
				// TODO::���M��m�[�h�Ɛڑ��ł���͈͂܂ňړ�
			}
			virtual void equip(const std::shared_ptr<GeometryMap>& p_gps) {
				mp_gmap = p_gps;
			}
			// �����t���O
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
			// �S�m�[�h�������Ă��邩�𔻒�
			bool areAlive() const {
				return !includeDeadOne();
			}
			// ��ԏ�񂩂烁�b�Z�[�W�̃R�s�[���擾����
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
			// ���M���m�[�h��T��
			virtual void searchSender() {
				for (const auto& p_node : mp_nodes)
				{
					p_node->searchSender();
				}
			}
			// ���M��m�[�h��T��
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
		};
	}
}