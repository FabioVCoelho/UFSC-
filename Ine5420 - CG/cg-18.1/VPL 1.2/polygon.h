#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <vector>

class Polygon : public Shape {
public:
    Polygon(const points_t& points);
	Shape::shape_ptr_t clone() const;
	const points_t& points() const;
	points_t& points();
    void xShift(unit dx);
    void yShift(unit dy);
    void shift(unit dx, unit dy);
    void xShift(double fx, unit rx);
    void yShift(double fy, unit ry);
    void shift(double fx, double fy, unit rx, unit ry);
    void xScale(double sx);
    void yScale(double sy);
    void scale(double sx, double sy);
	void rotate(double a);
    void morph(const points_t& points);

private:
    points_t m_points;
	point_t m_center;

};

#endif