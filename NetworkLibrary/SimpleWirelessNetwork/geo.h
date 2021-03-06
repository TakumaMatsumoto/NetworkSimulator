#pragma once
#include <cmath>
#include <utility>

namespace geo{
	static const double PI = 3.141592653589793;
	template<typename T>
	class Vector2D {
	public:
		virtual ~Vector2D() = default;
		Vector2D(const T x, const T y) : x(x), y(y) {

		}
		Vector2D() : x(0), y(0) {
		}
		T x, y;
		double distanceTo(const Vector2D& target) const {
			return sqrt(pow(x - target.x, 2.0) + pow(y - target.y, 2.0));
		}
	};

	template<typename T> 
	using Point = Vector2D<T>;

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
	public:
		// 傾き
		T m_slope;
		// y切片
		T m_y_intercept;
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
		// x座標軸の値が引数で与えられた値のときの座標を取得する
		geo::Point<T> getPointAtX(const T x) const {
			return geo::Point<T>(x, m_slope * x + m_y_intercept);
		}
		// 引数で与えられた座標から見て最も近い線上の座標を求める
		// 参考:https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q13115670548
		// @param point: 
		Point<T> getClosestCoordinate(const Point<T>& point) const {
			const T
				x_numer = m_slope * (point.y - m_y_intercept) + point.x,
				x_denom = pow(m_slope, 2.0) + 1.0,
				y_numer = m_slope * (m_slope * (point.y - m_y_intercept) + point.x),
				y_denom = pow(m_slope, 2.0) + 1.0,
				y_second = m_y_intercept;
			return Point<T>(x_numer / x_denom, y_numer / y_denom + y_second);
		}
		// 単位ベクトルを取得する
		Vector2D<T> getUnitVector() const {
			const T numer = sqrt(1 + pow(m_slope, 2.0));
			return Vector2D<T>(1.0 / numer, m_slope / numer);
		}
		double getAngle() const {
			return std::atan(m_slope);
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
		bool include(const Point<T>& point) const{
			const bool inX = (bottom_left.x < point.x) && (point.x < bottom_left.x + width);
			const bool inY = (bottom_left.y < point.y) && (point.y < bottom_left.y + height);
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
			if (!intersects(line)) throw std::exception("circle does not intersect line");
			const Point<T> foot_of_perpendicular = line.getClosestCoordinate(center);
			const auto length = sqrt(pow(range, 2.0) - pow(line.distanceTo(center), 2.0));
			const Vector2D<T> unit_vector = line.getUnitVector();
			return {
				Point<T>(
					foot_of_perpendicular.x + length * unit_vector.x,
					foot_of_perpendicular.y + length * unit_vector.y),
				Point<T>(
					foot_of_perpendicular.x - length * unit_vector.x,
					foot_of_perpendicular.y - length * unit_vector.y),
			};
		}
		// 引数で与えられた直線との交わる場合、trueとなる
		bool intersects(const StraightLine<T>& line) const{
			const double
				first = pow(line.m_slope * (line.m_y_intercept - center.y) - center.x, 2.0),
				second = (pow(line.m_slope, 2.0) + 1.0) * (pow(center.x, 2.0) + pow(line.m_y_intercept - center.y, 2.0) - pow(range, 2.0));
			return first - second >= 0;
		}
		bool include(const Point<T>& point) const{
			return center.distanceTo(point) <= range;
		}
	};
}