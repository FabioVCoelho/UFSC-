#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "matrix.h"
#include <vector>

class Polygon : public Shape {
public:
    Polygon(const points_t& points);
	Shape::shape_ptr_t clone() const;
	//const points_t& points() const;
	//points_t& points();
	point_t center() const;
    void xShift(const matrix3f& transf);
    void yShift(unit dy);
    void shift(unit dx, unit dy);
	void shift(const matrix3f& shift, const matrix3f& toWorld);
	void scale(const matrix3f& scale, const matrix3f& toWindow);
	void rotate(const matrix3f& rotation, const matrix3f& toWindow);
    void xShift(double fx, unit rx);
    void yShift(double fy, unit ry);
    void shift(double fx, double fy, unit rx, unit ry);
    void xScale(double sx);
    void yScale(double sy);
    void scale(double sx, double sy);
	void rotate(angle_t a);
    void morph(const points_t& points);
	void worldToWindow(const matrix3f& transf);
	void windowToWorld(const matrix3f& transf);
	void windowTransform(const matrix3f& transf);
	void worldTransform(const matrix3f& transf);

private:
	point_t m_center;
	point_t m_windowCenter;

};

#endif