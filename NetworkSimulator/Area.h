#pragma once

namespace ns{
	class Area{
		geo::Rectangle<double> m_rect;
	public:
		Area(const geo::Rectangle<double>& rect) : m_rect(rect){
		}
	};
}