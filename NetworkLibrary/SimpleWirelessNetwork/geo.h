#pragma once
#include <cmath>
#include <utility>

namespace geo{
	static const double PI = 3.141592653589793;
	/*
		�_�N���X
		x,y���W��ۗL����
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
		�����N���X
		�[�_��ۗL����
	*/
	template<typename T>
	class LineSegment {
	private:
		std::pair<Point<T>, Point<T>> m_end_points;

	};
	/*
		�������N���X
		�I�_��ۗL����
	*/
	template<typename T>
	class HalfLine {
	private:
		Point<T> m_end_point;

	};
	/*
		�����N���X
		�X���Ay�ؕЂ�ۗL����
	*/
	template<typename T>
	class StraightLine {
	private:
		// �X��
		T m_slope;
		// y�ؕ�
		T m_y_intercept;
	public:
		// return y = slope * x + y_intercept
		// @param slope:		�X��
		// @param y_intercept:	y�ؕ�
		StraightLine(const T slope, const T y_intercept) :
			m_slope(slope), m_y_intercept(y_intercept) {
		}
		// �X���ƒ������ʂ�_���璼���I�u�W�F�N�g�𐶐�
		// @param slope: �X��
		// @param point: �ʂ�_
		static StraightLine<T> createFromSlopeAndPoint(const T slope, const geo::Point<T>& point) {
			return StraightLine<T>(slope, -slope * point.x + point.y);
		}
		// �X���̊p�x��y�ؕЂ��璼���I�u�W�F�N�g�𐶐�
		// @param slope_angle: �X���̊p�x
		// @param y_intercept: y�ؕ�
		static StraightLine<T> createFromSlopeAngleAndIntercept(const T slope_degree, const T y_intercept) {
			return StraightLine<T>(std::tan(slope_degree * PI / 180.0), y_intercept);
		}
		// �X���̊p�x�ƒ������ʂ�_���璼���I�u�W�F�N�g�𐶐�
		// @param slope_angle: �X���̊p�x
		// @param point: �ʂ�_
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
		// �����ŗ^����ꂽ���W���猩�čł��߂�����̍��W�����߂�
		// �Q�l:https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q13115670548
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
		��`�N���X
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
		// �����ŗ^����ꂽ�����Ƃ̌�_�����߂�
		std::pair<Point<T>, Point<T>> calcIntercepts(const StraightLine<T>& line) {

		}
		bool include(const Point<T>& point){
			return center.distanceTo(point) <= range;
		}
	};
}