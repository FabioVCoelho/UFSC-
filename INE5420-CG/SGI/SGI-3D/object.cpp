#include "object.h"
#include "transforms.h"

template<size_t Dim>
Object<Dim>::Object(const shape_t<Dim>& shape)
	: Object(shape, ObjectTraits())
{}

template<size_t Dim>
Object<Dim>::Object(const shape_t<Dim>& shape, const ObjectTraits& traits)
	: m_shape(shape), m_windowShape(shape), m_id(-1), m_traits(traits)
{}

template<size_t Dim>
Object<Dim>::~Object() {}

template<size_t Dim>
void Object<Dim>::cloneShape(const shape_t<Dim>& shape) {
	m_shape.copy(shape);
}

template<>
void Object<2>::perspective(double dop) {}


template<>
void Object<3>::perspective(double dop) {
	for (vertex3_t& v : m_windowShape.vertices()) {
		double d = dop / v.m_z;
		scale4f(d, d, d) >> v;
	}
}


template class Object<2>;
template class Object<3>;
	 	  	 	     	   		   	      	 	    	 	
