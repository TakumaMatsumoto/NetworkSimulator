#pragma once
#include <vector>
#include <numeric>

namespace sim {
	namespace swn {
		class IMessage {
		public:
			virtual ~IMessage() = default;
			virtual int getSize() const = 0;
		};
		class Message : public IMessage {
		private:
			unsigned int m_data_size;
		public:
			Message(const int data_size) : m_data_size(data_size) {

			}
			int getSize() const { return m_data_size; }
			Message* createClone() const {
				return new Message(m_data_size);
			}
		};
		class Messages : public IMessage {
			std::vector<Message> m_msgs;
		public:
			Messages(const std::vector<Message>& msgs) : m_msgs(msgs) {

			}
			int getSize() const { return std::accumulate(
				m_msgs.begin(), m_msgs.end(),
				0, [](int sum, const Message& elem) { return sum + elem.getSize(); });
			}
		};
	}
}