#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "point.h"
#include <vector>

class Line : public Shape {
public:
    Line(const Point& p1, const Point& p2);
	std::unique_ptr<Shape> clone() const;
	points_t points() const;
    void moveX(int dx);
    void moveY(int dy);
    void move(int dx, int dy);
    void morph(const points_t& points);

private:
    Point p1, p2;

};

#endif