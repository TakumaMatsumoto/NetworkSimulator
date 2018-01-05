#pragma once
#include "geo.h"

namespace sim {
	namespace swn {
		class Obstacle {
		private:
			unsigned int m_UID;
			geo::Point<double> m_position;
		public:
			Obstacle(const unsigned int UID, const geo::Point<double>& position) 
				: m_UID(UID), m_position(position) {

			}
			geo::Circle<double> getCollisionArea() const {
				return geo::Circle<double>(m_position, 2.0);
			}
			geo::Point<double> getPosition() const {
				return m_position;
			}
			bool closeTo(const geo::StraightLine<double>& line) const {
				const auto base = line.getPointAtX(m_position.x);
				return base.distanceTo(m_position) < 0.01;
			}
		};
	}
}