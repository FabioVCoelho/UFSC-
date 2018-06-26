#include "point.h"
#include <cassert>

Point::Point() 
    : Point(0, 0) {}

// Point::Point(int x, int y) 
//     : m_coords(x,y) {}

Point::Point(int x, int y) 
    : x(x), y(y) {}

std::unique_ptr<Shape> Point::clone() const {
	return std::unique_ptr<Point>(new Point(*this));
}

points_t Point::points() const {
	return points_t{point_t{x,y}};
}
    
void Point::moveX(int dx) {
    x += dx;
    //m_coords += dx;
}

void Point::moveY(int dy) {
    y += dy;
    //m_coords += dy;
}

void Point::move(int dx, int dy) {
    moveX(dx);
    moveY(dy);
}

void Point::morph(const points_t& points) {
    assert(points.size() == 1);
    x = points[0].first;
    y = points[0].second;
}

void Point::morph(const point_t& point) {
    x = point.first;
    y = point.second;
}