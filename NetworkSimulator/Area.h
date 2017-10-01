#pragma once

namespace ns{
	class Area{
		geo::Rectangle<double> m_rect;
	public:
		Area(const geo::Point<double>& left_bottom, const double width, const double height) : 
			m_rect(left_bottom, width, height){

		}
		Area(const geo::Rectangle<double>& rect) : m_rect(rect){
		}
	};
}