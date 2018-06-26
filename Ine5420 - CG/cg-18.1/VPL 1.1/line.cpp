#include "line.h"
#include <cassert>


Line::Line(const Point& p1, const Point& p2)
    : p1(p1), p2(p2) {}

std::unique_ptr<Shape> Line::clone() const {
	return std::unique_ptr<Line>(new Line(*this));
}

points_t Line::points() const {
	return points_t{
		point_t{p1.xPos(),p1.yPos()},
		point_t{p2.xPos(),p2.yPos()}
	};
}

void Line::moveX(int dx) {
    p1.moveX(dx);
    p2.moveX(dx);
}

void Line::moveY(int dy) {
    p1.moveY(dy);
    p2.moveY(dy);
}

void Line::move(int dx, int dy) {
    p1.move(dx, dy);
    p2.move(dx, dy);
}

void Line::morph(const points_t& points) {
    assert(points.size() == 2);
    p1.morph(points[0]);
    p2.morph(points[1]);
}