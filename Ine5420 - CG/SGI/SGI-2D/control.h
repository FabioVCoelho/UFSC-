#ifndef CONTROL_H
#define CONTROL_H

#include "model.h"
#include "cg_system.h"
#include <vector>
#include <map>

class Control {
public:
	Control(Model& model, CGSys& cg);
	void addShapeInit(std::string name, const Shape& shape);
	void addShape(std::string name, const Shape& shape);

	void init();

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

	void initWindow(const WinDims<unit>& windowSize);
	void initMap(const WinDims<unsigned int>& mapSize);
	void initMinimap(const WinDims<unsigned int>& minimapSize);

	void resizeMap(const WinDims<unsigned int>& mapSize);
	void resizeMinimap(const WinDims<unsigned int>& minimapSize);
	void resizeWindow(const WinDims<unit>& windowSize);

	std::vector<Drawable>* mapShapes();
	std::vector<Drawable>* minimapShapes();
	edgevertex2f_t* minimapWindow();

	bool objectExists(std::string objName);

	std::vector<std::pair<std::string, std::string >> fromObj();

 private:
     Model& m_model;
     CGSys& m_cg;
	 std::map<std::string, shape_ptr_t> m_worldObjects;


 };

 #endif	 	  	 	     	   		   	      	 	    	 	
