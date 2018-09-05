#include "cg_system.h"
#include "point.h"

#define ZOOM_FACTOR 0.1f
#define SCROLL_FACTOR 0.05f
#define ROTATE_ANGLE 0.08f


CGSys::CGSys(Model& model)
    :  m_window(WinDims<unit>(0,0,800,600)), m_model(model), m_nextId(0), m_perspective(false)
{
	m_window.setLimits(model.worldSize());
	m_minimapWindow = shape3_t(m_window.cornersWorldCoords());
	m_minimapWindow.defaultEdges();
}

const object3_ptr_t CGSys::addObject(std::string name, const object3_t& Object) {
	object3_ptr_t ptr = m_model.addObject(Object, m_nextId++);
	ptr->worldToWindow(m_window.worldToWindow());
	ptr->name(name);
	m_mapObjects.emplace_back(Drawable(shape2_t(), Object.traits()));
	m_minimapObjects.emplace_back(Drawable(shape2_t(ptr->shape().vertices()), Object.traits()));
	updateViewport(ptr);
	return ptr;
}

const object3_ptr_t CGSys::addObjectInit(std::string name, const object3_t& Object) {
	object3_ptr_t ptr = m_model.addObject(Object, m_nextId++);
	ptr->name(name);
	m_mapObjects.emplace_back(Drawable(shape2_t(), Object.traits()));
	m_minimapObjects.emplace_back(Drawable(shape2_t(ptr->shape().vertices()), Object.traits()));
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
void CGSys::windowXRotateAc() {
	m_window.rotate(m_windowXRotationAc);
	worldToWindow();
}
void CGSys::windowXRotateC() {
	m_window.rotate(m_windowXRotationC);
	worldToWindow();
}
void CGSys::windowYRotateAc() {
	m_window.rotate(m_windowYRotationAc);
	worldToWindow();
}	 	  	 	     	   		   	      	 	    	 	
void CGSys::windowYRotateC() {
	m_window.rotate(m_windowYRotationC);
	worldToWindow();
}
void CGSys::windowZRotateAc() {
	m_window.rotate(m_windowZRotationAc);
	worldToWindow();
}
void CGSys::windowZRotateC() {
	m_window.rotate(m_windowZRotationC);
	worldToWindow();
}

void CGSys::objectShiftU(const object3_ptr_t& Object) {
	Object->shift(m_yshiftU, m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectShiftD(const object3_ptr_t& Object) {
	Object->shift(m_yshiftD, m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectShiftL(const object3_ptr_t& Object) {
	Object->shift(m_xshiftL, m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectShiftR(const object3_ptr_t& Object) {
	Object->shift(m_xshiftR, m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectShiftF(const object3_ptr_t& Object) {
	Object->shift(m_zshiftF, m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectShiftB(const object3_ptr_t& Object) {
	Object->shift(m_zshiftB, m_window.worldToWindow());
	updateViewport(Object);
}	 	  	 	     	   		   	      	 	    	 	


void CGSys::objectScaleU(const object3_ptr_t& Object) {
	Object->scale(scalec4f(scaleFactorU, scaleFactorU, scaleFactorU, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectScaleD(const object3_ptr_t& Object) {
	Object->scale(scalec4f(scaleFactorD, scaleFactorD, scaleFactorD, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}

void CGSys::objectXRotateAc(const object3_ptr_t& Object) {
	Object->rotate(xrotatec4f(rotationAngle, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectXRotateC(const object3_ptr_t& Object) {
	Object->rotate(xrotatec4f(-rotationAngle, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}

void CGSys::objectYRotateAc(const object3_ptr_t& Object) {
	Object->rotate(yrotatec4f(rotationAngle, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectYRotateC(const object3_ptr_t& Object) {
	Object->rotate(yrotatec4f(-rotationAngle, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}

void CGSys::objectZRotateAc(const object3_ptr_t& Object) {
	Object->rotate(zrotatec4f(rotationAngle, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}
void CGSys::objectZRotateC(const object3_ptr_t& Object) {
	Object->rotate(zrotatec4f(-rotationAngle, Object->center()), m_window.worldToWindow());
	updateViewport(Object);
}	 	  	 	     	   		   	      	 	    	 	

//void CGSys::objectRotateL(const object3_ptr_t& Object) {
//	Object->rotate(rotatec3f(rotationAngle, Object->center()), m_window.worldToWindow());
//	updateViewport(Object);
//}
//void CGSys::objectRotateR(const object3_ptr_t& Object) {
//	Object->rotate(rotatec3f(-rotationAngle, Object->center()), m_window.worldToWindow());
//	updateViewport(Object);
//}

void CGSys::initWindow(const WinDims<unit>& windowSize) {
	m_window.resize(windowSize);
	//matrix3f transf = m_window.worldToWindow();
}

void CGSys::initMap(const WinDims<unsigned int>& mapSize) {
	m_map.resize(mapSize);
}
void CGSys::initMinimap(const WinDims<unsigned int>& minimapSize) {
	m_minimap.resize(minimapSize);
}

void CGSys::resizeWindow(const WinDims<unit>& windowSize) {
	/*m_window.resize(windowSize);
	matrix3f transf = m_window.worldToWindow();
	std::vector<Object2_ptr_t>& worldObjects = m_model.getObjects();
	for (auto& Object : worldObjects) {
		Object->worldToWindow(m_window.worldToWindow());
	}
	updateViewports();*/
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
	std::vector<object3_ptr_t>& worldObjects = m_model.getObjects();
	transform3_t transf = m_window.worldToWindow();
	for (auto& Object : worldObjects) {
		Object->worldToWindow(transf);
		updateViewport(Object);
	}
	updateMinimapWindow();
}


void CGSys::updateViewport(const object3_ptr_t& Object) {
	if (m_perspective) {
		Object->perspective(m_window.dop());
	}
	Object->clip(m_clipper, m_mapObjects[Object->id()].shape);
	m_winvpMap >> m_mapObjects[Object->id()].shape.vertices();
	m_minimapObjects[Object->id()].shape.copy(Object->shape());
	m_winvpMinimap >> m_minimapObjects[Object->id()].shape.vertices();

}

void CGSys::updateMinimapWindow() {
	m_minimapWindow.copy(m_window.cornersWorldCoords());
	m_minimapWindow.defaultEdges();
	m_winvpMinimap >> m_minimapWindow.vertices();
}


void CGSys::updateViewports() {	 	  	 	     	   		   	      	 	    	 	
	std::vector<object3_ptr_t>& worldObjects = m_model.getObjects();
	for (auto& Object : worldObjects) {
		updateViewport(Object);
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
