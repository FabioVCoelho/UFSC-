#include "algebra.h"

void winVpTransf(
	points_t& vpcoords,
	const points_t& coords,
	const Dims2d<int>& win,
	const Dims2d<int>& vp
)
{
	//points_t vpCoords;
	assert(vpcoords.size() == coords.size());
	for (size_t i = 0; i < vpcoords.size(); ++i) {
		auto& point = coords[i];
		auto& vppoint = vpcoords[i];
		vppoint[0] = int(1.0f * (point[0] - win.xMin) * (vp.xMax - vp.xMin) / (win.xMax - win.xMin));
		vppoint[1] = int((1 - (1.0f *(point[1] - win.yMin)) / (win.yMax - win.yMin)) * (vp.yMax - vp.yMin));
	}
}

//void transform(points_t& points, tranform_t transf) {
//	transf * points;
//}