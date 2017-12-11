#pragma once

namespace ns{
	class Shelter{
		geo::Point<double> m_pos;
	public:
		Shelter(const geo::Point<double>& pos) : m_pos(pos){
		}
	};
	class Shelters{
		std::vector<Shelter> m_shelters;
	public:
		Shelters(const std::vector<Shelter>& shelters) : m_shelters(shelters){

		}
	};
}