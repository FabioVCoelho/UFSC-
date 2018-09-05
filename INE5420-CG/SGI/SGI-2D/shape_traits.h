#ifndef SHAPE_TRAITS_H
#define SHAPE_TRAITS_H

#include "color.h"

struct ShapeTraits {
	ShapeTraits() 
		: ShapeTraits(Color(), false, true) {}

	ShapeTraits(const Color& c, bool fill, bool close)
		:color(c), filled(fill), closed(close) {}

	Color color;
	bool filled;
	bool closed;
};


#endif
