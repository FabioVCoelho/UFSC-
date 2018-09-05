 #include "control.h"
#include <cassert>

Control::Control(Model& model, CGSys& cg)
	: m_model(model), m_cg(cg)
{}

void Control::addObject(std::string name, const object_t<3>& Object) {
	m_worldObjects[name] = m_cg.addObject(name, Object);
}

void Control::addObjectInit(std::string name, const object_t<3>& Object) {
	m_worldObjects[name] = m_cg.addObjectInit(name, Object);
}

void Control::init() {
	m_cg.init();
}

void Control::zoomIn() {
    m_cg.zoomIn();
}

void Control::zoomOut() {
    m_cg.zoomOut();
}


void Control::scrollUp() {
	m_cg.scrollUp();
}
void Control::scrollDown() {
	m_cg.scrollDown(); 
}
void Control::scrollLeft() {
	m_cg.scrollLeft();
}	 	  	 	     	   		   	      	 	    	 	
void Control::scrollRight() {
	m_cg.scrollRight();
}
void Control::windowXRotateAc() {
	m_cg.windowXRotateAc();
}
void Control::windowXRotateC() {
	m_cg.windowXRotateC();
}
void Control::windowYRotateAc() {
	m_cg.windowYRotateAc();
}
void Control::windowYRotateC() {
	m_cg.windowYRotateC();
}
void Control::windowZRotateAc() {
	m_cg.windowZRotateAc();
}
void Control::windowZRotateC() {
	m_cg.windowZRotateC();
}

void Control::objectShiftU(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectShiftU(m_worldObjects[objName]);
}

void Control::objectShiftD(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectShiftD(m_worldObjects[objName]);
}

void Control::objectShiftL(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectShiftL(m_worldObjects[objName]);
}	 	  	 	     	   		   	      	 	    	 	

void Control::objectShiftR(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectShiftR(m_worldObjects[objName]);
}

void Control::objectShiftF(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectShiftF(m_worldObjects[objName]);
}

void Control::objectShiftB(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectShiftB(m_worldObjects[objName]);
}

void Control::objectScaleU(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectScaleU(m_worldObjects[objName]);
}

void Control::objectScaleD(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectScaleD(m_worldObjects[objName]);
}

void Control::objectXRotateAc(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectXRotateAc(m_worldObjects[objName]);
}
void Control::objectXRotateC(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectXRotateC(m_worldObjects[objName]);
}
void Control::objectYRotateAc(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectYRotateAc(m_worldObjects[objName]);
}	 	  	 	     	   		   	      	 	    	 	
void Control::objectYRotateC(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectYRotateC(m_worldObjects[objName]);
}
void Control::objectZRotateAc(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectZRotateAc(m_worldObjects[objName]);
}
void Control::objectZRotateC(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_cg.objectZRotateC(m_worldObjects[objName]);
}

void Control::initWindow(const WinDims<unit>& windowSize) {
	m_cg.initWindow(windowSize);
}

void Control::initMap(const WinDims<unsigned int>& mapSize) {
	m_cg.initMap(mapSize);
}

void Control::initMinimap(const WinDims<unsigned int>& minimapSize) {
	m_cg.initMinimap(minimapSize);
}

void Control::resizeMap(const WinDims<unsigned int>& mapSize) {
	m_cg.resizeMap(mapSize);
}

void Control::resizeMinimap(const WinDims<unsigned int>& minimapSize) {
	m_cg.resizeMinimap(minimapSize);
}

void Control::resizeWindow(const WinDims<unit>& windowSize) {
	m_cg.resizeWindow(windowSize);
}	 	  	 	     	   		   	      	 	    	 	

std::vector<Drawable>* Control::mapObjects() {
	 //m_cg.updateViewports();
	 return &m_cg.mapObjects();
 }

std::vector<Drawable>* Control::minimapObjects() {
	 //m_cg.updateViewports();
	 return &m_cg.minimapObjects();
 }

shape_t<2>* Control::minimapWindow() {
	 return &m_cg.minimapWindow();
 }

bool Control::objectExists(std::string objName) {
	return (m_worldObjects.find(objName) != m_worldObjects.end());
}

void Control::setPerspective(bool persp) {
	m_cg.setPerspective(persp);
}

 std::vector<std::pair<std::string, std::string >> Control::fromObj() {
	std::vector<std::pair<std::string, std::string >> objs;
	for (const auto& pair : m_worldObjects) {
		objs.push_back({ pair.first, pair.second->shape().vertices().size() > 2 ? "Wireframe" : "Line" });
}
	return objs;
}	 	  	 	     	   		   	      	 	    	 	
