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

template<size_t Dim>
using cp = typename curva2<Dim>::cp;

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

template<size_t Dim>
const vertices_t<Dim>& calcPoints(const cp<Dim>& p1, const cp<Dim>& p2, const cp<Dim>& p3, const cp<Dim>& p4);

template<>
const vertices_t<2>& calcPoints(const cp<2>& p1, const cp<2>& p2, const cp<2>& p3, const cp<2>& p4) {
	float t = 0;
	static vertices_t<2> curve(numpoints);
	for (size_t t = 0; t < curve.size(); ++t) {
		const Vec4f& bc = bezierCoefficients[t];
		curve[t] = {
			bc[0] * p1[0] + bc[1] * p2[0] + bc[2] * p3[0] + bc[3] * p4[0],
			bc[0] * p1[1] + bc[1] * p2[1] + bc[2] * p3[1] + bc[3] * p4[1]
		};
	}
	return curve;
}

template<>
const vertices_t<3>& calcPoints(const cp<3>& p1, const cp<3>& p2, const cp<3>& p3, const cp<3>& p4) {
	float t = 0;
	static vertices_t<3> curve(numpoints);
	for (size_t t = 0; t < curve.size(); ++t) {
		const Vec4f& bc = bezierCoefficients[t];
		curve[t] = {
			bc[0] * p1[0] + bc[1] * p2[0] + bc[2] * p3[0] + bc[3] * p4[0],
			bc[0] * p1[1] + bc[1] * p2[1] + bc[2] * p3[1] + bc[3] * p4[1],
			bc[0] * p1[2] + bc[1] * p2[2] + bc[2] * p3[2] + bc[3] * p4[2],
		};
	}
	return curve;
}

template<size_t Dim>
curva2<Dim>::curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4)
	: Object<Dim>::Object(calcPoints<Dim>(p1, p2, p3, p4), ObjectTraits(Color(), false, false))
{}	 	  	 	     	   		   	      	 	    	 	

template<size_t Dim>
curva2<Dim>::curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const Color& color)
	: Object<Dim>::Object(calcPoints<Dim>(p1, p2, p3, p4), ObjectTraits(color, false, false))
{}

template<size_t Dim>
curva2<Dim>::curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const ObjectTraits& traits)
	: Object<Dim>::Object(calcPoints<Dim>(p1, p2, p3, p4), traits)
{}

template<size_t Dim>
object_ptr_t<Dim> curva2<Dim>::clone() const {
	std::shared_ptr<curva2<Dim>> p(new curva2<Dim>(*this));
	//using Object<Dim>::m_shape;
	//using Object<Dim>::cloneShape;
	p->cloneShape(this->m_shape);
	//p->
	return p;
}

template<size_t Dim>
void curva2<Dim>::shift(const transform_t<Dim>& shift, const transform_t<Dim>& toWindow) {
	shift >> this->m_shape.vertices();
	shift >> m_center;
	worldToWindow(toWindow);
}

template<size_t Dim>
void curva2<Dim>::scale(const transform_t<Dim>& scale, const transform_t<Dim>& toWindow) {
	scale >> this->m_shape.vertices();
	worldToWindow(toWindow);
}

template<size_t Dim>
void curva2<Dim>::rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow) {	 	  	 	     	   		   	      	 	    	 	
	rotation >> this->m_shape.vertices();
	rotation >> m_center;
	worldToWindow(toWindow);
}

template<size_t Dim>
void curva2<Dim>::worldToWindow(const transform_t<Dim>& transf) {
	mult(this->m_windowShape.vertices(), transf, this->m_shape.vertices());
	mult(m_windowCenter, transf, m_center);
}

template<size_t Dim>
void curva2<Dim>::windowToWorld(const transform_t<Dim>& transf) {
	mult(this->m_shape.vertices(), transf, this->m_windowShape.vertices());
	mult(m_center, transf, m_windowCenter);
}

template<size_t Dim>
void curva2<Dim>::clip(const Clipper& clipper, shape2_t& clippedObject) {
	clipper.clipPoint(this->m_windowShape.vertices(), clippedObject.vertices());
	clippedObject.defaultEdges(false);
	//clippedObject.reset(false);
}

template class curva2<2>;
template class curva2<3>;





	 	  	 	     	   		   	      	 	    	 	
