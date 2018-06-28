#include "window.h"
#include <cmath>

#define INC_AMOUNT(val,inc,lim) (((val + inc) > lim) ? lim - val : inc)
#define DEC_AMOUNT(val,dec,lim) (((val - dec) < lim) ? val - lim : dec)

const double DOP = 500;

Window::Window(const WinDims<unit>& windims)
	: m_width(windims.width),
	m_height(windims.height),
	m_up(0.0, 1.0, 0.0),
	m_right(1.0, 0.0, 0.0),
	m_vpn(0.0, 0.0, 1.0)
{
	//m_scale = { 2 / m_width, 2 / m_height },
	m_center = {
		(windims.width + 2 * windims.xmin) / 2,
		(windims.height + 2 * windims.ymin) / 2,
		-500.0
	};
	updateTransforms();
    setLimits(windims);
    updateRatio();
}

double Window::dop() { return DOP; }

void Window::setLimits(const WinDims<unit>& limits) {
    m_lowerX = limits.xmin;
    m_upperX = limits.xmin + limits.width;
    m_lowerY = limits.ymin;
    m_upperY = limits.ymin + limits.height;
}

WinDims<unit> Window::dims() const {
	//return WinDims<unit>(m_center[0] - m_width/2, m_center[1] - m_height/2, m_width, m_height);
	return WinDims<unit>(-1, -1, 2, 2);
}	 	  	 	     	   		   	      	 	    	 	

//Dims2d<unit> Window::dims() const {
//	unit xmin = m_center[0] - m_width / 2;
//	unit ymin = m_center[1] - m_height / 2;
//	unit xmax = xmin + m_width;
//	unit ymax = ymin + m_height;
//	return Dims2d<unit>(xmin, xmax, ymin, ymax);
//}


void Window::xShiftL(unit d) {
	m_center -= (m_right * d);
	updateTransforms();
}
void Window::xShiftR(unit d) {
	m_center += (m_right * d);
	updateTransforms();
}
void Window::yShiftU(unit d) {
	m_center += (m_up * d);
	updateTransforms();
}
void Window::yShiftD(unit d) {
	m_center -= (m_up * d);
	updateTransforms();
}
void Window::shift(unit dx, unit dy) {
	m_center += (m_right * dx);
	m_center += (m_up * dy);
	updateTransforms();
}

void Window::xShiftF(double fx) {
	m_center += (m_right * (fx*m_width));
	updateTransforms();
}	 	  	 	     	   		   	      	 	    	 	
void Window::yShiftF(double fy) {
	m_center += (m_up * (fy*m_height));
	updateTransforms();

}
void Window::shiftF(double fx, double fy) {
	xShiftF(fx);
	yShiftF(fy);
	updateTransforms();
}



void Window::scale(double sx, double sy) {
	//double currRatio = ratio;
	m_width *= sx;
	m_height *= sy;
	updateTransforms();
	//forceRatio(currRatio);
}

//void Window::rotate(angle_t angle) {
//	matrix3f rot = rotate4f(angle);
//	rot >> m_up;
//	rot >> m_right;
//	updateTransforms();
//}

void Window::rotate(const transform3_t& rotation) {
	rotation >> m_up;
	rotation >> m_right;
	rotation >> m_vpn;
	updateTransforms();
}




void Window::moveto(unit xmin, unit ymin) {	 	  	 	     	   		   	      	 	    	 	
	//xmin < m_Xmin ?
	//	xShiftL((m_Xmin - xmin))
	//	: xShiftR((xmin - m_Xmin));
	//ymin < m_Ymin ?
	//	yShiftU((m_Ymin - ymin))
	//	: yShiftD((ymin - m_Ymin));
}

void Window::resize(const WinDims<unit>& dims) {
	m_width = dims.width;
	m_height = dims.height;
	//m_scale = scale3f(2 / m_width, 2 / m_height);
	m_center = {
		(dims.width + 2 * dims.xmin) / 2,
		(dims.height + 2 * dims.ymin) / 2,
		0.0
	};
	m_up = { 0.0, 1.0, 0.0};
	m_right = { 1.0, 0.0, 0.0};
	m_vpn = { 0.0, 0.0, 1.0 };
	updateTransforms();
	//updateRatio();
}

void Window::updateRatio() {
	//ratio = 1.0f * (m_Xmax - m_Xmin) / (m_Ymax - m_Ymin);
}

void Window::forceRatio(double r) {
	/*if (ratio > r) {
		m_Xmax = m_Xmin + (m_Ymax - m_Ymin) * r;
	}
	else {
		m_Ymax = m_Ymin + (m_Xmax - m_Xmin) / r;
	}
	updateRatio();*/
}	 	  	 	     	   		   	      	 	    	 	

const Vec3f& Window::center() const {
	return m_center;
}

angle_t Window::angle() const {
	return atan2(m_up[0], m_up[1]);
}

angle_t Window::angleX() const {
	return atan2(m_vpn[1], m_vpn[2]);
}

angle_t Window::angleY() const {
	return atan2(m_vpn[0], m_vpn[2]);
}

angle_t Window::angleZ() const {
	return atan2(m_up[0], m_up[1]);
	//return atan2(m_vpn[0], m_vpn[1]);
}

vertices3_t Window::cornersWorldCoords() {
	Vec3f p0 = m_center + m_right*(m_width / 2) + m_up*(m_height / 2);
	Vec3f p1 = p0 - m_up*m_height;
	Vec3f p2 = p1 - m_right*m_width;
	Vec3f p3 = p0 - m_right*m_width;
	return { p0, p1, p2, p3 };
}


//void Window::updateTransforms() {
//	m_worldToWindow = scale3f(2 / m_width, 2 / m_height) * shiftrotate3f(-m_center, angle());
//	m_windowToWorld = rotateshift3f(-angle(), m_center) * scale3f(m_width / 2, m_height / 2);
//}

