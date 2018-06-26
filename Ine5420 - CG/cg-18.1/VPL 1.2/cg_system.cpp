#include "cg_system.h"
#include "point.h"
#include "algebra.h"

#define ZOOM_FACTOR 0.1f
#define SCROLL_FACTOR 0.01f
#define ROTATE_ANGLE 0.08f

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
void CGSys::rotateLeft() {
	m_window.rotate(ROTATE_ANGLE);
}
void CGSys::rotateRight() {
	m_window.rotate(-ROTATE_ANGLE);
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
	std::vector<Shape::shape_ptr_t>& shapes,
	const Dims2d<int>& win,
	const Dims2d<int>& vp
) const
{
	std::vector<Shape::shape_ptr_t>& worldShapes = m_model.getShapes();
	shapes.clear();
	for (auto& shape : worldShapes) {	
		const points_t& points = shape->points();
		shapes.push_back(shape->clone());
		winVpTransf(shapes.back()->points(), points, win, vp);
	}
}

std::vector<Shape::shape_ptr_t>& CGSys::mapShapes() {
	viewportShapes(m_mapShapes, m_window.size(), m_map.size());
	return m_mapShapes;
}

std::vector<Shape::shape_ptr_t>& CGSys::minimapShapes() {
	viewportShapes(m_minimapShapes, m_model.worldSize(), m_minimap.size());
	return m_minimapShapes;
}

points_t& CGSys::minimapWindow() {
	const Dims2d<int>& win = m_window.size();
	m_minimapWindow = {
		Vec2f(win.xMin, win.yMin),
		Vec2f(win.xMax, win.yMin),
		Vec2f(win.xMax, win.yMax),
		Vec2f(win.xMin, win.yMax)
	};
	 
	winVpTransf(m_minimapWindow, m_minimapWindow, m_model.worldSize(), m_minimap.size());
	return m_minimapWindow;
}

void CGSys::updateViewports() {
	mapShapes();
	minimapShapes();
	minimapWindow();
}
