#ifndef CLIPPER_H
#define CLIPPER_H

#include "types.h"

enum class WireframeClippingAlgs {
	CohenSutherland,
	alg2
};

enum class PolygonClippingAlgs {
	alg1,
	alg2
};


class WireframeClipper {
public:
	virtual size_t clip(const window_edges_t& edges, edgevertex2f_t& clippedShape) = 0;
};

class PolygonClipper {
public:
	virtual size_t clip(const edgevertex2f_t& points, edgevertex2f_t& clippedShape) = 0;
};


class Clipper {
public:
	Clipper();
	size_t clipWireframe(const window_edges_t& edges, edgevertex2f_t& clippedShape) const;
	size_t clipPolygon(const edgevertex2f_t& points, edgevertex2f_t& clippedShape) const;
	void setWireframeClipping(WireframeClippingAlgs alg);
	void setPolygonClipping(PolygonClippingAlgs alg);

private:
	WireframeClipper* m_wireframeClipper;
	PolygonClipper* m_polygonClipper;
};


#endif
