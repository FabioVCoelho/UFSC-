 #include "control.h"
#include <cassert>

Control::Control(Model& model, CGSys& cg)
	: m_model(model), m_cg(cg)
{}

 //void Control::addShape(const Shape& shape) {
 //    m_model.zoomIn();
 //}

 void Control::addShape(std::string name, const Shape& shape) {
	 m_worldObjects[name] = m_model.addShape(shape);
 }

 void Control::zoomIn() {
     m_cg.zoomIn();
	 m_cg.updateViewports();
 }

 void Control::zoomOut() {
     m_cg.zoomOut();
	 m_cg.updateViewports();
 }


 void Control::scrollUp() {
	 m_cg.scrollUp();
	 m_cg.updateViewports();
 }
 void Control::scrollDown() {
	 m_cg.scrollDown(); 
	 m_cg.updateViewports();
 }
 void Control::scrollLeft() {
	 m_cg.scrollLeft();
	 m_cg.updateViewports();
 }
 void Control::scrollRight() {
	 m_cg.scrollRight();
	 m_cg.updateViewports();
 }
 void Control::rotateRight() {
	 m_cg.rotateRight();
	 m_cg.updateViewports();
 }
 void Control::rotateLeft() {
	 m_cg.rotateLeft();
	 m_cg.updateViewports();
 }

void Control::objectShiftU(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->yShift(10);
	m_cg.updateViewports();
}

void Control::objectShiftD(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->yShift(-10);
	m_cg.updateViewports();
}

void Control::objectShiftL(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->xShift(-10);
	m_cg.updateViewports();
}

void Control::objectShiftR(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->xShift(10);
	m_cg.updateViewports();
}

void Control::objectScaleU(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->scale(1.1, 1.1);
	m_cg.updateViewports();
}

void Control::objectScaleD(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->scale(0.9, 0.9);
	m_cg.updateViewports();
}

void Control::objectRotateL(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->rotate(0.05);
	m_cg.updateViewports();
}
void Control::objectRotateR(std::string objName) {
	assert(m_worldObjects.find(objName) != m_worldObjects.end());
	m_worldObjects[objName]->rotate(-0.05);
	m_cg.updateViewports();
}


void Control::resizeMap(const Dims2d<int>& mapSize) {
	m_cg.resizeMap(mapSize);
	m_cg.updateViewports();
}

void Control::resizeMinimap(const Dims2d<int>& minimapSize) {
	m_cg.resizeMinimap(minimapSize);
	m_cg.updateViewports();
}

 std::vector<Shape::shape_ptr_t>* Control::mapShapes() {
	 m_cg.updateViewports();
	 return &m_cg.mapShapes();
 }

 std::vector<Shape::shape_ptr_t>* Control::minimapShapes() {
	 m_cg.updateViewports();
	 return &m_cg.minimapShapes();
 }

 points_t* Control::minimapWindow() {
	 return &m_cg.minimapWindow();
 }

 bool Control::objectExists(std::string objName) {
	 return (m_worldObjects.find(objName) != m_worldObjects.end());
	
 }