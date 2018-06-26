#ifndef ALGEBRA_H
#define ALGEBRA_H

#include "dimensions.h"
#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "matrix.h"
#include <vector>
#include <cassert>

using point_t = Vec2f;
using points_t = std::vector<point_t>;
using tranform_t = matrix3f;
using unit = double;


void winVpTransf(
	points_t& vpcoords,
	const points_t& coords,
	const Dims2d<int>& win,
	const Dims2d<int>& vp
);

//void transform(points_t& points, tranform_t transf);


#endif


