#ifndef ALGEBRA_H
#define ALGEBRA_H

#include "window.h"
#include "dimensions.h"
#include "types.h"
#include <cassert>


//void winVpTransf(
//	points_t& vpcoords,
//	const points_t& coords,
//	const Dims2d<int>& win,
//	const Dims2d<int>& vp
//);

vp_shape_t winVpTransf(
	const window_shape_t& winshape,
	const WinDims<unit>& windims,
	const WinDims<int>& vpdims
);

void winVpTransf(
	vp_shape_t& vpshapes,
	const window_shape_t& winshape,
	const WinDims<unit>& windims,
	const WinDims<int>& vpdims
);

vp_shapes_t winVpTransf(
	const window_shapes_t& wincoords,
	const WinDims<unit>& win,
	const WinDims<int>& vp
);

void winVpTransf(
	vp_shapes_t& vpshapes,
	const window_shapes_t& winshapes,
	const WinDims<unit>& win,
	const WinDims<int>& vp
);

//void transform(points_t& points, tranform_t transf);


#endif


