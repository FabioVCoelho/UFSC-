#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "types.h"
#include "color.h"

struct Drawable {
	Drawable(const edgevertex2f_t& sh, const Color& c, bool fill)
		: shape(sh), color(c), filled(fill)
	{
		shape.reset();
	}
	edgevertex2f_t shape;
	Color color;
	bool filled;
};


#endif