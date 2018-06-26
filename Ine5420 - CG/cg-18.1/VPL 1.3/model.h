#ifndef MODEL_H
#define MODEL_H

#include "shape.h"
#include "dimensions.h"
#include <memory>
#include <vector>

class Model {

public:
	Model(const WinDims<unit>& size);
    const Shape::shape_ptr_t addShape(const Shape& shape, shapeId_t id);
    std::vector<Shape::shape_ptr_t>& getShapes() const;
	const WinDims<unit>& worldSize() const;

private:
    mutable std::vector<Shape::shape_ptr_t> shapes;
	WinDims<unit> m_worldSize;
};

#endif