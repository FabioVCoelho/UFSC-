#ifndef LINE_H
#define LINE_H

#include "object.h"
#include "point.h"
#include "types.h"
#include <vector>

template<size_t Dim>
class Line : public Object<Dim> {
public:

    Line(const vertex_t<Dim>& p1, const vertex_t<Dim>& p2);
	Line(const vertex_t<Dim>& p1, const vertex_t<Dim>& p2, const Color& color);
	object_ptr_t<Dim> clone() const;

	vertex_t<Dim> center() const;
	void shift(const transform_t<Dim>& transf, const transform_t<Dim>& toWindow);
	void scale(const transform_t<Dim>& transf, const transform_t<Dim>& toWindow);
	void rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow);
   
	virtual void worldToWindow(const transform_t<Dim>& transf);
	virtual void windowToWorld(const transform_t<Dim>& transf);

	void clip(const Clipper& clipper, shape2_t& clippedShape);

private:

};

#endif	 	  	 	     	   		   	      	 	    	 	
