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

size_t Clipper::clipWireframe(const window_edges_t& edges, edgevertex2f_t& clippedShape) const {
	return m_wireframeClipper->clip(edges, clippedShape);
}

size_t Clipper::clipPolygon(const edgevertex2f_t& points, edgevertex2f_t& clippedShape) const {
	return m_polygonClipper->clip(points, clippedShape);
}