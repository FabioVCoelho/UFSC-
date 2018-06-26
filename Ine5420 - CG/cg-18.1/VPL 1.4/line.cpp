#include "line.h"
#include <cassert>
#include <cmath>


Line::Line(const point_t& p1_, const point_t& p2_)
	: Shape::Shape({ p1_, p2_ }) {}

Line::Line(const point_t& p1_, const point_t& p2_, const Color& color)
	: Shape::Shape({ p1_, p2_ }, color) {}


shape_ptr_t Line::clone() const {
	std::shared_ptr<Line> p(new Line(*this));
	p->reset(m_points.vertices());
	return p;
}

point_t Line::center() const {
	return point_t(
		(m_points.vertices()[0][0] + m_points.vertices()[1][0]) / 2,
		(m_points.vertices()[0][1] + m_points.vertices()[1][1]) / 2
	);
}

void Line::shift(const matrix3f& shift, const matrix3f& toWindow) {
	shift >> m_points.vertices();
	worldToWindow(toWindow);
}

void Line::scale(const matrix3f& scale, const matrix3f& toWindow) {
	scale >> m_points.vertices();
	worldToWindow(toWindow);
}

void Line::rotate(const matrix3f& rotation, const matrix3f& toWindow) {
	rotation >> m_points.vertices();
	worldToWindow(toWindow);
}

void Line::worldToWindow(const matrix3f& transf) {
	mult(m_windowPoints.vertices(), transf, m_points.vertices());
}
void Line::windowToWorld(const matrix3f& transf) {
	mult(m_points.vertices(), transf, m_windowPoints.vertices());
}

void Line::clip(const Clipper& clipper, edgevertex2f_t& clippedShape) {
	clipper.clipWireframe(m_windowPoints.edges(), clippedShape);
}