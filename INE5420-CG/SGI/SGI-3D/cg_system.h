#ifndef CG_SYSTEM_H
#define CG_SYSTEM_H

#include "object.h"
#include "window.h"
#include "viewport.h"
#include "dimensions.h"
#include "model.h"
#include "clipping.h"
#include "transforms.h"
#include "drawable.h"
#include <vector>
#include <memory>

class CGSys {

public:
    CGSys(Model& model);
	const object3_ptr_t addObject(std::string name, const object3_t& object);
	const object3_ptr_t addObjectInit(std::string name, const object3_t& object);
	void init();
    void zoomIn();
    void zoomOut();
    //void zoomFull();
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
	void initWindow(const WinDims<unit>& windowSize);
	void initMap(const WinDims<unsigned int>& mapSize);
	void initMinimap(const WinDims<unsigned int>& minimapSize);
	void resizeWindow(const WinDims<unit>& windowSize);
	void resizeMap(const WinDims<unsigned int>& mapSize);
	void resizeMinimap(const WinDims<unsigned int>& minimapSize);

	void objectShiftU(const object3_ptr_t& Object);
	void objectShiftD(const object3_ptr_t& Object);
	void objectShiftL(const object3_ptr_t& Object);
	void objectShiftR(const object3_ptr_t& Object);
	void objectShiftF(const object3_ptr_t& Object);
	void objectShiftB(const object3_ptr_t& Object);

	void objectScaleU(const object3_ptr_t& Object);
	void objectScaleD(const object3_ptr_t& Object);

	void objectXRotateAc(const object3_ptr_t& Object);
	void objectXRotateC(const object3_ptr_t& Object);
	void objectYRotateAc(const object3_ptr_t& Object);
	void objectYRotateC(const object3_ptr_t& Object);
	void objectZRotateAc(const object3_ptr_t& Object);
	void objectZRotateC(const object3_ptr_t& Object);

	

	std::vector<Drawable>& mapObjects() { return m_mapObjects; }	 	  	 	     	   		   	      	 	    	 	
	std::vector<Drawable>& minimapObjects() { return m_minimapObjects; }
	shape2_t& minimapWindow() { return m_minimapWindow; }

	void setWireframeClippingAlgorithm(WireframeClippingAlgs alg);
	void setPolygonClippingAlgorithm(PolygonClippingAlgs alg);

	void setPerspective(bool persp) { 
		m_perspective = persp; 
		worldToWindow();
	}
	
private:
    Window m_window;
    Model& m_model;
    Viewport m_map;
    Viewport m_minimap;

	Clipper m_clipper;
	shape2_t m_clippedObject;

	std::vector<Drawable> m_mapObjects;
	std::vector<Drawable> m_minimapObjects;
	shape2_t m_minimapWindow;

	//std::vector<std::pair<vp_Object_t, size_t>> m_mapObjects;
	//vp_Objects_t m_mapObjects;
	
	ObjectId_t m_nextId;

	//void clip(const Object2_ptr_t& Object);

	void worldToWindow();
	void updateViewports();
	void updateViewport(const object3_ptr_t& Object);
	void updateViewportTransf();
	void updateMapViewportTransf();
	void updateMinimapViewportTransf();
	void updateMinimapWindow();


	const double scaleFactorU = 1.1;
	const double scaleFactorD = 0.9;
	const double rotationAngle = 0.1;
	const shift4f m_xshiftR = shift4f(20, 0.0, 0.0);
	const shift4f m_xshiftL = shift4f(-20, 0.0, 0.0);
	const shift4f m_yshiftU = shift4f(0.0, 20, 0.0);
	const shift4f m_yshiftD = shift4f(0.0, -20, 0.0);
	const shift4f m_zshiftF = shift4f(0.0, 0.0, 20);
	const shift4f m_zshiftB = shift4f(0.0, 0.0, -20);

	const angle_t m_windowRotationAngle = 0.1;
	const xrotate4f m_windowXRotationC = xrotate4f(-m_windowRotationAngle);
	const xrotate4f m_windowXRotationAc = xrotate4f(m_windowRotationAngle);
	const yrotate4f m_windowYRotationC = yrotate4f(-m_windowRotationAngle);
	const yrotate4f m_windowYRotationAc = yrotate4f(m_windowRotationAngle);
	const zrotate4f m_windowZRotationC = zrotate4f(-m_windowRotationAngle);
	const zrotate4f m_windowZRotationAc = zrotate4f(m_windowRotationAngle);

	bool m_perspective;

	winvp3f m_winvpMap;
	winvp3f m_winvpMinimap;
    
};

#endif	 	  	 	     	   		   	      	 	    	 	
