#ifndef WINDOW_H
#define WINDOW_H

#include "dimensions.h"

class Window {
public:
    Window(const Dims2d<int>& windowSize);

    void setLimits(const Dims2d<int>& worldLimits);

    Dims2d<int> size() const;

    void xShiftL(int dx);
    void xShiftR(int dx);
    void yShiftU(int dy);
    void yShiftD(int dy);
    void shift(int dx, int dy);

    void xShift(double fx);
    void yShift(double fy);
    void shift(double dx, double dy);

    void xScale(double sx);
    void yScale(double sy);
    void scale(double sx, double sy);

    void moveto(int xmin, int ymin);

    void resize(const Dims2d<int>& windowSize);

private:
    int m_Xmin, m_Xmax, m_Ymin, m_Ymax;
    int m_lowerX, m_upperX, m_lowerY, m_upperY; 
    double ratio;
    void updateRatio();
    void forceRatio(double r);

};

#endif