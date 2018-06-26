#include "model.h"

using shape_ptr_t = Shape::shape_ptr_t;

Model::Model(const Dims2d<int>& size)
    : m_worldSize(size){}

const Shape::shape_ptr_t Model::addShape(const Shape& shape) {
    auto pshape = shape.clone();
    shapes.push_back(pshape);
	//return shapes.back();
	return pshape;
}

std::vector<shape_ptr_t>& Model::getShapes() const {
    return shapes;
}

Dims2d<int> Model::worldSize() const {
    return m_worldSize;
}