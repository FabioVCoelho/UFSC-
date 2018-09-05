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

	//void rotate(angle_t angle);
	void rotate(const transform3_t& rotation);

    void moveto(unit xmin, unit unit);

    void resize(const WinDims<unit>& windowSize);

	const Vec3f& center() const;

	angle_t angle() const;

	angle_t angleX() const;

	angle_t angleY() const;

	angle_t angleZ() const;

	double dop();

	//const matrix3f& scale() const { return m_scale; }	 	  	 	     	   		   	      	 	    	 	

	const transform3_t& windowToWorld() const { return m_windowToWorld; }

	const transform3_t& worldToWindow() const { return m_worldToWindow; }

	vertices3_t cornersWorldCoords();

private:
	unit m_width, m_height;
	
	unit m_lowerX, m_upperX, m_lowerY, m_upperY;
    double ratio;
    void updateRatio();
    void forceRatio(double r);
	Vec3f m_center;
	Vec3f m_up, m_right, m_vpn;
	//scale3f m_scale;
	transform3_t m_windowToWorld, m_worldToWindow;

	void updateTransforms();



};

#endif	 	  	 	     	   		   	      	 	    	 	
