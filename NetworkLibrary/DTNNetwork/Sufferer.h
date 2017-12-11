#pragma once

namespace ns{
	class Sufferer{
		geo::Point<double> m_pos;
	public:
		Sufferer(const geo::Point<double>& pos) : m_pos(pos){

		}
	};
	class Sufferers{
		std::vector<Sufferer> m_sufferers;
	public:
		Sufferers(const std::vector<Sufferer>& sufferers) : m_sufferers(sufferers){

		}
	};
}