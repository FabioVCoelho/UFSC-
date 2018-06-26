#ifndef DIMENSIONS_H
#define DIMENSIONS_H

template <typename T>
struct Dims2d {
    Dims2d() : Dims2d(0,0,0,0) {}
    Dims2d(T xmin, T xmax, T ymin, T ymax)
        : xMin(xmin), xMax(xmax), yMin(ymin), yMax(ymax) {}

    void resize(T xmin, T xmax, T ymin, T ymax) {
        xMin = xmin;
        xMax = xmax;
        yMin = ymin;
        yMax = ymax;
    }
    void copy(const Dims2d<T>& src) {
        xMin = src.xMin;
        xMax = src.xMax;
        yMin = src.yMin;
        yMax = src.yMax;
    }

    T xMin, xMax, yMin, yMax;
};

#endif