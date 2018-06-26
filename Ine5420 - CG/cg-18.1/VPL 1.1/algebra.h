#ifndef ALGEBRA_H
#define ALGEBRA_H

#include "dimensions.h"
#include <vector>

using point_t = std::pair<int, int>;
using points_t = std::vector<point_t>;

points_t winVpTransf(
    const points_t& coords, 
    const Dims2d<int>& win,
    const Dims2d<int>& vp
)
{
    points_t vpCoords;
	for (auto point : coords) {
		auto xw = point.first;
		auto yw = point.second;
		auto xVp = int(1.0f * (xw - win.xMin) * (vp.xMax - vp.xMin) / (win.xMax - win.xMin));
		auto yVp = int((1 - (1.0f *(yw - win.yMin)) / (win.yMax - win.yMin)) * (vp.yMax - vp.yMin));
		vpCoords.push_back(point_t(xVp, yVp));
	}
	return vpCoords;
}


#endif


