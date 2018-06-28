#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "types.h"
#include "object_traits.h"

struct Drawable {
	Drawable(const shape2_t& sh, const ObjectTraits& tr)
		: shape(sh), traits(tr)
	{
		//Object.reset(tr.closed);
	}
	shape2_t shape;
	ObjectTraits traits;
};


#endif