#ifndef MODEL_H
#define MODEL_H

#include "shape.h"
#include "dimensions.h"
#include <memory>
#include <vector>

class Model {

public:
	Model(const Dims2d<int>& size);
    void addShape(const Shape& shape);
    std::vector<Shape::shape_ptr>& getShapes() const;
    Dims2d<int> worldSize() const;

private:
    mutable std::vector<Shape::shape_ptr> shapes;
    Dims2d<int> m_worldSize;
};

#endif