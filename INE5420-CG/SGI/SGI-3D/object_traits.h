#ifndef OBJECT_TRAITS_H
#define OBJECT_TRAITS_H

#include "color.h"

struct ObjectTraits {
	ObjectTraits() 
		: ObjectTraits(Color(), false, true) {}

	ObjectTraits(const Color& c, bool fill, bool close)
		:color(c), filled(fill), closed(close) {}

	Color color;
	bool filled;
	bool closed;
};


#endif
