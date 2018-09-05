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

class PointClipper {
public:
	virtual void clip(const window_vertices2_t& points, window_vertices2_t& clippedPoints) = 0;
};

class WireframeClipper {
public:
	virtual void clip(const window_edges2_t& edges, shape2_t& clippedShape) = 0;
	virtual void clip(const window_edges3_t& edges, shape2_t& clippedShape) = 0;
};

class PolygonClipper {
public:
	virtual void clip(const shape2_t& shape, shape2_t& clippedShape) = 0;
};


class Clipper {
public:
	Clipper();
	void clipPoint(const window_vertices2_t& points, window_vertices2_t& clippedPoints) const;
	void clipPoint(const window_vertices3_t& points, window_vertices2_t& clippedPoints) const;
	void clipWireframe(const window_edges2_t& edges, shape2_t& clippedShape) const;
	void clipWireframe(const window_edges3_t& edges, shape2_t& clippedShape) const;
	//void clipWireframe(const window_edges2_t& edges, shape2_t& clippedShape) const;
	void clipPolygon(const shape2_t& shape, shape2_t& clippedShape) const;
	
	void setWireframeClipping(WireframeClippingAlgs alg);
	void setPolygonClipping(PolygonClippingAlgs alg);

private:
	WireframeClipper* m_wireframeClipper;
	PolygonClipper* m_polygonClipper;
};


#endif
	 	  	 	     	   		   	      	 	    	 	
