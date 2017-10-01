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
		Point<T> left_bottom;
		T width, height;
		Rectangle(const Point<T>& left_bottom, const T width, const T height) :
			left_bottom(left_bottom), width(width), height(height){

		}
		Point<T> getCenter() const{
			return Point<T>((left_bottom.x + width) / 2, (left_bottom.y + height) / 2);
		}
		T getLeft() const{
			return left_bottom.x;
		}
		T getRight() const{
			return left_bottom.x + width;
		}
		T getButtom() const{
			return left_bottom.y;
		}
		T getTop() const{
			return left_bottom.y + height;
		}
		bool include(const Point<T>& point){
			bool inX = (left_bottom.x <= point.x) && (point.x <= left_bottom.x + width);
			bool inY = (left_bottom.y <= point.y) && (point.y <= left_bottom.y + height);
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