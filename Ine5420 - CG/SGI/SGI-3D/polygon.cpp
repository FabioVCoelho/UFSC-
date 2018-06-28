#include "polygon.h"
#include <cassert>
#include <cmath>

template<size_t Dim>
Polygon<Dim>::Polygon(const shape_t<Dim>& shape)
	: Wireframe<Dim>(shape, ObjectTraits(Color(), true, true))
{}

template<size_t Dim>
Polygon<Dim>::Polygon(const shape_t<Dim>& shape, const Color& color)
	: Wireframe<Dim>::Wireframe(shape, ObjectTraits(color, true, true))
{}

template<size_t Dim>
Polygon<Dim>::Polygon(const shape_t<Dim>& shape, const ObjectTraits& traits)
	: Wireframe<Dim>::Wireframe(shape, traits)
{}

template<size_t Dim>
object_ptr_t<Dim> Polygon<Dim>::clone() const {
	std::shared_ptr<Polygon> p(new Polygon(*this));
	p->cloneShape(this->m_shape);
	return p;
}

template<size_t Dim>
void Polygon<Dim>::clip(const Clipper& clipper, shape2_t& clippedShape) {
	clipper.clipPolygon(this->m_windowShape, clippedShape);
}

template class Polygon<2>;
template class Polygon<3>;	 	  	 	     	   		   	      	 	    	 	
