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
	virtual void clip(const window_points_t& points, window_points_t& clippedPoints) = 0;
};

class WireframeClipper {
public:
	virtual void clip(const window_edges_t& edges, edgevertex2f_t& clippedShape) = 0;
};

class PolygonClipper {
public:
	virtual void clip(const edgevertex2f_t& points, edgevertex2f_t& clippedShape) = 0;
};


class Clipper {
public:
	Clipper();
	void clipWireframe(const window_edges_t& edges, edgevertex2f_t& clippedShape) const;
	void clipPolygon(const edgevertex2f_t& points, edgevertex2f_t& clippedShape) const;
	void clipPoint(const window_points_t& points, window_points_t& clippedPoints) const;
	void setWireframeClipping(WireframeClippingAlgs alg);
	void setPolygonClipping(PolygonClippingAlgs alg);

private:
	WireframeClipper* m_wireframeClipper;
	PolygonClipper* m_polygonClipper;
};


#endif
	 	  	 	     	   		   	      	 	    	 	
