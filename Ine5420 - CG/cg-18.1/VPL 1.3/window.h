#ifndef WINDOW_H
#define WINDOW_H

#include "dimensions.h"
#include "types.h"
#include "algebra.h"
#include "transforms.h"

//template <typename T>
//class ViewUp {
//public:
//	ViewUp(T x1, T x2, T y1, T y2)
//		: x({x1, x2}), y({ y1, y2 }), ax(0.0), ay(1.0), angle(0.0), size(y2 - y1){}
//
//	void shiftPar(T d) {
//		x -= (d * ax);
//		y += (d * ay);
//	}
//
//	void shiftPerp(T d) {
//		x += (d * ay);
//		y += (d * ax);
//	}
//
//	void scale(double sx, double sy) {
//		x[1] *= sx;
//		y[1] *= sy;
//	}
//
//	void rotate(angle_t a) {
//		angle += a;
//		ax = sin(angle);
//		ay = cos(angle);
//
//	}
//
//	inline const Vec<2, T>& vux() { return x; }
//	inline const Vec<2, T>& vuy() { return y; }
//
//private:
//	Vec<2, T> x, y;
//	T size;
//	angle_t angle;
//	double ax, ay;
//};

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

    //void xScale(double sx);
    //void yScale(double sy);
    void scale(double sx, double sy);

	void rotate(angle_t angle);
	void rotate(const matrix3f& rotation);

    void moveto(unit xmin, unit unit);

    void resize(const WinDims<unit>& windowSize);

	const Vec2f& center() const;

	angle_t angle() const;

	//const matrix3f& scale() const { return m_scale; }

	const matrix3f& scale() const { return m_scale; }

	const matrix3f& windowToWorld() const { return m_windowToWorld; } 

	const matrix3f& worldToWindow() const { return m_worldToWindow; }

	points_t cornersWorldCoords();

private:
    //int m_Xmin, m_Xmax, m_Ymin, m_Ymax;
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

	
	//ViewUp<unit> m_vu;

};

#endif