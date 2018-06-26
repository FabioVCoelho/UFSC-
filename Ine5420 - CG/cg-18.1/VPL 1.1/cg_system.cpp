#include "cg_system.h"
#include "point.h"
#include "algebra.h"

#define ZOOM_FACTOR 0.1f
#define SCROLL_FACTOR 0.01f

CGSys::CGSys(const Model& model)
    :  m_window(Dims2d<int>(0,800,0,600)), m_model(model)
{
	m_window.setLimits(model.worldSize());
}

void CGSys::zoomIn() {
    m_window.scale(1 - ZOOM_FACTOR, 1 - ZOOM_FACTOR);
}
void CGSys::zoomOut() {
    m_window.scale(1 + ZOOM_FACTOR, 1 + ZOOM_FACTOR);
}
//void CGSys::zoomFull() {
//    m_window.
//}
void CGSys::scrollUp() {
    m_window.yShift(SCROLL_FACTOR);
}
void CGSys::scrollDown() {
    m_window.yShift(-SCROLL_FACTOR);
}
void CGSys::scrollLeft() {
    m_window.xShift(-SCROLL_FACTOR);
}
void CGSys::scrollRight() {
    m_window.xShift(SCROLL_FACTOR);
}

void CGSys::resizeMap(const Dims2d<int>& mapSize) {
	m_map.resize(mapSize);
}

void CGSys::resizeMinimap(const Dims2d<int>& minimapSize) {
	m_minimap.resize(minimapSize);
}

void CGSys::resizeWindow(const Dims2d<int>& windowSize) {
	m_window.resize(windowSize);
}

void CGSys::viewportShapes(
	std::vector<Shape::shape_ptr>& shapes,
	const Dims2d<int>& win,
	const Dims2d<int>& vp
) const
{
	std::vector<Shape::shape_ptr>& worldShapes = m_model.getShapes();
	for (auto& shape : worldShapes) {	
		points_t points = shape->points();
		Shape::shape_ptr shape_vp = shape->clone();
		shape_vp->morph(winVpTransf(points, win, vp));
		shapes.push_back(std::move(shape_vp));
	}
}

std::vector<Shape::shape_ptr> CGSys::mapShapes() {
	std::vector<Shape::shape_ptr> shapes;
	viewportShapes(shapes, m_window.size(), m_map.size());
	return shapes;
}

std::vector<Shape::shape_ptr> CGSys::minimapShapes() {
	std::vector<Shape::shape_ptr> shapes;
	viewportShapes(shapes, m_model.worldSize(), m_minimap.size());
	return shapes;
}

points_t CGSys::minimapWindow() {
	const Dims2d<int>& win = m_window.size();
	points_t window {
		{win.xMin, win.yMin},
		{win.xMax, win.yMin},
		{win.xMax, win.yMax},
		{win.xMin, win.yMax}
	};
	return winVpTransf(window, m_model.worldSize(), m_minimap.size());
}