//void Window::updateTransforms() {	 	  	 	     	   		   	      	 	    	 	
//	m_worldToWindow = scale4f(2 / m_width, 2 / m_height, 1.0) * yrotate4f(angleY()) * xrotate4f(angleX()) * shift4f(-m_center);
//	//m_worldToWindow = scale3f(2 / m_width, 2 / m_height) * shiftrotate3f(-m_center, angle());
//	//m_windowToWorld = rotateshift3f(-angle(), m_center) * scale3f(m_width / 2, m_height / 2);
//	m_windowToWorld = shift4f(m_center) * xrotate4f(-angleX()) * yrotate4f(-angleY()) * scale4f(m_width / 2, m_height / 2, 1.0);
//}

void Window::updateTransforms() {
	m_worldToWindow = scale4f(2 / m_width, 2 / m_height, 1.0) * zrotate4f(angleZ()) * yrotate4f(angleY()) * xrotate4f(angleX()) * shift4f(-m_center);
	//m_worldToWindow = scale3f(2 / m_width, 2 / m_height) * shiftrotate3f(-m_center, angle());
	//m_windowToWorld = rotateshift3f(-angle(), m_center) * scale3f(m_width / 2, m_height / 2);
	m_windowToWorld = shift4f(m_center) * xrotate4f(-angleX()) * yrotate4f(-angleY()) * zrotate4f(-angleZ()) * scale4f(m_width / 2, m_height / 2, 1.0);
}




//void Window::xShiftL(unit dx) {
//    auto shift = DEC_AMOUNT(m_Xmin, dx, m_lowerX);
//    m_Xmin -= shift;
//    m_Xmax -= shift;
//}
//void Window::xShiftR(unit dx) {
//	auto shift = INC_AMOUNT(m_Xmax, dx, m_upperX);
//    m_Xmin += shift;
//    m_Xmax += shift;
//}
//void Window::yShiftU(unit dy) {
//	auto shift = INC_AMOUNT(m_Ymax, dy, m_upperY);
//    m_Ymin += shift;
//    m_Ymax += shift;
//}
//void Window::yShiftD(unit dy) {
//	auto shift = DEC_AMOUNT(m_Ymin, dy, m_lowerY);
//    m_Ymin -= shift;
//    m_Ymax -= shift;
//}	 	  	 	     	   		   	      	 	    	 	
//void Window::shift(unit dx, unit dy) {
//    dx > 0 ? xShiftR(dx) : xShiftL((-dx));
//    dy > 0 ? yShiftD(dy) : yShiftU((-dy));
//}
//
//void Window::xShift(double fx) {
//    auto size = m_Xmax - m_Xmin;
//	auto inc = fx * size;
//	inc > 0 ?
//		inc = ceil(inc), xShiftR(inc)
//		: (inc = floor(inc), xShiftL((-inc)));
//}
//void Window::yShift(double fy) {
//    auto size = m_Ymax - m_Ymin;
//    auto inc = fy * size;
//	inc > 0 ?
//		(inc = ceil(inc), yShiftU(inc))
//		: (inc = floor(inc), yShiftD((-inc)));
//
//}
//void Window::shift(double fx, double fy) {
//    xShift(fx);
//    yShift(fy);
//}
//
//void Window::moveto(unit xmin, unit ymin) {
//    xmin < m_Xmin ?
//        xShiftL((m_Xmin - xmin))
//        : xShiftR((xmin - m_Xmin));
//    ymin < m_Ymin ?
//        yShiftU((m_Ymin - ymin))
//        : yShiftD((ymin - m_Ymin));
//}
//
//void Window::xScale(double sx) {
//	auto d = (m_Xmax - m_Xmin);
//    auto m = (m_Xmax + m_Xmin) / 2;
//    m_Xmax = sx*(m_Xmax - m) + m;
//    m_Xmin = m_Xmax - d*sx;
//    if (m_Xmin < m_lowerX) {	 	  	 	     	   		   	      	 	    	 	
//        m_Xmin = m_lowerX;
//    }
//    if (m_Xmax > m_upperX) {
//        m_Xmax = m_upperX;
//    }
//    updateRatio();
//}
//void Window::yScale(double sy) {
//	auto d = (m_Ymax - m_Ymin);
//	auto m = (m_Ymax + m_Ymin) / 2;
//	m_Ymax = sy*(m_Ymax - m) + m;
//	m_Ymin = m_Ymax - d*sy;
//    if (m_Ymin < m_lowerY) {
//        m_Ymin = m_lowerY;
//    }
//    if (m_Ymax > m_upperY) {
//        m_Ymax = m_upperY;
//    }
//    updateRatio();
//}
//void Window::scale(double sx, double sy) {
//    double currRatio = ratio;
//    xScale(sx);
//    yScale(sy);
//    forceRatio(currRatio);
//}
//
//void Window::resize(const Dims2d<unit>& windowSize) {
//    m_Xmin = windowSize.xMin; 
//    m_Xmax = windowSize.xMax;
//    m_Ymin = windowSize.yMin;
//    m_Ymax = windowSize.yMax;
//    updateRatio();
//}
//
//void Window::updateRatio() {	 	  	 	     	   		   	      	 	    	 	
//    ratio = 1.0f * (m_Xmax - m_Xmin) / (m_Ymax - m_Ymin);
//}
//
//void Window::forceRatio(double r) {
//    if (ratio > r) {
//        m_Xmax = m_Xmin + (m_Ymax - m_Ymin) * r;
//    }
//    else {
//        m_Ymax = m_Ymin + (m_Xmax - m_Xmin) / r;
//    }
//    updateRatio();
//}

