#include "algebra.h"

//void winVpTransf(
//	points_t& vpcoords,
//	const points_t& coords,
//	const Dims2d<int>& win,
//	const Dims2d<int>& vp
//)
//{
//	//points_t vpCoords;
//	assert(vpcoords.size() == coords.size());
//	for (size_t i = 0; i < vpcoords.size(); ++i) {
//		auto& point = coords[i];
//		auto& vppoint = vpcoords[i];
//		vppoint[0] = int(1.0f * (point[0] - win.xMin) * (vp.xMax - vp.xMin) / (win.xMax - win.xMin));
//		vppoint[1] = int((1 - (1.0f *(point[1] - win.yMin)) / (win.yMax - win.yMin)) * (vp.yMax - vp.yMin));
//	}
//}

vp_shape_t winVpTransf(
	const window_shape_t& winshape,
	const WinDims<unit>& windims,
	const WinDims<int>& vpdims
)
{
	vp_shape_t vpshape(winshape.size());
	for (size_t p = 0; p < vpshape.size(); ++p) {
		auto& vppoint = vpshape[p];
		auto& winpoint = winshape[p];
		vppoint[0] = int(1.0f * (winpoint[0] - windims.xmin) * (vpdims.width) / windims.width);
		vppoint[1] = int((1 - (1.0f *(winpoint[1] - windims.ymin)) / windims.height) * (vpdims.height));
	}
	return vpshape;
}

void winVpTransf(
	vp_shape_t& vpshape,
	const window_shape_t& winshape,
	const WinDims<unit>& windims,
	const WinDims<int>& vpdims
)
{
	assert(vpshape.size() == winshape.size());
	for (size_t p = 0; p < vpshape.size(); ++p) {
		auto& vppoint = vpshape[p];
		auto& winpoint = winshape[p];
		vppoint[0] = int(1.0f * (winpoint[0] - windims.xmin) * (vpdims.width) / windims.width);
		vppoint[1] = int((1 - (1.0f *(winpoint[1] - windims.ymin)) / windims.height) * (vpdims.height));
	}
}

vp_shapes_t winVpTransf(
	const window_shapes_t& winshapes,
	const WinDims<unit>& windims,
	const WinDims<int>& vpdims
)
{
	vp_shapes_t vpshapes(winshapes.size());
	for (size_t s = 0; s < vpshapes.size(); ++s) {
		auto& winshape = winshapes[s];
		auto& vpshape = vpshapes[s];
		for (size_t p = 0; p < vpshapes.size(); ++p) {
			auto& wpoint = winshape[p];
			auto& vppoint = vpshape[p];
			vppoint[0] = int(1.0f * (wpoint[0] - windims.xmin) * (vpdims.width) / windims.width);
			vppoint[1] = int((1 - (1.0f *(wpoint[1] - windims.ymin)) / windims.height) * (vpdims.height));
		}
	}
	return vpshapes;
}

void winVpTransf(
	vp_shapes_t& vpshapes,
	const window_shapes_t& winshapes,
	const WinDims<unit>& windims,
	const WinDims<int>& vpdims
)
{
	assert(vpshapes.size() == winshapes.size());
	for (size_t s = 0; s < vpshapes.size(); ++s) {
		auto& winshape = winshapes[s];
		auto& vpshape = vpshapes[s];
		for (size_t p = 0; p < vpshapes.size(); ++p) {
			auto& wpoint = winshape[p];
			auto& vppoint = vpshape[p];
			vppoint[0] = int(1.0f * (wpoint[0] - windims.xmin) * (vpdims.width) / windims.width);
			vppoint[1] = int((1 - (1.0f *(wpoint[1] - windims.ymin)) / windims.height) * (vpdims.height));
		}
	}
}

//vp_shape_t winVpTransf(
//	const window_shape_t& winshape,
//	const WinDims<unit>& windims,
//	const WinDims<int>& vpdims
//) 
//{
//	vp_shape_t vpshape = winshape;
//	for (auto& point : vpshape) {
//		point[0] = int(1.0f * (point[0] - windims.xmin) * (vpdims.width) / windims.width);
//		point[1] = int((1 - (1.0f *(point[1] - windims.ymin)) / windims.height) * (vpdims.height));
//	}
//	return vpshape;
//}
//
//void winVpTransf(
//	vp_shape_t& vpshape,
//	const window_shape_t& winshape,
//	const WinDims<unit>& windims,
//	const WinDims<int>& vpdims
//)
//{
//	assert(vpshape.size() == winshape.size());
//	for (size_t p = 0; p < vpshape.size(); ++p) {
//		auto& vppoint = vpshape[p];
//		auto& winpoint = winshape[p];
//		vppoint[0] = int(1.0f * (winpoint[0] - windims.xmin) * (vpdims.width) / windims.width);
//		vppoint[1] = int((1 - (1.0f *(winpoint[1] - windims.ymin)) / windims.height) * (vpdims.height));
//	}
//}
//
//vp_shapes_t winVpTransf(
//	const window_shapes_t& winshapes,
//	const WinDims<unit>& windims,
//	const WinDims<int>& vpdims
//)
//{
//	vp_shapes_t vpshapes = winshapes;
//	for (auto& shape : vpshapes) {
//		for (auto& point : shape) {
//			point[0] = int(1.0f * (point[0] - windims.xmin) * (vpdims.width) / windims.width);
//			point[1] = int((1 - (1.0f *(point[1] - windims.ymin)) / windims.height) * (vpdims.height));
//		}
//	}
//	return vpshapes;
//}
//
//void winVpTransf(
//	vp_shapes_t& vpshapes,
//	const window_shapes_t& winshapes,
//	const WinDims<unit>& windims,
//	const WinDims<int>& vpdims
//) 
//{
//	assert(vpshapes.size() == winshapes.size());
//	for (size_t s = 0; s < vpshapes.size(); ++s) {
//		auto& winshape = winshapes[s];
//		auto& vpshape = vpshapes[s];
//		for (size_t p = 0; p < vpshapes.size(); ++p) {
//			auto& wpoint = winshape[p];
//			auto& vppoint = vpshape[p];
//			vppoint[0] = int(1.0f * (wpoint[0] - windims.xmin) * (vpdims.width) / windims.width);
//			vppoint[1] = int((1 - (1.0f *(wpoint[1] - windims.ymin)) / windims.height) * (vpdims.height));
//		}
//	}
//}



//void transform(points_t& points, tranform_t transf) {
//	transf * points;
//}