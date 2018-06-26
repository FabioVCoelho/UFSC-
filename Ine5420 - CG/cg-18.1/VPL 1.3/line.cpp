#include "line.h"
#include <cassert>
#include <cmath>


Line::Line(const point_t& p1_, const point_t& p2_)
	: Shape::Shape({ p1_, p2_ }) {}//, p1(&m_points[0]), p2(&m_points[1])


Shape::shape_ptr_t Line::clone() const {
	return std::shared_ptr<Line>(new Line(*this));
}

point_t Line::center() const {
	return point_t(
		(m_points[0][0] + m_points[1][0]) / 2,
		(m_points[0][1] + m_points[1][1]) / 2
	);
}

//const points_t& Line::points() const {
//	//m_points = { p1,p2 };
//	return m_points;
//}
//
//points_t& Line::points() {
//	//m_points = { p1,p2 };
//	return m_points;
//}

void Line::xShift(unit dx) {
    m_points[0][0] += dx;
    m_points[1][0] += dx;
}

void Line::yShift(unit dy) {
	m_points[0][1] += dy;
    m_points[1][1] += dy;
}

void Line::shift(unit dx, unit dy) {
    m_points[0][0] += dx;
    m_points[0][1] += dy;
    m_points[1][0] += dx;
    m_points[1][1] += dy;
}

void Line::xShift(double fx, unit rx) {
	double inc = fx > 0 ?
		ceil(fx * rx) : floor(fx * rx);
    m_points[0][0] += inc;
    m_points[1][0] += inc;
}
void Line::yShift(double fy, unit ry) {
    double inc = fy > 0 ?
		ceil(fy * ry) : floor(fy * ry);
    m_points[0][1] += inc;
    m_points[1][1] += inc;
}
void Line::shift(double fx, double fy, unit rx, unit ry) {
    double incx = fx > 0 ?
		ceil(fx * rx) : floor(fx * rx);
    double incy = fy > 0 ?
		ceil(fy * ry) : floor(fy * ry);
    m_points[0][0] += incx;
    m_points[0][1] += incy;
    m_points[1][0] += incx;
    m_points[1][1] += incy;
}

void Line::xScale(double sx) {
    double xavg = double((m_points[0][0] + m_points[1][0]) * 1.0f / 2);
    
    m_points[0][0] = sx*(m_points[0][0] - xavg) + xavg;
    m_points[1][0] = sx*(m_points[1][0] - xavg) + xavg;

}
void Line::yScale(double sy) { 
   double yavg = double((m_points[0][1] + m_points[1][1]) * 1.0f / 2);
    
    m_points[0][1] = sy*(m_points[0][1] - yavg) + yavg;
    m_points[1][1] = sy*(m_points[1][1] - yavg) + yavg;
}
void Line::scale(double sx, double sy) {
    double xavg = double((m_points[0][0] + m_points[1][0]) * 1.0f / 2);
    double yavg = double((m_points[0][1] + m_points[1][1]) * 1.0f / 2);

    m_points[0][0] = sx*(m_points[0][0] - xavg) + xavg;
    m_points[0][1] = sy*(m_points[0][1] - yavg) + yavg;
    m_points[1][0] = sx*(m_points[1][0] - xavg) + xavg;
    m_points[1][1] = sy*(m_points[1][1] - yavg) + yavg;
}

void Line::rotate(double a) {
	
}

void Line::morph(const points_t& points) {
    assert(points.size() == 2);

	m_points[0] = points[0];
	m_points[1] = points[1];
}

void Line::worldToWindow(const matrix3f& transf) {
	//m_windowPoints = rotatec3f(-window.angle(), window.center()) * m_points;
	m_windowPoints = transf * m_points;
}
void Line::windowToWorld(const matrix3f& transf) {
	//m_points = rotatec3f(-window.angle(), window.center()) * m_windowPoints;
	m_points = transf * m_windowPoints;
}