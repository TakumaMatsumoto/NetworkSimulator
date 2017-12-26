#pragma once
#include <cmath>
#include <utility>

namespace geo{
	static const double PI = 3.141592653589793;
	/*
		点クラス
		x,y座標を保有する
	*/
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

	/*
		線分クラス
		端点を保有する
	*/
	template<typename T>
	class LineSegment {
	private:
		std::pair<Point<T>, Point<T>> m_end_points;

	};
	/*
		半直線クラス
		終点を保有する
	*/
	template<typename T>
	class HalfLine {
	private:
		Point<T> m_end_point;

	};
	/*
		直線クラス
		傾き、y切片を保有する
	*/
	template<typename T>
	class StraightLine {
	private:
		// 傾き
		T m_slope;
		// y切片
		T m_y_intercept;
	public:
		// return y = slope * x + y_intercept
		// @param slope:		傾き
		// @param y_intercept:	y切片
		StraightLine(const T slope, const T y_intercept) :
			m_slope(slope), m_y_intercept(y_intercept) {
		}
		// 傾きと直線が通る点から直線オブジェクトを生成
		// @param slope: 傾き
		// @param point: 通る点
		static StraightLine<T> createFromSlopeAndPoint(const T slope, const geo::Point<T>& point) {
			return StraightLine<T>(slope, -slope * point.x + point.y);
		}
		// 傾きの角度とy切片から直線オブジェクトを生成
		// @param slope_angle: 傾きの角度
		// @param y_intercept: y切片
		static StraightLine<T> createFromSlopeAngleAndIntercept(const T slope_degree, const T y_intercept) {
			return StraightLine<T>(std::tan(slope_degree * PI / 180.0), y_intercept);
		}
		// 傾きの角度と直線が通る点から直線オブジェクトを生成
		// @param slope_angle: 傾きの角度
		// @param point: 通る点
		static StraightLine<T> createFromSlopeAngleAndIntercept(const T slope_degree, const geo::Point<T>& point) {
			return createFromSlopeAndPoint(std::tan(slope_degree * PI / 180.0), point);
		}
		// target:	(x0,y0)
		// line:	ax + by + c = 0
		// |a*x0 + b*y0 + c| / sqrt(a^2 + b^2)
		// a = -m_slope, b = 1, c = -m_y_intercept
		double distanceTo(const Point<T>& target) const {
			const double
				numer = std::abs(-m_slope * target.x + target.y - m_y_intercept),
				denom = std::sqrt(std::pow(m_slope, 2.0) + std::pow(1.0, 2.0));
			return numer / denom;
		}
		// 引数で与えられた座標から見て最も近い線上の座標を求める
		// 参考:https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q13115670548
		// @param point: 
		Point<T> getClosestCoordinate(const Point<T>& point) const {
			const T
				x_numer = m_slope * (point.y - m_y_intercept) + point.x,
				x_denom = pow(m_slope, 2) + 1,
				y_numer = m_slope * (m_slope * (point.y - m_y_intercept) + point.x),
				y_denom = pow(m_slope, 2) + 1,
				y_second = m_y_intercept;
			return Point<T>(x_numer / x_denom, y_numer / y_denom + y_second);
		}
	};

	/*
		矩形クラス
	*/
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
		Circle(const Point<T>& center, const T range) 
			: center(center), range(range){

		}
		Circle() : range(0){

		}
		// 引数で与えられた直線との交点を求める
		std::pair<Point<T>, Point<T>> calcIntercepts(const StraightLine<T>& line) {

		}
		bool include(const Point<T>& point){
			return center.distanceTo(point) <= range;
		}
	};
}