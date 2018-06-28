#include "line.h"
#include <cassert>
#include <cmath>

template<size_t Dim>
Line<Dim>::Line(const vertex_t<Dim>& p1_, const vertex_t<Dim>& p2_)
	: Object<Dim>::Object(shape_t<Dim>({ p1_, p2_ }), ObjectTraits(Color(), false, false)) {}

template<size_t Dim>
Line<Dim>::Line(const vertex_t<Dim>& p1_, const vertex_t<Dim>& p2_, const Color& color)
	: Object<Dim>::Object(shape_t<Dim>({ p1_, p2_ }), ObjectTraits(color, false, false)) {}


template<size_t Dim>
object_ptr_t<Dim> Line<Dim>::clone() const {
	std::shared_ptr<Line> p(new Line(*this));
	p->cloneShape(this->m_shape);
	return p;
}

template<size_t Dim>
vertex_t<Dim> Line<Dim>::center() const {
	return ((this->m_shape.vertices()[0] + this->m_shape.vertices()[1]) / 2.0);
	/*return vertex_t(
		(this->m_shape.vertices()[0][0] + this->m_shape.vertices()[1][0]) / 2,
		(this->m_shape.vertices()[0][1] + this->m_shape.vertices()[1][1]) / 2
	);*/
}

template<size_t Dim>
void Line<Dim>::shift(const transform_t<Dim>& shift, const transform_t<Dim>& toWindow) {
	shift >> this->m_shape.vertices();
	worldToWindow(toWindow);
}

template<size_t Dim>
void Line<Dim>::scale(const transform_t<Dim>& scale, const transform_t<Dim>& toWindow) {	 	  	 	     	   		   	      	 	    	 	
	scale >> this->m_shape.vertices();
	worldToWindow(toWindow);
}

template<size_t Dim>
void Line<Dim>::rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow) {
	rotation >> this->m_shape.vertices();
	worldToWindow(toWindow);
}
template<size_t Dim>
void Line<Dim>::worldToWindow(const transform_t<Dim>& transf) {
	mult(this->m_windowShape.vertices(), transf, this->m_shape.vertices());
}

template<size_t Dim>
void Line<Dim>::windowToWorld(const transform_t<Dim>& transf) {
	mult(this->m_shape.vertices(), transf, this->m_windowShape.vertices());
}

template<size_t Dim>
void Line<Dim>::clip(const Clipper& clipper, shape2_t& clippedShape) {
	clipper.clipWireframe(this->m_windowShape.edges(), clippedShape);
}

template class Line<2>; 
template class Line<3>;	 	  	 	     	   		   	      	 	    	 	
