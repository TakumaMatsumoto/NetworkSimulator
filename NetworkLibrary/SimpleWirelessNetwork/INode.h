#pragma once
#include <stack>
#include "Message.h"
#include "geo.h"

namespace sim {
	namespace swn {
		class INode {
		public:
			virtual ~INode() = default;
			// �ŗLID���擾����
			virtual unsigned int getUID() const = 0;
			// 
			virtual INode& getReceiver() = 0;
			// ���݈ʒu���擾����
			virtual geo::Point<double> getPosition() const = 0;
			// ���M���m�[�h��T��
			virtual void searchSender() = 0;
			// ���M��m�[�h��T��
			virtual void searchReceiver() = 0;
			// ���b�Z�[�W�����W����
			// return: ���b�Z�[�W
			virtual std::shared_ptr<IMessage> collectMessage() = 0;
			// �����t���O
			virtual bool isAlive() const = 0;
			// �Z�O�����g�ԍ����擾����
			virtual unsigned int getSegmentID() const = 0;
			// �ʐM�\�̈���擾����
			virtual geo::Circle<double> getTransmittableArea() const = 0;
		};
	}
}