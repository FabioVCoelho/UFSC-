#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "shape.h"
#include "matrix.h"
#include <vector>

class Wireframe : public Shape {
public:
	Wireframe(const points_t& points);
	Wireframe(const points_t& points, const Color& color);
	Wireframe(const points_t& points, const ShapeTraits& traits);

	shape_ptr_t clone() const;

	point_t center() const { return m_center; }

	void shift(const matrix3f& shift, const matrix3f& toWindow);
	void scale(const matrix3f& scale, const matrix3f& toWindow);
	void rotate(const matrix3f& rotation, const matrix3f& toWindow);
    
	void worldToWindow(const matrix3f& transf);
	void windowToWorld(const matrix3f& transf);

	void clip(const Clipper& clipper, edgevertex2f_t& clippedShape);

	void calcCenter();

private:
	point_t m_center;
	point_t m_windowCenter;
};

#endif