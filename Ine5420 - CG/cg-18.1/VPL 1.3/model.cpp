#include "model.h"

using shape_ptr_t = Shape::shape_ptr_t;

Model::Model(const WinDims<unit>& size)
    : m_worldSize(size){}

const Shape::shape_ptr_t Model::addShape(const Shape& shape, shapeId_t id) {
    auto pshape = shape.clone();
	pshape->id() = id;
    shapes.push_back(pshape);
	//return shapes.back();
	return pshape;
}

std::vector<shape_ptr_t>& Model::getShapes() const {
    return shapes;
}

const WinDims<unit>& Model::worldSize() const {
    return m_worldSize;
}