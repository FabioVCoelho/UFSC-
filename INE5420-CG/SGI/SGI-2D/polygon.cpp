#include "polygon.h"
#include <cassert>
#include <cmath>


Polygon::Polygon(const points_t& points)
	: Wireframe(points, ShapeTraits(Color(), true, true))
{}

Polygon::Polygon(const points_t& points, const Color& color)
	: Wireframe::Wireframe(points, ShapeTraits(color, true, true))
{}

Polygon::Polygon(const points_t& points, const ShapeTraits& traits)
	: Wireframe::Wireframe(points, traits)
{}

shape_ptr_t Polygon::clone() const {
	std::shared_ptr<Polygon> p(new Polygon(*this));
	p->reset(m_points.vertices());
	return p;
}

void Polygon::clip(const Clipper& clipper, edgevertex2f_t& clippedShape) {
	clipper.clipPolygon(m_windowPoints, clippedShape);
}	 	  	 	     	   		   	      	 	    	 	
