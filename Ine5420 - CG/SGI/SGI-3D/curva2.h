#ifndef CURVA_H
#define CURVA_H

#include <vector>
#include "object.h"

//using cp2 = control_vertex2_t;
//using cp3 = control_vertex3_t;

template<size_t Dim>
class curva2 : public Object<Dim> {
public:
	using cp = control_point_t<Dim>;

	curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4);
	curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const Color& color);
	curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const ObjectTraits& traits);

	object_ptr_t<Dim> clone() const;

	vertex_t<Dim> center() const { return m_center; }

	void shift(const transform_t<Dim>& shift, const transform_t<Dim>& toWindow);
	void scale(const transform_t<Dim>& scale, const transform_t<Dim>& toWindow);
	void rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow);

	void worldToWindow(const transform_t<Dim>& transf);
	void windowToWorld(const transform_t<Dim>& transf);

	void clip(const Clipper& clipper, shape2_t& clippedShape);

private:
	vertex_t<Dim> m_center;
	vertex_t<Dim> m_windowCenter;
};


#endif	 	  	 	     	   		   	      	 	    	 	
