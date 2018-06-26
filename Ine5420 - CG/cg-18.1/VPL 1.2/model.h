#ifndef MODEL_H
#define MODEL_H

#include "shape.h"
#include "dimensions.h"
#include <memory>
#include <vector>

class Model {

public:
	Model(const Dims2d<int>& size);
    const Shape::shape_ptr_t addShape(const Shape& shape);
    std::vector<Shape::shape_ptr_t>& getShapes() const;
    Dims2d<int> worldSize() const;

private:
    mutable std::vector<Shape::shape_ptr_t> shapes;
    Dims2d<int> m_worldSize;
};

#endif