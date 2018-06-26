#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"
#include "shape_traits.h"
#include "clipping.h"
#include "color.h"
#include <vector>
#include <string>
#include <memory>

class Shape;

using shape_ptr_t = std::shared_ptr<Shape>;

class Shape {
public:
	Shape(const points_t& points);

	Shape(const points_t& points, const ShapeTraits& traits);

    virtual ~Shape() = 0;

	const ShapeTraits& traits() const { return m_traits; }

	shapeId_t& id() const { return m_id; }

	std::string& name() { return m_name; }
	void name(std::string& name) { m_name = name; }

	//virtual bool isPolygon() const = 0;

	points_t& points() { return m_points.vertices(); }
	const points_t& points() const { return m_points.vertices(); }
	
	window_points_t& windowPoints() { return m_windowPoints.vertices(); }
	const window_points_t& windowPoints() const { return m_windowPoints.vertices(); }

	edges_t& edges() { return m_points.edges(); }
	const edges_t& edges() const { return m_points.edges(); }

	window_edges_t& windowEdges() { return m_windowPoints.edges(); }
	const window_edges_t& windowEdges() const { return m_windowPoints.edges(); }
	
	virtual shape_ptr_t clone() const = 0;
	
	void reset(const points_t& points);

	virtual point_t center() const = 0;

    virtual void shift(const matrix3f& shift, const matrix3f& toWindow) = 0;
	virtual void scale(const matrix3f& scale, const matrix3f& toWindow) = 0;
	virtual void rotate(const matrix3f& rotation, const matrix3f& toWindow) = 0;

	virtual void worldToWindow(const matrix3f& transf) = 0;
	virtual void windowToWorld(const matrix3f& transf) = 0;

	virtual void clip(const Clipper& clipper, edgevertex2f_t& clippedShape) = 0;

	void setColor(const Color& color) { m_traits.color = color; }

	Color color() const { return m_traits.color; }
    
protected:
	edgevertex2f_t m_points;
	edgevertex2f_t m_windowPoints;
	ShapeTraits m_traits;
	mutable shapeId_t m_id;
	std::string m_name;
};



#endif