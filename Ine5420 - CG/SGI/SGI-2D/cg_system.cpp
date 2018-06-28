#include "cg_system.h"
#include "point.h"

#define ZOOM_FACTOR 0.1f
#define SCROLL_FACTOR 0.05f
#define ROTATE_ANGLE 0.08f


CGSys::CGSys(Model& model)
    :  m_window(WinDims<unit>(0,0,800,600)), m_model(model), m_nextId(0)
{
	m_window.setLimits(model.worldSize());
	m_minimapWindow.reset(m_window.cornersWorldCoords());
}

const shape_ptr_t CGSys::addShape(std::string name, const Shape& shape) {
	shape_ptr_t ptr = m_model.addShape(shape, m_nextId++);
	ptr->worldToWindow(m_window.worldToWindow());
	ptr->name(name);
	m_mapShapes.emplace_back(Drawable(edgevertex2f_t(), shape.traits()));
	m_minimapShapes.emplace_back(Drawable(edgevertex2f_t(ptr->points()), shape.traits()));
	updateViewport(ptr);
	return ptr;
}

const shape_ptr_t CGSys::addShapeInit(std::string name, const Shape& shape) {
	shape_ptr_t ptr = m_model.addShape(shape, m_nextId++);
	ptr->name(name);
	m_mapShapes.emplace_back(Drawable(edgevertex2f_t(), shape.traits()));
	m_minimapShapes.emplace_back(Drawable(edgevertex2f_t(ptr->points()), shape.traits()));
	return ptr;
}

void CGSys::init() {
	updateViewportTransf();
	worldToWindow();
}	 	  	 	     	   		   	      	 	    	 	

void CGSys::zoomIn() {
    m_window.scale(1 - ZOOM_FACTOR, 1 - ZOOM_FACTOR);
	worldToWindow();
}
void CGSys::zoomOut() {
    m_window.scale(1 + ZOOM_FACTOR, 1 + ZOOM_FACTOR);
	worldToWindow();
}

void CGSys::scrollUp() {
    m_window.yShiftF(SCROLL_FACTOR);
	worldToWindow();
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
	m_window.rotate(m_windowRotationL);
	worldToWindow();
}
void CGSys::rotateRight() {
	m_window.rotate(m_windowRotationR);
	worldToWindow();
}

void CGSys::objectShiftU(const shape_ptr_t& shape) {	 	  	 	     	   		   	      	 	    	 	
	shape->shift(m_yshiftU, m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectShiftD(const shape_ptr_t& shape) {
	shape->shift(m_yshiftD, m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectShiftL(const shape_ptr_t& shape) {
	shape->shift(m_xshiftL, m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectShiftR(const shape_ptr_t& shape) {
	shape->shift(m_xshiftR, m_window.worldToWindow());
	updateViewport(shape);
}

void CGSys::objectScaleU(const shape_ptr_t& shape) {
	shape->scale(scalec3f(scaleFactorU, scaleFactorU, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectScaleD(const shape_ptr_t& shape) {
	shape->scale(scalec3f(scaleFactorD, scaleFactorD, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}

void CGSys::objectRotateL(const shape_ptr_t& shape) {
	shape->rotate(rotatec3f(rotationAngle, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}
void CGSys::objectRotateR(const shape_ptr_t& shape) {
	shape->rotate(rotatec3f(-rotationAngle, shape->center()), m_window.worldToWindow());
	updateViewport(shape);
}

void CGSys::initWindow(const WinDims<unit>& windowSize) {
	m_window.resize(windowSize);
	matrix3f transf = m_window.worldToWindow();
}	 	  	 	     	   		   	      	 	    	 	

void CGSys::initMap(const WinDims<unsigned int>& mapSize) {
	m_map.resize(mapSize);
}
void CGSys::initMinimap(const WinDims<unsigned int>& minimapSize) {
	m_minimap.resize(minimapSize);
}

void CGSys::resizeWindow(const WinDims<unit>& windowSize) {
	m_window.resize(windowSize);
	matrix3f transf = m_window.worldToWindow();
	std::vector<shape_ptr_t>& worldShapes = m_model.getShapes();
	for (auto& shape : worldShapes) {
		shape->worldToWindow(m_window.worldToWindow());
	}
	updateViewports();
}

void CGSys::resizeMap(const WinDims<unsigned int>& mapSize) {
	m_map.resize(mapSize);
	updateMapViewportTransf();
	updateViewports();
}

void CGSys::resizeMinimap(const WinDims<unsigned int>& minimapSize) {
	m_minimap.resize(minimapSize);
	updateMinimapViewportTransf();
	updateViewports();
}


void CGSys::worldToWindow() {
	std::vector<shape_ptr_t>& worldShapes = m_model.getShapes();
	matrix3f transf = m_window.worldToWindow();
	for (auto& shape : worldShapes) {
		shape->worldToWindow(transf);
		updateViewport(shape);
	}	 	  	 	     	   		   	      	 	    	 	
	updateMinimapWindow();
}


void CGSys::updateViewport(const shape_ptr_t& shape) {
	shape->clip(m_clipper, m_mapShapes[shape->id()].shape);
	m_winvpMap >> m_mapShapes[shape->id()].shape.vertices();
	m_minimapShapes[shape->id()].shape.copy(shape->points());
	m_winvpMinimap >> m_minimapShapes[shape->id()].shape.vertices();

}

void CGSys::updateMinimapWindow() {
	m_minimapWindow.copy(m_window.cornersWorldCoords());
	m_winvpMinimap >> m_minimapWindow.vertices();
}


void CGSys::updateViewports() {
	std::vector<shape_ptr_t>& worldShapes = m_model.getShapes();
	for (auto& shape : worldShapes) {
		updateViewport(shape);
	}
	updateMinimapWindow();
}

void CGSys::updateViewportTransf() {
	m_winvpMap = winvp3f(m_window.dims(), m_map.size());
	m_winvpMinimap = winvp3f(m_model.worldSize(), m_minimap.size());
}

void CGSys::updateMapViewportTransf() {
	m_winvpMap = winvp3f(m_window.dims(), m_map.size());
}

void CGSys::updateMinimapViewportTransf() {	 	  	 	     	   		   	      	 	    	 	
	m_winvpMinimap = winvp3f(m_model.worldSize(), m_minimap.size());
}

void CGSys::setWireframeClippingAlgorithm(WireframeClippingAlgs alg) {
	m_clipper.setWireframeClipping(alg);
}
void CGSys::setPolygonClippingAlgorithm(PolygonClippingAlgs alg) {
	m_clipper.setPolygonClipping(alg);
}