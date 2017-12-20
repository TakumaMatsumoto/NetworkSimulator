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
			// ��ԏ�񂩂烁�b�Z�[�W�̃R�s�[���擾����
			void sensing(const Space& space){
				mp_sensored_message.reset(space.getMessage().createClone());
			}
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M���m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M��m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// �����t���O
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
			// �S�m�[�h�������Ă��邩�𔻒�
			bool areAlive() const {
				return !includeDeadOne();
			}
			// ��ԏ�񂩂烁�b�Z�[�W�̃R�s�[���擾����
			void sensing(const Space& space) {
				for (const auto& snode : m_nodes)
				{
					snode->sensing(space);
				}
			}
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M���m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes){
				for (const auto& node : m_nodes)
				{
					node->searchSender(nodes);
				}
			}
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M��m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes){
				for (const auto& node : m_nodes)
				{
					node->searchReceiver(nodes);
				}
			}
			// ��̃m�[�h������ł��邩�𔻒�
			bool includeDeadOne() const {
				return std::any_of(m_nodes.begin(), m_nodes.end(), [](const std::shared_ptr<INode>& node) { return !node->isAlive(); });
			}
			// ����m�[�h�������Ă��邩�𔻒�
			bool includeAliveOne() const {
				return std::any_of(m_nodes.begin(), m_nodes.end(), [](const std::shared_ptr<INode>& node) { return node->isAlive(); });
			}
		};
		class BaseNode : public INode {
		private:

			// ���݈ʒu
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
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M���m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M��m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes) override {

			}
			// �����t���O
			virtual bool isAlive() const {
				return true;
			}
		};
	}
}