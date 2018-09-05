#include "shape.h"

Shape::Shape(const points_t& points)
	: Shape(points, ShapeTraits())
{}

Shape::Shape(const points_t& points, const ShapeTraits& traits)
	: m_points(points), m_windowPoints(points.size()), m_id(-1), m_traits(traits)
{}

Shape::~Shape() {}

void Shape::reset(const points_t& points) {
	m_points.reset(points, m_traits.closed);
	m_windowPoints.reset(points, m_traits.closed);
}

