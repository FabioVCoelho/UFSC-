#ifndef CURVA_H
#define CURVA_H

#include <vector>
#include "shape.h"

class curva2 : public Shape {
public:
	using cp = control_point_t;

	curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4);
	curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const Color& color);
	curva2(const cp& p1, const cp& p2, const cp& p3, const cp& p4, const ShapeTraits& traits);

	shape_ptr_t clone() const;

	point_t center() const { return m_center; }

	void shift(const matrix3f& shift, const matrix3f& toWindow);
	void scale(const matrix3f& scale, const matrix3f& toWindow);
	void rotate(const matrix3f& rotation, const matrix3f& toWindow);

	void worldToWindow(const matrix3f& transf);
	void windowToWorld(const matrix3f& transf);

	void clip(const Clipper& clipper, edgevertex2f_t& clippedShape);

private:
	point_t m_center;
	point_t m_windowCenter;
};


#endif	 	  	 	     	   		   	      	 	    	 	
