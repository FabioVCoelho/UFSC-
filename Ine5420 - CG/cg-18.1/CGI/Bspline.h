#ifndef BSPLINE_H
#define BSPLINE_H

#include <vector>
#include "shape.h"

class Bspline : public Shape {
public:

	Bspline(points_t controles);
	Bspline(points_t controles, const Color& color);
	Bspline(points_t controles, const ShapeTraits& traits);

	shape_ptr_t clone() const;

	point_t center() const { return m_center; }

	void shift(const matrix3f& shift, const matrix3f& toWindow);
	void scale(const matrix3f& scale, const matrix3f& toWindow);
	void rotate(const matrix3f& rotation, const matrix3f& toWindow);

	void worldToWindow(const matrix3f& transf);
	void windowToWorld(const matrix3f& transf);

	void clip(const Clipper& clipper, edgevertex2f_t& clippedShape);
        
        std::vector<Vec2f> forwardDiff(float n, double x, double x1, double x2, double x3
                                              , double y, double y1, double y2, double y3);
        std::vector<Vec2f> bSpline(std::vector<point_t> controlPoints);
        void calcCenter(points_t);
        
private:
	point_t m_center;
	point_t m_windowCenter;
};


#endif