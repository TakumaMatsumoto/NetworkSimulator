#pragma once
#include <math.h>

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
		double distanceTo(const Point<T>& target) const{
			return sqrt(pow(x - target.x, 2.0) + pow(y - target.y, 2.0));
		}
	};

	template<typename T>
	class Rectangle{
	public:
		Point<T> bottom_left;
		T width, height;
		Rectangle(const Point<T>& bottom_left, const T width, const T height) :
			bottom_left(bottom_left), width(width), height(height){

		}
		Point<T> getCenter() const{
			return Point<T>((bottom_left.x + width) / 2, (bottom_left.y + height) / 2);
		}
		T getLeft() const{
			return bottom_left.x;
		}
		T getRight() const{
			return bottom_left.x + width;
		}
		T getButtom() const{
			return bottom_left.y;
		}
		T getTop() const{
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
		Circle(const Point<T>& center, T range) : center(center), range(range){

		}
		bool include(const Point<T>& point){
			return center.distanceTo(point) <= range;
		}
	};
}