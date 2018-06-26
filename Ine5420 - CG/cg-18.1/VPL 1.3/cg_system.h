#ifndef CG_SYSTEM_H
#define CG_SYSTEM_H

#include "shape.h"
#include "window.h"
#include "viewport.h"
#include "dimensions.h"
#include "model.h"
#include <vector>
#include <memory>

class CGSys {

public:
    CGSys(Model& model);
	const Shape::shape_ptr_t addShape(std::string name, const Shape& shape);
    void zoomIn();
    void zoomOut();
    //void zoomFull();
    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
	void rotateLeft();
	void rotateRight();
	void resizeWindow(const WinDims<unit>& windowSize);
	void resizeMap(const WinDims<unsigned int>& mapSize);
	void resizeMinimap(const WinDims<unsigned int>& minimapSize);

	void objectShiftU(const Shape::shape_ptr_t& shape);
	void objectShiftD(const Shape::shape_ptr_t& shape);
	void objectShiftL(const Shape::shape_ptr_t& shape);
	void objectShiftR(const Shape::shape_ptr_t& shape);

	void objectScaleU(const Shape::shape_ptr_t& shape);
	void objectScaleD(const Shape::shape_ptr_t& shape);

	void objectRotateL(const Shape::shape_ptr_t& shape);
	void objectRotateR(const Shape::shape_ptr_t& shape);

	/*void worldToWindow();
	void worldToWindow(angle_t angle);*/
	/*void worldToWindow(const Shape::shape_ptr_t& shape);
	void windowToWorld(const Shape::shape_ptr_t& shape);*/
	

	vp_shapes_t& mapShapes() { return m_mapShapes; }
	vp_shapes_t& minimapShapes() { return m_minimapShapes; }
	vp_shape_t& minimapWindow() { return m_minimapWindow; }

	
	
private:
    Window m_window;
    Model& m_model;
    Viewport m_map;
    Viewport m_minimap;

	//window_shapes_t m_windowShapes;

	vp_shapes_t m_mapShapes;
	vp_shapes_t m_minimapShapes;
	vp_shape_t m_minimapWindow;

	shapeId_t m_nextId;

	void worldToWindow();
	void updateViewports();
	void updateViewport(const Shape::shape_ptr_t& shape);
	void updateMinimapWindow();


	const double scaleFactorU = 1.1;
	const double scaleFactorD = 0.9;
	const double rotationAngle = 0.1;
	const matrix3f xshiftR = shift3f(0.05, 0.0);
	const matrix3f xshiftL = shift3f(-0.05, 0.0);
	const matrix3f yshiftU = shift3f(0.0, 0.05);
	const matrix3f yshiftD = shift3f(0.0, -0.05);

	const angle_t windowRotationAngle = 0.1;
	const matrix3f windowRotationL = rotate3f(windowRotationAngle);
	const matrix3f windowRotationR = rotate3f(-windowRotationAngle);

	/*void viewportShapes(
		vp_shapes_t& shapes,
		const Dims2d<int>& win,
		const Dims2d<int>& vp
	) const;*/
    
};

#endif