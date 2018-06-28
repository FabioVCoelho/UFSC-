#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "object.h"
#include "matrix.h"
#include <vector>

template<size_t Dim>
class Wireframe : public Object<Dim> {
public:
	Wireframe(const shape_t<Dim>& shape);
	Wireframe(const shape_t<Dim>& shape, const Color& color);
	Wireframe(const shape_t<Dim>& shape, const ObjectTraits& traits);

	object_ptr_t<Dim> clone() const;

	vertex_t<Dim> center() const { return m_center; }

	void shift(const transform_t<Dim>& shift, const transform_t<Dim>& toWindow);
	void scale(const transform_t<Dim>& scale, const transform_t<Dim>& toWindow);
	void rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow);
    
	void worldToWindow(const transform_t<Dim>& transf);
	void windowToWorld(const transform_t<Dim>& transf);

	void clip(const Clipper& clipper, shape2_t& clippedShape);

	void calcCenter();

private:
	vertex_t<Dim> m_center;
	vertex_t<Dim> m_windowCenter;
};

#endif	 	  	 	     	   		   	      	 	    	 	
