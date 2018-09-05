#include "model.h"

//using Object2_ptr_t = Object2_ptr_t;

Model::Model(const WinDims<unit>& size)
    : m_worldSize(size){}

const object_ptr_t<3> Model::addObject(const object_t<3>& Object, ObjectId_t id) {
    auto pObject = Object.clone();
	pObject->id() = id;
	m_objects.push_back(pObject);
	return pObject;
}

std::vector<object_ptr_t<3>>& Model::getObjects() const {
    return m_objects;
}

const WinDims<unit>& Model::worldSize() const {
    return m_worldSize;
}