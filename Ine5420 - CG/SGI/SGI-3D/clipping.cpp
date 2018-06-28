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

void Clipper::clipWireframe(const window_edges2_t& edges, shape2_t& clippedShape) const {
	m_wireframeClipper->clip(edges, clippedShape);
}
void Clipper::clipWireframe(const window_edges3_t& edges, shape2_t& clippedShape) const {
	m_wireframeClipper->clip(edges, clippedShape);
}

//void Clipper::clipWireframe(const window_edges2_t& edges, shape2_t& clippedShape) const {
//	m_wireframeClipper->clip(edges, clippedShape);
//}

void Clipper::clipPolygon(const shape2_t& shape, shape2_t& clippedShape) const {
	m_polygonClipper->clip(shape, clippedShape);
}

//void Clipper::clipPoint(const window_vertices3_t& vertices, window_vertices2_t& clippedPoints) const {
//	window_vertices2_t vert(vertices.begin(), vertices.end());
//	clipPoint(vert, clippedPoints);
//}

void Clipper::clipPoint(const window_vertices2_t& points, window_vertices2_t& clippedPoints) const {
	clippedPoints.clear();
	for (auto& p : points) {
		if (!(p[0] < -1 || p[0] > 1 || p[1] < -1 || p[1] > 1)) {
			clippedPoints.emplace_back(p);
		}
	}

}

void Clipper::clipPoint(const window_vertices3_t& points, window_vertices2_t& clippedPoints) const {
	clippedPoints.clear();
	for (auto& p : points) {
		if (!(p[0] < -1 || p[0] > 1 || p[1] < -1 || p[1] > 1)) {
			clippedPoints.emplace_back(p);
		}	 	  	 	     	   		   	      	 	    	 	
	}

}