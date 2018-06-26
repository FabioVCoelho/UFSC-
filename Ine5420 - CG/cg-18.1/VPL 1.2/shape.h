#ifndef SHAPE_H
#define SHAPE_H

#include "algebra.h"
#include <memory>
#include <vector>

class Shape {
public:
	using shape_ptr_t = std::shared_ptr<Shape>;

    virtual ~Shape() = 0;
	virtual shape_ptr_t clone() const = 0;
	virtual const points_t& points() const = 0;
	virtual points_t& points() = 0;
    virtual void xShift(unit dx) = 0;
    virtual void yShift(unit dy) = 0;
    virtual void shift(unit dx, unit dy) = 0;
    virtual void xShift(double fx, unit rx) = 0;
    virtual void yShift(double fy, unit ry) = 0;
    virtual void shift(double fx, double fy, unit rx, unit ry) = 0;
    virtual void xScale(double sx) = 0;
    virtual void yScale(double sy) = 0;
	virtual void rotate(double a) = 0;
    virtual void scale(double sx, double sy) = 0;
    virtual void morph(const points_t& points) = 0;
    
protected:
    Shape();
};

#endif