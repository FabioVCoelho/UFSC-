 #ifndef CONTROL_H
 #define CONTROL_H

 #include "model.h"
 #include "cg_system.h"
 #include "geometry.h"
 #include <vector>
#include <map>

class Control {
public:
	Control(Model& model, CGSys& cg);
	void addShape(std::string name, const Shape& shape);

	void zoomIn();
	void zoomOut();
	void scrollUp();
	void scrollDown();
	void scrollLeft();
	void scrollRight();

	void rotateLeft();
	void rotateRight();

	void objectShiftU(std::string objName);
	void objectShiftD(std::string objName);
	void objectShiftL(std::string objName);
	void objectShiftR(std::string objName);

	void objectScaleU(std::string objName);
	void objectScaleD(std::string objName);

	void objectRotateL(std::string objName);
	void objectRotateR(std::string objName);

	void resizeMap(const Dims2d<int>& mapSize);
	void resizeMinimap(const Dims2d<int>& minimapSize);

	std::vector<Shape::shape_ptr_t>* mapShapes();
	std::vector<Shape::shape_ptr_t>* minimapShapes();
	points_t* minimapWindow();

	bool objectExists(std::string objName);

 private:
     Model& m_model;
     CGSys& m_cg;
	 std::map<std::string, Shape::shape_ptr_t> m_worldObjects;


 };

 #endif