#include "vec2.h"

template<>
template<>
Vec<2, int>::Vec(const Vec<2, double>& p)
	: m_x(lround(p.m_x)), m_y(lround(p.m_y)) {}

template<>
template<>
Vec<2, double>::Vec(const Vec<2, int>& p)
	: m_x(p.m_x), m_y(p.m_y) {}
