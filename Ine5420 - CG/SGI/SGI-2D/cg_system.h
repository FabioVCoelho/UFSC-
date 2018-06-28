#ifndef CG_SYSTEM_H
#define CG_SYSTEM_H

#include "shape.h"
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
	const shape_ptr_t addShape(std::string name, const Shape& shape);
	const shape_ptr_t addShapeInit(std::string name, const Shape& shape);
	void init();
    void zoomIn();
    void zoomOut();
    //void zoomFull();
    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
	void rotateLeft();
	void rotateRight();
	void initWindow(const WinDims<unit>& windowSize);
	void initMap(const WinDims<unsigned int>& mapSize);
	void initMinimap(const WinDims<unsigned int>& minimapSize);
	void resizeWindow(const WinDims<unit>& windowSize);
	void resizeMap(const WinDims<unsigned int>& mapSize);
	void resizeMinimap(const WinDims<unsigned int>& minimapSize);

	void objectShiftU(const shape_ptr_t& shape);
	void objectShiftD(const shape_ptr_t& shape);
	void objectShiftL(const shape_ptr_t& shape);
	void objectShiftR(const shape_ptr_t& shape);

	void objectScaleU(const shape_ptr_t& shape);
	void objectScaleD(const shape_ptr_t& shape);

	void objectRotateL(const shape_ptr_t& shape);
	void objectRotateR(const shape_ptr_t& shape);
	

	std::vector<Drawable>& mapShapes() { return m_mapShapes; }	 	  	 	     	   		   	      	 	    	 	
	std::vector<Drawable>& minimapShapes() { return m_minimapShapes; }
	edgevertex2f_t& minimapWindow() { return m_minimapWindow; }

	void setWireframeClippingAlgorithm(WireframeClippingAlgs alg);
	void setPolygonClippingAlgorithm(PolygonClippingAlgs alg);
	
	
private:
    Window m_window;
    Model& m_model;
    Viewport m_map;
    Viewport m_minimap;

	Clipper m_clipper;
	edgevertex2f_t m_clippedShape;

	std::vector<Drawable> m_mapShapes;
	std::vector<Drawable> m_minimapShapes;
	edgevertex2f_t m_minimapWindow;

	//std::vector<std::pair<vp_shape_t, size_t>> m_mapShapes;
	//vp_shapes_t m_mapShapes;
	
	shapeId_t m_nextId;

	//void clip(const shape_ptr_t& shape);

	void worldToWindow();
	void updateViewports();
	void updateViewport(const shape_ptr_t& shape);
	void updateViewportTransf();
	void updateMapViewportTransf();
	void updateMinimapViewportTransf();
	void updateMinimapWindow();


	const double scaleFactorU = 1.1;
	const double scaleFactorD = 0.9;
	const double rotationAngle = 0.1;
	const shift3f m_xshiftR = shift3f(20, 0.0);
	const shift3f m_xshiftL = shift3f(-20, 0.0);
	const shift3f m_yshiftU = shift3f(0.0, 20);
	const shift3f m_yshiftD = shift3f(0.0, -20);

	const angle_t m_windowRotationAngle = 0.1;
	const rotate3f m_windowRotationL = rotate3f(m_windowRotationAngle);
	const rotate3f m_windowRotationR = rotate3f(-m_windowRotationAngle);

	winvp3f m_winvpMap;
	winvp3f m_winvpMinimap;
    
};

#endif	 	  	 	     	   		   	      	 	    	 	
