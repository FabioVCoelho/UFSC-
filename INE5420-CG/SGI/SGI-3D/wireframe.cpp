#include "wireframe.h"
#include "transforms.h"
#include <cassert>
#include <cmath>

template<size_t Dim>
Wireframe<Dim>::Wireframe(const shape_t<Dim>& shape)
	: Object<Dim>::Object(shape)
{
	calcCenter();
}

template<size_t Dim>
Wireframe<Dim>::Wireframe(const shape_t<Dim>& shape, const Color& color)
	: Object<Dim>::Object(shape, ObjectTraits(color, false, true))
{
	calcCenter();
}

template<size_t Dim>
Wireframe<Dim>::Wireframe(const shape_t<Dim>& shape, const ObjectTraits& traits)
	: Object<Dim>::Object(shape, traits)
{
	calcCenter();
}


template<size_t Dim>
void Wireframe<Dim>::calcCenter() {
	unit xavg = 0;
	unit yavg = 0;

	vertex_t<Dim> avg;
	for (auto& p : this->m_shape.vertices()) {
		avg += p;
		//xavg += p[0];
		//yavg += p[1];
	}	 	  	 	     	   		   	      	 	    	 	
	avg /= double(this->m_shape.vertices().size());
	//xavg /= this->m_shape.vertices().size();
	//yavg /= this->m_shape.vertices().size();
	//m_center = { xavg, yavg };
	m_center = avg;
}

template<size_t Dim>
object_ptr_t<Dim> Wireframe<Dim>::clone() const {
	std::shared_ptr<Wireframe> p(new Wireframe(*this));
	p->cloneShape(this->m_shape);
	return p;
}

template<size_t Dim>
void Wireframe<Dim>::shift(const transform_t<Dim>& shift, const transform_t<Dim>& toWindow) {
	shift >> this->m_shape.vertices();
	shift >> m_center;
	worldToWindow(toWindow);
}

template<size_t Dim>
void Wireframe<Dim>::scale(const transform_t<Dim>& scale, const transform_t<Dim>& toWindow) {
	scale >> this->m_shape.vertices();
	worldToWindow(toWindow);
}

template<size_t Dim>
void Wireframe<Dim>::rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow) {
	rotation >> this->m_shape.vertices();
	rotation >> m_center;
	worldToWindow(toWindow);
}

template<size_t Dim>
void Wireframe<Dim>::worldToWindow(const transform_t<Dim>& transf) {	 	  	 	     	   		   	      	 	    	 	
	mult(this->m_windowShape.vertices(), transf, this->m_shape.vertices());
	mult(m_windowCenter, transf, m_center);
}

template<size_t Dim>
void Wireframe<Dim>::windowToWorld(const transform_t<Dim>& transf) {
	mult(this->m_shape.vertices(), transf, this->m_windowShape.vertices());
	mult(m_center, transf, m_windowCenter);
}

template<size_t Dim>
void Wireframe<Dim>::clip(const Clipper& clipper, shape2_t& clippedShape) {
	clipper.clipWireframe(this->m_windowShape.edges(), clippedShape);
}

template class Wireframe<2>;
template class Wireframe<3>;
