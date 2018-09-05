#include "clipping.h"
#include "cohen_sutherland.h"
#include "weiler_atherton.h"
#include <limits>


CohenSutherland cohenSutherland;
WeilerAtherton weilerAtherton;


Clipper::Clipper() 
	: m_wireframeClipper(&cohenSutherland), m_polygonClipper(&weilerAtherton)
{}

void Clipper::setWireframeClipping(WireframeClippingAlgs alg) {
	switch (alg) {
	case WireframeClippingAlgs::CohenSutherland:
		m_wireframeClipper = &cohenSutherland;
		break;
	case WireframeClippingAlgs::alg2 :
		break;
	default:
		break;
	}
}

void Clipper::setPolygonClipping(PolygonClippingAlgs alg) {
	switch (alg) {
	case PolygonClippingAlgs::alg1:
		m_polygonClipper = &weilerAtherton;
		break;
	case PolygonClippingAlgs::alg2:
		break;
	default:
		break;
	}
}	 	  	 	     	   		   	      	 	    	 	

void Clipper::clipWireframe(const window_edges_t& edges, edgevertex2f_t& clippedShape) const {
	m_wireframeClipper->clip(edges, clippedShape);
}

void Clipper::clipPolygon(const edgevertex2f_t& points, edgevertex2f_t& clippedShape) const {
	m_polygonClipper->clip(points, clippedShape);
}

void Clipper::clipPoint(const window_points_t& points, window_points_t& clippedPoints) const {
	clippedPoints.clear();
	for (auto& p : points) {
		if (!(p[0] < -1 || p[0] > 1 || p[1] < -1 || p[1] > 1)) {
			clippedPoints.emplace_back(p);
		}
	}

}