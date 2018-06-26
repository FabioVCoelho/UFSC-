#include "model.h"

using shape_ptr = Shape::shape_ptr;

Model::Model(const Dims2d<int>& size)
    : m_worldSize(size){}

void Model::addShape(const Shape& shape) {
    shapes.push_back(shape.clone());
}

std::vector<shape_ptr>& Model::getShapes() const {
    return shapes;
}

Dims2d<int> Model::worldSize() const {
    return m_worldSize;
}