#include "polygon.h"
#include "transforms.h"
#include <cassert>
#include <cmath>


Polygon::Polygon(const points_t& points)
    : m_points(points) 
{
	unit xavg = 0;
	unit yavg = 0;

	for (auto& p : m_points) {
		xavg += p[0];
		yavg += p[1];
	}
	xavg /= m_points.size();
	yavg /= m_points.size();
	m_center = { xavg, yavg };
}

Shape::shape_ptr_t Polygon::clone() const {
	return std::shared_ptr<Polygon>(new Polygon(*this));
}

const points_t& Polygon::points() const {
	return m_points;
}

points_t& Polygon::points() {
	return m_points;
}

void Polygon::xShift(unit dx) {
	shift3f(dx, 0.0) * m_points;
	m_center[0] += dx;
}

void Polygon::yShift(unit dy) {
	shift3f(0.0, dy) * m_points;
	m_center[1] += dy;
}

void Polygon::shift(unit dx, unit dy) {
	shift3f(dx, dy) * m_points;
	m_center[0] += dx;
	m_center[1] += dy;
}

void Polygon::xShift(double fx, unit rx) {
	shift3f(fx*rx, 0.0) * m_points;
	m_center[0] += fx*rx;
}
void Polygon::yShift(double fy, unit ry) {
	shift3f(0.0, fy*ry) * m_points;
	m_center[1] += fy*ry;
}
void Polygon::shift(double fx, double fy, unit rx, unit ry) {
	shift3f(fx*rx, fy*ry) * m_points;
	m_center[0] += fx*rx;
	m_center[1] += fy*ry;
}

void Polygon::xScale(double sx) {
	scalec3f(sx, 0.0, m_center) * m_points;
}
void Polygon::yScale(double sy) {
	scalec3f(0.0, sy, m_center) * m_points;
}
void Polygon::scale(double sx, double sy) {
	scalec3f(sx, sy, m_center) * m_points;
}

void Polygon::rotate(double a) {
	rotatec3f(a, m_center) * m_points;
}

void Polygon::morph(const points_t& points) {
    assert(points.size() == m_points.size());
    size_t i = 0;
    for (auto& point : m_points) {
        point = points[i++];
    }
}