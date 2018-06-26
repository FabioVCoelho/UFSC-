 #include "control.h"
#include <cassert>

Control::Control(Model& model, CGSys& cg)
	: m_model(model), m_cg(cg)
{}

 //void Control::addShape(const Shape& shape) {
 //    m_model.zoomIn();
 //}

 void Control::addShape(std::string name, const Shape& shape) {
	 m_worldObjects[name] = m_cg.addShape(name, shape);
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
 void Control::rotateRight() {
	 m_cg.rotateRight();
 }
 void Control::rotateLeft() {
	 m_cg.rotateLeft();
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

 void Control::objectScaleU(std::string objName) {
	 assert(m_worldObjects.find(objName) != m_worldObjects.end());
	 m_cg.objectScaleU(m_worldObjects[objName]);
 }

 void Control::objectScaleD(std::string objName) {
	 assert(m_worldObjects.find(objName) != m_worldObjects.end());
	 m_cg.objectScaleD(m_worldObjects[objName]);
 }

 void Control::objectRotateL(std::string objName) {
	 assert(m_worldObjects.find(objName) != m_worldObjects.end());
	 m_cg.objectRotateL(m_worldObjects[objName]);
 }
 void Control::objectRotateR(std::string objName) {
	 assert(m_worldObjects.find(objName) != m_worldObjects.end());
	 m_cg.objectRotateR(m_worldObjects[objName]);
 }

//void Control::objectShiftU(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->yShift(10);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//
//void Control::objectShiftD(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->yShift(-10);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//
//void Control::objectShiftL(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->xShift(-10);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//
//void Control::objectShiftR(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->xShift(10);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//
//void Control::objectScaleU(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->scale(1.1, 1.1);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//
//void Control::objectScaleD(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->scale(0.9, 0.9);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//
//void Control::objectRotateL(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->rotate(0.05);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}
//void Control::objectRotateR(std::string objName) {
//	assert(m_worldObjects.find(objName) != m_worldObjects.end());
//	m_worldObjects[objName]->rotate(-0.05);
//	m_cg.worldToWindow();
//	m_cg.updateViewports();
//}


void Control::resizeMap(const WinDims<unsigned int>& mapSize) {
	m_cg.resizeMap(mapSize);
}

void Control::resizeMinimap(const WinDims<unsigned int>& minimapSize) {
	m_cg.resizeMinimap(minimapSize);
}

void Control::resizeWindow(const WinDims<unit>& windowSize) {
	m_cg.resizeWindow(windowSize);
}

vp_shapes_t* Control::mapShapes() {
	 //m_cg.updateViewports();
	 return &m_cg.mapShapes();
 }

vp_shapes_t* Control::minimapShapes() {
	 //m_cg.updateViewports();
	 return &m_cg.minimapShapes();
 }

vp_shape_t* Control::minimapWindow() {
	 return &m_cg.minimapWindow();
 }

 bool Control::objectExists(std::string objName) {
	 return (m_worldObjects.find(objName) != m_worldObjects.end());
 }

 std::vector<std::pair<std::string, std::string >> Control::fromObj() {
	std::vector<std::pair<std::string, std::string >> objs;
	for (const auto& pair : m_worldObjects) {
		objs.push_back({ pair.first, pair.second->points().size() > 2 ? "Polygon" : "Line" });
}
	return objs;
}