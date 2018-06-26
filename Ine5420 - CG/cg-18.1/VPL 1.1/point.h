#ifndef POINT_H
#define POINT_H

#include "shape.h"
//#include "geometry.h"

class Point : public Shape {
public:
    Point();
    Point(int x, int y);
	std::unique_ptr<Shape> clone() const;
	points_t points() const;
    void moveX(int dx);
    void moveY(int dy);
    void move(int dx, int dy);
    void morph(const points_t& points);
    void morph(const point_t& point);
    int xPos() const { return x; }
	int yPos() const { return y; }
	// int xPos() const { return m_coords[0]; }
	// int yPos() const { return m_coords[1]; }

private:
    int x, y;
    //Vec2i m_coords;
};

#endif