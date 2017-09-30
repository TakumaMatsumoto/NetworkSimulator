#pragma once

namespace geo{
	class Point{
	public:
		virtual ~Point() = default;
		Point(const int x, const int y) : x(x), y(y){

		}
		Point() : x(0), y(0){
		}
		int x, y;
		double distanceTo(const Point& target) const{
			return sqrt(pow(x - target.x, 2.0) + pow(y - target.y, 2.0));
		}
	};

	class Rectangle{
	public:
		virtual ~Rectangle() = default;
		Point bottom_left;
		int width, height;
		Rectangle(const Point& bottom_left, const int width, const int height) :
			bottom_left(bottom_left), width(width), height(height){

		}
		Rectangle() : width(0), height(0){

		}
		Point getCenter() const{
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
		bool include(const Point& point){
			bool inX = (bottom_left.x <= point.x) && (point.x <= bottom_left.x + width);
			bool inY = (bottom_left.y <= point.y) && (point.y <= bottom_left.y + height);
			return inX && inY;
		}
	};

	class Circle{
	public:
		Point center;
		int range;
		Circle(const Point& center, int range) : center(center), range(range){

		}
		Circle() : range(0){

		}
		bool include(const Point& point){
			return center.distanceTo(point) <= range;
		}
	};
}