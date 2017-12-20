#pragma once
#include <memory>
#include <vector>
#include "Message.h"
#include "geo.h"

namespace sim {
	namespace swn {
		class INode {
		public:
			virtual ~INode() = default;
			// ���݈ʒu���擾����
			virtual geo::Point<double> getPosition() const = 0;
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M���m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchSender(const std::vector<std::shared_ptr<INode>>& nodes) = 0;
			// �����ŗ^����ꂽ�m�[�h�̃��X�g���瑗�M��m�[�h��T��
			// @param nodes: �{���Ώۂ̃m�[�h���X�g
			virtual void searchReceiver(const std::vector<std::shared_ptr<INode>>& nodes) = 0;
			// ���b�Z�[�W�����W����
			// return: ���b�Z�[�W
			virtual IMessage& collectMessage() = 0;
			// �����t���O
			virtual bool isAlive() const = 0;
		};
	}
}