#pragma once
#include <vector>
#include <numeric>

namespace sim {
	namespace swn {
		class IMessage {
		public:
			virtual ~IMessage() = default;
			virtual unsigned int getSize() const = 0;
		};
		class Message : public IMessage {
		private:
			unsigned int m_data_size;
		public:
			Message(const unsigned int data_size) : m_data_size(data_size) {

			}
			unsigned int getSize() const { return m_data_size; }
			Message clone() const {
				return Message(m_data_size);
			}
		};
		class Messages : public IMessage {
		private:
			std::vector<std::shared_ptr<IMessage>> mp_msgs;
		public:
			Messages() = default;
			Messages(const std::vector<std::shared_ptr<IMessage>>& p_msgs) : mp_msgs(p_msgs) {
			}
			void add(const std::shared_ptr<IMessage>& msg) {
				mp_msgs.push_back(msg);
			}
			unsigned int getSize() const {
				return std::accumulate(mp_msgs.begin(), mp_msgs.end(), 0, [](unsigned int init, const std::shared_ptr<IMessage>& msg) {
					return init + msg->getSize();
				});
			}
		};
	}
}