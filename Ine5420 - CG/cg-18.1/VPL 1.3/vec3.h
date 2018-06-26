#ifndef VEC3_H
#define VEC3_H

#include "vec.h"

template <typename T>
class Vec<3, T> {
public:
	Vec() : m_x(T()), m_y(T()), m_z(T()) {}
	Vec(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}
	template <typename U>
	Vec<3, T>(const Vec<3, U>& p);

	T& operator[](const size_t dim) {
		assert(dim < 3);
		return dim < 1 ? m_x : (dim < 2 ? m_y : m_z);
	}
	const T& operator[](const size_t dim) const {
		assert(dim < 3);
		return dim < 1 ? m_x : (dim < 2 ? m_y : m_z);
	}

	T m_x, m_y, m_z;
};

template<typename T>
Vec<2, T> operator-(const Vec<3, T>& vec) {
	return (Vec<2, T>(-vec.m_x, -vec.m_y, -vec.m_y));
}

template<typename T>
Vec<3, T> operator+(const Vec<3, T>& lhs, const Vec<3, T>& rhs) {
	return (Vec<2, T>(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z));
}

template<typename T>
Vec<3, T> operator-(const Vec<3, T>& lhs, const Vec<3, T>& rhs) {
	return (Vec<2, T>(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z));
}

template<typename T>
void operator+=(Vec<3, T>& lhs, const Vec<3, T>& rhs) {
	lhs.m_x += rhs.m_x;
	lhs.m_y += rhs.m_y;
	lhs.m_z += rhs.m_z;
}

template<typename T>
void operator-=(Vec<3, T>& lhs, const Vec<3, T>& rhs) {
	lhs.m_x -= rhs.m_x;
	lhs.m_y -= rhs.m_y;
	lhs.m_z -= rhs.m_z;
}

template<typename T>
T dot(const Vec<3, T>& lhs, const Vec<3, T>& rhs) {
	return T(lhs.m_x*rhs.m_x + lhs.m_y*rhs.m_y + lhs.m_z*rhs.m_z);
}

template<typename T>
T dot(const Vec<3, T>& lhs, const Vec<2, T>& rhs) {
	return T(lhs.m_x*rhs.m_x + lhs.m_y*rhs.m_y + lhs.m_z);
}

template<typename T>
Vec<3, T> operator+(const Vec<3, T>& lhs, const T& rhs) {
	return (Vec<3, T>(lhs.m_x + rhs, lhs.m_y + rhs, lhs.m_z + rhs));
}
template<typename T>
Vec<3, T> operator-(const Vec<3, T>& lhs, const T& rhs) {
	return (Vec<3, T>(lhs.m_x - rhs, lhs.m_y - rhs, lhs.m_z - rhs));
}
template<typename T>
Vec<3, T> operator*(const Vec<3, T>& lhs, const T& rhs) {
	return (Vec<3, T>(lhs.m_x * rhs, lhs.m_y * rhs, lhs.m_z * rhs));
}
template<typename T>
Vec<3, T> operator/(const Vec<3, T>& lhs, const T& rhs) {
	return (Vec<3, T>(lhs.m_x / rhs, lhs.m_y / rhs, lhs.m_z / rhs));
}
template<typename T>
void operator+=(Vec<3, T>& lhs, const T& rhs) {
	lhs.m_x += rhs;
	lhs.m_y += rhs;
	lhs.m_z += rhs;
}
template<typename T>
void operator-=(Vec<3, T>& lhs, const T& rhs) {
	lhs.m_x -= rhs;
	lhs.m_y -= rhs;
	lhs.m_z -= rhs;
}
template<typename T>
void operator*=(Vec<3, T>& lhs, const T& rhs) {
	lhs.m_x *= rhs;
	lhs.m_y *= rhs;
	lhs.m_z *= rhs;
}
template<typename T>
void operator/=(Vec<3, T>& lhs, const T& rhs) {
	lhs.m_x /= rhs;
	lhs.m_y /= rhs;
	lhs.m_z /= rhs;
}

using Vec3i = Vec<3, int>;
using Vec3f = Vec<3, float>;

#endif
