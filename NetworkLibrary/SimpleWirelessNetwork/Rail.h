#pragma once
#include "geo.h"

namespace sim {
	namespace swn {
		class Rail {
		private:
			const unsigned int m_UID;
			geo::StraightLine<double> m_line;
		public:
			Rail(const unsigned int UID, const geo::StraightLine<double>& line) 
				: m_UID(UID), m_line(line) {
			}
			unsigned int getUID() const {
				return m_UID;
			}
			double distanceTo(const geo::Point<double>& dst) const {
				return m_line.distanceTo(dst);
			}
			geo::Point<double> getClosestCoordinate(const geo::Point<double>& point) const {
				return m_line.getClosestCoordinate(point);
			}
		};
	}
}