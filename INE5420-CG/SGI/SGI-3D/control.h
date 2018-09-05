#ifndef CONTROL_H
#define CONTROL_H

#include "model.h"
#include "cg_system.h"
#include <vector>
#include <map>

class Control {
public:
	Control(Model& model, CGSys& cg);
	void addObjectInit(std::string name, const object_t<3>& Object);
	void addObject(std::string name, const object_t<3>& Object);

	void init();

	void zoomIn();
	void zoomOut();
	void scrollUp();
	void scrollDown();
	void scrollLeft();
	void scrollRight();

	void windowXRotateAc();
	void windowXRotateC();
	void windowYRotateAc();
	void windowYRotateC();
	void windowZRotateAc();
	void windowZRotateC();

	void objectShiftU(std::string objName);
	void objectShiftD(std::string objName);
	void objectShiftL(std::string objName);
	void objectShiftR(std::string objName);
	void objectShiftF(std::string objName);
	void objectShiftB(std::string objName);

	void objectScaleU(std::string objName);
	void objectScaleD(std::string objName);

	/*void objectRotateL(std::string objName);
	void objectRotateR(std::string objName);*/
	void objectXRotateAc(std::string objName);
	void objectXRotateC(std::string objName);
	void objectYRotateAc(std::string objName);
	void objectYRotateC(std::string objName);
	void objectZRotateAc(std::string objName);
	void objectZRotateC(std::string objName);

	void initWindow(const WinDims<unit>& windowSize);
	void initMap(const WinDims<unsigned int>& mapSize);
	void initMinimap(const WinDims<unsigned int>& minimapSize);

	void resizeMap(const WinDims<unsigned int>& mapSize);
	void resizeMinimap(const WinDims<unsigned int>& minimapSize);
	void resizeWindow(const WinDims<unit>& windowSize);

	std::vector<Drawable>* mapObjects();
	std::vector<Drawable>* minimapObjects();
	shape_t<2>* minimapWindow();

	bool objectExists(std::string objName);

	void setPerspective(bool persp);

	std::vector<std::pair<std::string, std::string >> fromObj();

 private:
     Model& m_model;
     CGSys& m_cg;
	 std::map<std::string, object_ptr_t<3>> m_worldObjects;


 };

 #endif	 	  	 	     	   		   	      	 	    	 	
