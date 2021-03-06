#pragma once
namespace sim {
	namespace swn {
		/*
			UIDの生成を担当するクラス
		*/
		class UIDCreator {
		private:
			unsigned int m_current_id = 0;
		public:
			unsigned int get() {
				const auto ret = m_current_id;
				m_current_id++;
				return ret;
			}
		};
	}
}