#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "point.h"
#include "types.h"
#include <vector>

class Line : public Shape {
public:
    Line(const point_t& p1, const point_t& p2);
	Line(const point_t& p1, const point_t& p2, const Color& color);
	shape_ptr_t clone() const;

	point_t center() const;
	void shift(const matrix3f& transf, const matrix3f& toWindow);
	void scale(const matrix3f& transf, const matrix3f& toWindow);
	void rotate(const matrix3f& rotation, const matrix3f& toWindow);
   
	virtual void worldToWindow(const matrix3f& transf);
	virtual void windowToWorld(const matrix3f& transf);

	void clip(const Clipper& clipper, edgevertex2f_t& clippedShape);

private:

};

#endif	 	  	 	     	   		   	      	 	    	 	
