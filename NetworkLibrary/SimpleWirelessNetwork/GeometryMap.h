#pragma once
#include <memory>
#include "INode.h"
#include "Obstacle.h"

namespace sim {
	namespace swn {
		/*
			�S�m�[�h�̈ʒu�A���[���̏��A�Z���V���O���b�Z�[�W
			�Ȃǂ̋�ԏ����W�߂��}�b�v
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
			// �����ŗ^����ꂽ�ʒu����݂ċ߂����ɂ��ă��[�����擾����
			// @param pos: �ʒu���
			std::vector<Rail> orderRailsByDistance(const geo::Point<double>& pos) const {
				std::vector<Rail> ret = m_rails;
				const auto sort_func = [&pos](const Rail& l, const Rail& r) {
					return l.distanceTo(pos) < r.distanceTo(pos);
				};
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

			// �����ŗ^����ꂽ���[���Ƌ������߂��m�[�h�̃��X�g���擾����
			// @param rail: ���[��
			std::vector<std::weak_ptr<INode>> searchNodesCloseToRail(const Rail& rail) const {
				std::vector<std::weak_ptr<INode>> ret;
				for (const auto& node : m_nodes)
				{
					// �Z�O�����gID��0�̂Ƃ���n�ǂȂ̂ŃX���[
					if (node.lock()->getSegmentID() == 0) continue;
					if (rail.getUID() == orderRailsByDistance(node.lock()->getPosition())[0].getUID()) ret.push_back(node);
				}
				return ret;
			}
			std::vector<std::weak_ptr<INode>> getNodes() const {
				return m_nodes;
			}
			// �����ŗ^����ꂽ�m�[�h���Z���V���O�\�Ȕ͈͓��Ƀ��b�Z�[�W�����݂���ꍇ�A���b�Z�[�W���Ƃ��Ă���
			// ���݂͂ǂ̏ꍇ�ł����Ă����b�Z�[�W���擾����悤�ɂ��Ă���
			Message fetchMessage(const geo::Point<double>& pos) const {
				return m_default_message.clone();
			}
		};
	}
}