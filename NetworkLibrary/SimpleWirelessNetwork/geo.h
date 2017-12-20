#pragma once
#include <cmath>
#include <utility>

namespace geo{
	template<typename T>
	class Point{
	public:
		virtual ~Point() = default;
		Point(const T x, const T y) : x(x), y(y){

		}
		Point() : x(0), y(0){
		}
		T x, y;
		double distanceTo(const Point& target) const{
			return sqrt(pow(x - target.x, 2.0) + pow(y - target.y, 2.0));
		}
	};

	template<typename T>
	class LineSegment {
	private:
		std::pair<Point<T>, Point<T>> m_end_points;

	};
	template<typename T>
	class HalfLine {
	private:
		Point<T> m_end_point;

	};

	template<typename T>
	class StraightLine {
	private:
		// åXÇ´
		T m_slope;
		// yêÿï–
		T m_y_intercept;
	public:
		// return y = slope * x + y_intercept
		// @param slope:		åXÇ´
		// @param y_intercept:	yêÿï–
		StraightLine(const T slope, const T y_intercept) :
			m_slope(slope), m_y_intercept(y_intercept) {
		}
		// target:	(x0,y0)
		// line:	ax + by + c = 0
		// |a*x0 + b*y0 + c| / sqrt(a^2 + b^2)
		// a = -m_slope, b = 1, c = -m_y_intercept
		double distanceTo(const Point& target) const {
			const double
				numer = std::abs(-m_slope * target.x + target.y - m_y_intercept),
				denom = std::sqrt(std::pow(m_slope, 2.0) + std::pow(1.0, 2.0));
			return numer / denom;
		}
	};

	template<typename T>
	class Rectangle{
	public:
		virtual ~Rectangle() = default;
		Point<T> bottom_left;
		T width, height;
		Rectangle(const Point<T>& bottom_left, const T width, const T height) :
			bottom_left(bottom_left), width(width), height(height){

		}
		Rectangle() : width(0), height(0){

		}
		Point<T> getCenter() const{
			return Point((bottom_left.x + width) / 2, (bottom_left.y + height) / 2);
		}
		int getLeft() const{
			return bottom_left.x;
		}
		int getRight() const{
			return bottom_left.x + width;
		}
		int getButtom() const{
			return bottom_left.y;
		}
		int getTop() const{
			return bottom_left.y + height;
		}
		bool include(const Point<T>& point){
			bool inX = (bottom_left.x <= point.x) && (point.x <= bottom_left.x + width);
			bool inY = (bottom_left.y <= point.y) && (point.y <= bottom_left.y + height);
			return inX && inY;
		}
	};

	template<typename T>
	class Circle{
	public:
		Point<T> center;
		T range;
		Circle(const Point<T>& center, const T range) : center(center), range(range){

		}
		Circle() : range(0){

		}
		bool include(const Point<T>& point){
			return center.distanceTo(point) <= range;
		}
	};
}