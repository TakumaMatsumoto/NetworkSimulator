#pragma once
#include <memory>
#include "INode.h"

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
			// �����ŗ^����ꂽ�m�[�h����݂čł��߂����[�����擾����
			// @param node: �m�[�h
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

			// �����ŗ^����ꂽ���[���Ƌ������߂��m�[�h�̃��X�g���擾����
			// @param rail: ���[��
			std::vector<std::weak_ptr<INode>> searchNodesCloseToRail(const Rail& rail) const {
				std::vector<std::weak_ptr<INode>> ret;
				for (const auto& node : m_nodes)
				{
					// �Z�O�����gID��0�̂Ƃ���n�ǂȂ̂ŃX���[
					if (node.lock()->getSegmentID() == 0) continue;
					if (rail.getUID() == searchTheClosestRail(*node.lock()).getUID()) ret.push_back(node);
				}
				return ret;
			}
			// �����ŗ^����ꂽ�m�[�h���Z���V���O�\�Ȕ͈͓��Ƀ��b�Z�[�W�����݂���ꍇ�A���b�Z�[�W���Ƃ��Ă���
			// ���݂͂ǂ̏ꍇ�ł����Ă����b�Z�[�W���擾����悤�ɂ��Ă���
			Message fetchMessage(const INode& node) const {
				return m_default_message.clone();
			}
		};
	}
}