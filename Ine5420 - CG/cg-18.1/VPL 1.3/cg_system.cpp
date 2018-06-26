#include "cg_system.h"
#include "point.h"
#include "algebra.h"
#include "transforms.h"

#define ZOOM_FACTOR 0.1f
#define SCROLL_FACTOR 0.05f
#define ROTATE_ANGLE 0.08f


CGSys::CGSys(Model& model)
    :  m_window(WinDims<unit>(0,0,800,600)), m_model(model), m_nextId(0)
{
	m_window.setLimits(model.worldSize());
}

const Shape::shape_ptr_t CGSys::addShape(std::string name, const Shape& shape) {
	Shape::shape_ptr_t ptr = m_model.addShape(shape, m_nextId++);
	ptr->worldToWindow(m_window.worldToWindow());
	ptr->name(name);
	m_mapShapes.push_back(winVpTransf(ptr->windowPoints(), m_window.dims(), m_map.size()));
	m_minimapShapes.push_back(winVpTransf(ptr->points(), m_model.worldSize(), m_minimap.size()));
	return ptr;
}

void CGSys::zoomIn() {
    m_window.scale(1 - ZOOM_FACTOR, 1 - ZOOM_FACTOR);
	worldToWindow();
}
void CGSys::zoomOut() {
    m_window.scale(1 + ZOOM_FACTOR, 1 + ZOOM_FACTOR);
	worldToWindow();
}
//void CGSys::zoomFull() {
//    m_window.
//}
void CGSys::scrollUp() {
    m_window.yShiftF(SCROLL_FACTOR);
	worldToWindow();
	//updateViewports;
}
void CGSys::scrollDown() {
    m_window.yShiftF(-SCROLL_FACTOR);
	worldToWindow();
}
void CGSys::scrollLeft() {
    m_window.xShiftF(-SCROLL_FACTOR);
	worldToWindow();
}
void CGSys::scrollRight() {
    m_window.xShiftF(SCROLL_FACTOR);
	worldToWindow();
}
void CGSys::rotateLeft() {
	m_window.rotate(windowRotationL);
	worldToWindow();
}
void CGSys::rotateRight() {
	m_window.rotate(windowRotationR);
	worldToWindow();
}

void CGSys::objectShiftU(const Shape::shape_ptr_t& shape) {
	shape->shift(yshiftU, m_window.windowToWorld());
	updateViewport(shape);
}
void CGSys::objectShiftD(const Shape::shape_ptr_t& shape) {
	shape->shift(yshiftD, m_window.windowToWorld());
	updateViewport(shape);
}
void CGSys::objectShiftL(const Shape::shape_ptr_t& shape) {
	shape->shift(xshiftL, m_window.windowToWorld());
	updateViewport(shape);
}
void CGSys::objectShiftR(const Shape::shape_ptr_t& shape) {
	shape->shift(xshiftR, m_window.windowToWorld());
	updateViewport(shape);
}

void CGSys::objectScaleU(const Shape::shape_ptr_t& shape) {
	shape->scale(scalec3f(scaleFactorU, scaleFactorU, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectScaleD(const Shape::shape_ptr_t& shape) {
	shape->scale(scalec3f(scaleFactorD, scaleFactorD, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}

void CGSys::objectRotateL(const Shape::shape_ptr_t& shape) {
	shape->rotate(rotatec3f(rotationAngle, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectRotateR(const Shape::shape_ptr_t& shape) {
	shape->rotate(rotatec3f(-rotationAngle, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}


void CGSys::resizeMap(const WinDims<unsigned int>& mapSize) {
	m_map.resize(mapSize);
	updateViewports();
}

void CGSys::resizeMinimap(const WinDims<unsigned int>& minimapSize) {
	m_minimap.resize(minimapSize);
	updateViewports();
}

void CGSys::resizeWindow(const WinDims<unit>& windowSize) {
	m_window.resize(windowSize);
	matrix3f transf = m_window.worldToWindow();
	std::vector<Shape::shape_ptr_t>& worldShapes = m_model.getShapes();
	for (auto& shape : worldShapes) {
		shape->worldToWindow(m_window.worldToWindow());
	}
	updateViewports();
}

//void CGSys::viewportShapes(
//	vp_shapes_t& shapes,
//	const Dims2d<int>& win,
//	const Dims2d<int>& vp
//) const
//{
//	std::vector<Shape::shape_ptr_t>& worldShapes = m_model.getShapes();
//	shapes.clear();
//	for (auto& shape : worldShapes) {	
//		const points_t& points = shape->points();
//		shapes.push_back(shape->clone());
//		winVpTransf(shapes.back()->points(), points, win, vp);
//	}
//}

//vp_shapes_t& CGSys::mapShapes() {
//	winVpTransf(m_mapShapes, m_windowShapes, m_window.dims(), m_map.size());
//	return m_mapShapes;
//}
//
//vp_shapes_t& CGSys::minimapShapes() {
//	const WinDims<unit>& win = m_window.dims();
//	unit xmax = win.xmin + win.width;
//	unit ymax = win.ymin + win.height;
//	m_minimapWindow = {
//		Vec2f(win.xmin, win.ymin),
//		Vec2f(xmax, win.ymin),
//		Vec2f(xmax, ymax),
//		Vec2f(win.xmin, ymax)
//	};
//	winVpTransf(m_minimapShapes, m_windowShapes, m_model.worldSize(), m_minimap.size());
//	return m_minimapShapes;
//}


//vp_shapes_t& CGSys::mapShapes() {
//	viewportShapes(m_mapShapes, m_window.size(), m_map.size());
//	return m_mapShapes;
//}
//
//vp_shapes_t& CGSys::minimapShapes() {
//	viewportShapes(m_minimapShapes, m_model.worldSize(), m_minimap.size());
//	return m_minimapShapes;
//}

void CGSys::worldToWindow() {
	std::vector<Shape::shape_ptr_t>& worldShapes = m_model.getShapes();
	matrix3f transf = m_window.worldToWindow();
	for (auto& shape : worldShapes) {
		shape->worldToWindow(transf);
		updateViewport(shape);
	}
	updateMinimapWindow();
}


void CGSys::updateViewport(const Shape::shape_ptr_t& shape) {
	winVpTransf(m_mapShapes[shape->id()], shape->windowPoints(), m_window.dims(), m_map.size());
	winVpTransf(m_minimapShapes[shape->id()], shape->points(), m_model.worldSize(), m_minimap.size());
}

void CGSys::updateMinimapWindow() {
	const WinDims<unit>& win = m_window.dims();
	unit xmax = win.xmin + win.width;
	unit ymax = win.ymin + win.height;
	m_minimapWindow = winVpTransf(m_window.cornersWorldCoords(), m_model.worldSize(), m_minimap.size());
}


void CGSys::updateViewports() {
	std::vector<Shape::shape_ptr_t>& worldShapes = m_model.getShapes();
	for (auto& shape : worldShapes) {
		updateViewport(shape);
	}
	updateMinimapWindow();
}
