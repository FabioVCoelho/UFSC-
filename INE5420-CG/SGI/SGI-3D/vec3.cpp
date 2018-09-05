#include "vec3.h"

template<>
template<>
Vec<3, int>::Vec(const Vec<3, float>& p)
	: m_x(lround(p.m_x)), m_y(lround(p.m_y)), m_z(lround(p.m_z)) {}

template<>
template<>
Vec<3, double>::Vec(const Vec<3, int>& p)
	: m_x(p.m_x), m_y(p.m_y), m_z(p.m_z) {}


