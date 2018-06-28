#ifndef POLYGON_H
#define POLYGON_H

#include "wireframe.h"
#include "matrix.h"
#include <vector>

template<size_t Dim>
class Polygon : public Wireframe<Dim> {
public:
	Polygon(const shape_t<Dim>& shape);
	Polygon(const shape_t<Dim>& shape, const Color& color);
	Polygon(const shape_t<Dim>& shape, const ObjectTraits& traits);

	object_ptr_t<Dim> clone() const;

	void clip(const Clipper& clipper, shape2_t& clippedShape);

private:
	vertex_t<Dim> m_center;
	vertex_t<Dim> m_windowCenter;
};

#endif