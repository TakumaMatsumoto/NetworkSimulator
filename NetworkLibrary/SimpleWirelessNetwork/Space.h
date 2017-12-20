#pragma once
#include "Message.h"
namespace sim {
	namespace swn {
		/*
			空間に関する情報
		*/
		class Space {
		private:
			const Message m_default_message;
		public:
			Space(const Message& default_message) : m_default_message(default_message) {

			}
			virtual ~Space() = default;
			Message getMessage() const {
				return m_default_message;
			}
		};
	}
}