#include "wireframe.h"
#include "transforms.h"
#include <cassert>
#include <cmath>


Wireframe::Wireframe(const points_t& points)
    : Shape::Shape(points)
{
	calcCenter();
}

Wireframe::Wireframe(const points_t& points, const Color& color)
	: Shape::Shape(points, ShapeTraits(color, false, true))
{
	calcCenter();
}

Wireframe::Wireframe(const points_t& points, const ShapeTraits& traits)
	: Shape::Shape(points, traits)
{
	calcCenter();
}



void Wireframe::calcCenter() {
	unit xavg = 0;
	unit yavg = 0;

	for (auto& p : m_points.vertices()) {
		xavg += p[0];
		yavg += p[1];
	}
	xavg /= m_points.vertices().size();
	yavg /= m_points.vertices().size();
	m_center = { xavg, yavg };
}


shape_ptr_t Wireframe::clone() const {
	std::shared_ptr<Wireframe> p(new Wireframe(*this));
	p->reset(m_points.vertices());
	return p;
}

void Wireframe::shift(const matrix3f& shift, const matrix3f& toWindow) {
	shift >> m_points.vertices();
	shift >> m_center;
	worldToWindow(toWindow);
}

void Wireframe::scale(const matrix3f& scale, const matrix3f& toWindow) {
	scale >> m_points.vertices();
	worldToWindow(toWindow);
}

void Wireframe::rotate(const matrix3f& rotation, const matrix3f& toWindow) {
	rotation >> m_points.vertices();
	rotation >> m_center;
	worldToWindow(toWindow);
}

void Wireframe::worldToWindow(const matrix3f& transf) {
	mult(m_windowPoints.vertices(), transf, m_points.vertices());
	mult(m_windowCenter, transf, m_center);
}
void Wireframe::windowToWorld(const matrix3f& transf) {
	mult(m_points.vertices(), transf, m_windowPoints.vertices());
	mult(m_center, transf, m_windowCenter);
}

void Wireframe::clip(const Clipper& clipper, edgevertex2f_t& clippedShape) {
	clipper.clipWireframe(m_windowPoints.edges(), clippedShape);
}

