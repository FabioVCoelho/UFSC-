#include "vec4.h"

template<>
template<>
Vec<4, int>::Vec(const Vec<4, float>& p)
	: m_data{ lround(p.m_data[0]), lround(p.m_data[1]), lround(p.m_data[2]), lround(p.m_data[3]) } {}

template<>
template<>
Vec<4, double>::Vec(const Vec<4, int>& p)
	: m_data{ (double)p.m_data[0], (double)p.m_data[1], (double)p.m_data[2], (double)p.m_data[3] } {}


