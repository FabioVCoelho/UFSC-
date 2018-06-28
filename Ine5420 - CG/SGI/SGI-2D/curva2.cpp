
#include "curva2.h"
#include "vec.h"
#include "types.h"
#include <math.h>
#include <string>
#include "transforms.h"
#include <cassert>
#include <cmath>
#include <cstdio>

const double DELTA = 0.01;
unsigned int numpoints = 0;

using cp = curva2::cp;

std::vector<Vec4f> bezierFactors() {
	std::vector<Vec4f> ret;
	ret.reserve(1 + 1.0 / DELTA);
	double step = 0;
	double tt, ttt, t3, tt3, ttt3;
	for (double t = 0; t <= 1.0; t += DELTA) {
		t3 = 3 * t;
		tt = t * t;
		ttt = tt * t;
		tt3 = 3 * tt;
		ttt3 = 3 * ttt;
		ret.push_back(Vec4f(
			(1 - t3 + tt3 - ttt),
			(t3 - 6 * tt + ttt3),
			(tt3 - ttt3),
			ttt
		));
	}
	numpoints = ret.size();
	return ret;
}	 	  	 	     	   		   	      	 	    	 	

const std::vector<Vec4f> bezierCoefficients = bezierFactors();


const points_t& calcPoints(const cp& p1, const cp& p2, const cp& p3, const cp& p4) {
	float t = 0;
	static points_t curve(numpoints);

	for (size_t t = 0; t < curve.size(); ++t) {
		const Vec4f& bc = bezierCoefficients[t];
		curve[t] = {
			bc[0]*p1[0] + bc[1]*p2[0] + bc[2]*p3[0] + bc[3]*p4[0],
			bc[0]*p1[1] + bc[1]*p2[1] + bc[2]*p3[1] + bc[3]*p4[1]
		};
	}

	return curve;
}

curva2::curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4)
	: Shape::Shape(calcPoints(p1, p2, p3, p4), ShapeTraits(Color(), false, false))
{}

curva2::curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const Color& color)
	: Shape::Shape(calcPoints(p1, p2, p3, p4), ShapeTraits(color, false, false))
{}

curva2::curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const ShapeTraits& traits)
	: Shape::Shape(calcPoints(p1, p2, p3, p4), traits)
{}

shape_ptr_t curva2::clone() const {
	std::shared_ptr<curva2> p(new curva2(*this));
	p->reset(m_points.vertices());
	return p;
}	 	  	 	     	   		   	      	 	    	 	

void curva2::shift(const matrix3f& shift, const matrix3f& toWindow) {
	shift >> m_points.vertices();
	shift >> m_center;
	worldToWindow(toWindow);
}

void curva2::scale(const matrix3f& scale, const matrix3f& toWindow) {
	scale >> m_points.vertices();
	worldToWindow(toWindow);
}

void curva2::rotate(const matrix3f& rotation, const matrix3f& toWindow) {
	rotation >> m_points.vertices();
	rotation >> m_center;
	worldToWindow(toWindow);
}

void curva2::worldToWindow(const matrix3f& transf) {
	mult(m_windowPoints.vertices(), transf, m_points.vertices());
	mult(m_windowCenter, transf, m_center);
}

void curva2::windowToWorld(const matrix3f& transf) {
	mult(m_points.vertices(), transf, m_windowPoints.vertices());
	mult(m_center, transf, m_windowCenter);
}

void curva2::clip(const Clipper& clipper, edgevertex2f_t& clippedShape) {
	clipper.clipPoint(m_windowPoints.vertices(), clippedShape.vertices());
	clippedShape.reset(false);
}






	 	  	 	     	   		   	      	 	    	 	
