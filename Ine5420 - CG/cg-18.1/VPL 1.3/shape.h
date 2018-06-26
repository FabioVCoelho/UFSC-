#ifndef SHAPE_H
#define SHAPE_H

#include "algebra.h"
#include <memory>
#include <vector>
#include <string>

class Shape {
public:
	Shape(const points_t& points): m_points(points), m_id(-1) {}
	using shape_ptr_t = std::shared_ptr<Shape>;
    virtual ~Shape() = 0;
	shapeId_t& id() const { return m_id; }
	std::string& name() { return m_name; }
	void name(std::string& name) { m_name = name; }
	virtual shape_ptr_t clone() const = 0;
	const points_t& points() const { return m_points; }
	points_t& points() { return m_points; }
	const points_t& windowPoints() const { return m_windowPoints; }
	points_t& windowPoints() { return m_windowPoints; }
	virtual point_t center() const = 0;
    virtual void shift(const matrix3f& shift, const matrix3f& toWorld) = 0;
	virtual void scale(const matrix3f& scale, const matrix3f& toWindow) = 0;
	virtual void rotate(const matrix3f& rotation, const matrix3f& toWindow) = 0;
    virtual void yShift(unit dy) = 0;
    virtual void shift(unit dx, unit dy) = 0;
    virtual void xShift(double fx, unit rx) = 0;
    virtual void yShift(double fy, unit ry) = 0;
    virtual void shift(double fx, double fy, unit rx, unit ry) = 0;
    virtual void xScale(double sx) = 0;
    virtual void yScale(double sy) = 0;
	virtual void rotate(angle_t a) = 0;
    virtual void scale(double sx, double sy) = 0;
    virtual void morph(const points_t& points) = 0;
	virtual void worldToWindow(const matrix3f& transf) = 0;
	virtual void windowToWorld(const matrix3f& transf) = 0;
	virtual void windowTransform(const matrix3f& transf) = 0;
	virtual void worldTransform(const matrix3f& transf) = 0;
    
protected:
	points_t m_points;
	window_points_t m_windowPoints;
	mutable shapeId_t m_id;
	std::string m_name;

    //Shape();
};

#endif