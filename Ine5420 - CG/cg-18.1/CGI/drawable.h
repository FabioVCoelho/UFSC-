#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "types.h"
#include "shape_traits.h"

struct Drawable {
	Drawable(const edgevertex2f_t& sh, const ShapeTraits& tr)
		: shape(sh), traits(tr)
	{
		shape.reset(tr.closed);
	}
	edgevertex2f_t shape;
	ShapeTraits traits;
};


#endif