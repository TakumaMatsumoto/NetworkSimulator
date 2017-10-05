#pragma once
#include "geo.h"

namespace ns{
	class Area{
		geo::Rectangle<double> m_rect;
	public:
		double getWidth() const{
			return m_rect.width;
		}
		double getHeight() const{
			return m_rect.height;
		}
		Area(const geo::Point<double>& left_bottom, const double width, const double height) : 
			m_rect(left_bottom, width, height){

		}
		Area(const geo::Rectangle<double>& rect) : m_rect(rect){
		}
	};
}