#ifndef WINDOW_H
#define WINDOW_H

#include "dimensions.h"
#include "types.h"
#include "transforms.h"


class Window {
public:
    Window(const WinDims<unit>& windims);

    void setLimits(const WinDims<unit>& worldLimits);

	WinDims<unit> dims() const;

    void xShiftL(unit dx);
    void xShiftR(unit dx);
    void yShiftU(unit dy);
    void yShiftD(unit dy);
    void shift(unit dx, unit dy);

    void xShiftF(double fx);
    void yShiftF(double fy);
    void shiftF(double dx, double dy);

    void scale(double sx, double sy);

	void rotate(angle_t angle);
	void rotate(const matrix3f& rotation);

    void moveto(unit xmin, unit unit);

    void resize(const WinDims<unit>& windowSize);

	const Vec2f& center() const;

	angle_t angle() const;

	const matrix3f& scale() const { return m_scale; }	 	  	 	     	   		   	      	 	    	 	

	const matrix3f& windowToWorld() const { return m_windowToWorld; } 

	const matrix3f& worldToWindow() const { return m_worldToWindow; }

	points_t cornersWorldCoords();

private:
	unit m_width, m_height;
	
	unit m_lowerX, m_upperX, m_lowerY, m_upperY;
    double ratio;
    void updateRatio();
    void forceRatio(double r);
	Vec2f m_center;
	Vec2f m_up, m_right;
	scale3f m_scale;
	matrix3f m_windowToWorld, m_worldToWindow;

	void updateTransforms();



};

#endif	 	  	 	     	   		   	      	 	    	 	
