#include "shape.h"

Shape::Shape(const points_t& points)
	: Shape(points, Color())
{}

Shape::Shape(const points_t& points, const Color& color)
	: m_points(points), m_windowPoints(points.size()), m_id(-1), m_color(color)
{}

Shape::~Shape() {}

void Shape::reset(const points_t& points) {
	m_points.reset(points);
	m_windowPoints.reset(points);
}

