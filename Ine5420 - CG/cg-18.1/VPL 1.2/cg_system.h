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
    CGSys(const Model& model);
    void zoomIn();
    void zoomOut();
    //void zoomFull();
    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
	void rotateLeft();
	void rotateRight();
	void resizeWindow(const Dims2d<int>& windowSize);
	void resizeMap(const Dims2d<int>& mapSize);
	void resizeMinimap(const Dims2d<int>& minimapSize);

    std::vector<Shape::shape_ptr_t>& mapShapes();
    std::vector<Shape::shape_ptr_t>& minimapShapes();
    points_t& minimapWindow();
	void updateViewports();
	
private:
    Window m_window;
    const Model& m_model;
    Viewport m_map;
    Viewport m_minimap;

	std::vector<Shape::shape_ptr_t> m_mapShapes;
	std::vector<Shape::shape_ptr_t> m_minimapShapes;

	points_t m_minimapWindow;

	void viewportShapes(
		std::vector<Shape::shape_ptr_t>& shapes,
		const Dims2d<int>& win,
		const Dims2d<int>& vp
	) const;
    
};

#endif