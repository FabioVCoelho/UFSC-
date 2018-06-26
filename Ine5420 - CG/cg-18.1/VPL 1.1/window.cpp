#include "window.h"
#include <cmath>

#define INC_AMOUNT(val,inc,lim) (((val + inc) > lim) ? lim - val : inc)
#define DEC_AMOUNT(val,dec,lim) (((val - dec) < lim) ? val - lim : dec)


Window::Window(const Dims2d<int>& windowSize) 
    : m_Xmin(windowSize.xMin), m_Xmax(windowSize.xMax), 
      m_Ymin(windowSize.yMin), m_Ymax(windowSize.yMax)
{
    setLimits(windowSize);
    updateRatio();
}

void Window::setLimits(const Dims2d<int>& worldLimits) {
    m_lowerX = worldLimits.xMin;
    m_upperX = worldLimits.xMax;
    m_lowerY = worldLimits.yMin;
    m_upperY = worldLimits.yMax;
}

Dims2d<int> Window::size() const {
    return Dims2d<int>(m_Xmin, m_Xmax, m_Ymin, m_Ymax);
}

void Window::xShiftL(int dx) {
	auto shift = DEC_AMOUNT(m_Xmin, dx, m_lowerX);
    m_Xmin -= shift;
    m_Xmax -= shift;
}
void Window::xShiftR(int dx) {
	auto shift = INC_AMOUNT(m_Xmax, dx, m_upperX);
    m_Xmin += shift;
    m_Xmax += shift;
}
void Window::yShiftU(int dy) {
	auto shift = INC_AMOUNT(m_Ymax, dy, m_upperY);
    m_Ymin += shift;
    m_Ymax += shift;
}
void Window::yShiftD(int dy) {
	auto shift = DEC_AMOUNT(m_Ymin, dy, m_lowerY);
    m_Ymin -= shift;
    m_Ymax -= shift;
}
void Window::shift(int dx, int dy) {
    dx > 0 ? xShiftR(dx) : xShiftL((-dx));
    dy > 0 ? yShiftD(dy) : yShiftU((-dy));
}

void Window::xShift(double fx) {
    auto size = m_Xmax - m_Xmin;
	auto inc = fx * size;
	inc > 0 ?
		inc = ceil(inc), xShiftR(inc)
		: (inc = floor(inc), xShiftL((-inc)));
}
void Window::yShift(double fy) {
    auto size = m_Ymax - m_Ymin;
    auto inc = fy * size;
	inc > 0 ?
		(inc = ceil(inc), yShiftU(inc))
		: (inc = floor(inc), yShiftD((-inc)));

}
void Window::shift(double fx, double fy) {
    xShift(fx);
    yShift(fy);
}

void Window::moveto(int xmin, int ymin) {
    xmin < m_Xmin ?
        xShiftL((m_Xmin - xmin))
        : xShiftR((xmin - m_Xmin));
    ymin < m_Ymin ?
        yShiftU((m_Ymin - ymin))
        : yShiftD((ymin - m_Ymin));
}

void Window::xScale(double sx) {
	auto d = (m_Xmax - m_Xmin);
    auto m = (m_Xmax + m_Xmin) / 2;
    m_Xmax = sx*(m_Xmax - m) + m;
    m_Xmin = m_Xmax - d*sx;
    if (m_Xmin < m_lowerX) {
        m_Xmin = m_lowerX;
    }
    if (m_Xmax > m_upperX) {
        m_Xmax = m_upperX;
    }
    updateRatio();
}
void Window::yScale(double sy) {
	auto d = (m_Ymax - m_Ymin);
	auto m = (m_Ymax + m_Ymin) / 2;
	m_Ymax = sy*(m_Ymax - m) + m;
	m_Ymin = m_Ymax - d*sy;
    if (m_Ymin < m_lowerY) {
        m_Ymin = m_lowerY;
    }
    if (m_Ymax > m_upperY) {
        m_Ymax = m_upperY;
    }
    updateRatio();
}
void Window::scale(double sx, double sy) {
    double currRatio = ratio;
    xScale(sx);
    yScale(sy);
    forceRatio(currRatio);
}

void Window::resize(const Dims2d<int>& windowSize) {
    m_Xmin = windowSize.xMin; 
    m_Xmax = windowSize.xMax;
    m_Ymin = windowSize.yMin;
    m_Ymax = windowSize.yMax;
    updateRatio();
}

void Window::updateRatio() {
    ratio = 1.0f * (m_Xmax - m_Xmin) / (m_Ymax - m_Ymin);
}

void Window::forceRatio(double r) {
    if (ratio > r) {
        m_Xmax = m_Xmin + (m_Ymax - m_Ymin) * r;
    }
    else {
        m_Ymax = m_Ymin + (m_Xmax - m_Xmin) / r;
    }
    updateRatio();
}

