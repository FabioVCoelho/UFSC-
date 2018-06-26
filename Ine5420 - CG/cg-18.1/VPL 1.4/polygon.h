#ifndef POLYGON_H
#define POLYGON_H

#include "wireframe.h"
#include "matrix.h"
#include <vector>

class Polygon : public Wireframe {
public:
	Polygon(const points_t& points);
	Polygon(const points_t& points, const Color& color);

	shape_ptr_t clone() const;

	bool isPolygon() const { return true; }

	void clip(const Clipper& clipper, edgevertex2f_t& clippedShape);

private:
	point_t m_center;
	point_t m_windowCenter;
};

#endif