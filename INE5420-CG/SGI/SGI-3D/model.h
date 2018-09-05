#ifndef MODEL_H
#define MODEL_H

#include "object.h"
#include "dimensions.h"
#include <memory>
#include <vector>

class Model {

public:
	Model(const WinDims<unit>& size);
	//const Object2_ptr_t addObject(const Object<2>& Object, ObjectId_t id);
	const object_ptr_t<3> addObject(const object_t<3>& Object, ObjectId_t id);
    std::vector<object_ptr_t<3>>& getObjects() const;
	const WinDims<unit>& worldSize() const;

private:
    mutable std::vector<object_ptr_t<3>> m_objects;
	WinDims<unit> m_worldSize;
};

#endif