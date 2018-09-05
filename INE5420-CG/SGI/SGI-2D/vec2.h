#ifndef VEC2_H
#define VEC2_H

#include "vec.h"

template <typename T>
class Vec<2, T> {
public:
	Vec() : m_x(T()), m_y(T()) {}
	Vec(T x, T y) : m_x(x), m_y(y) {}
	template <typename U>
	Vec<2, T>(const Vec<2, U>& p);

	T& operator[](const size_t dim) {
		assert(dim < 2);
		return dim <= 0 ? m_x : m_y;
	}
	const T& operator[](const size_t dim) const {
		assert(dim < 2);
		return dim <= 0 ? m_x : m_y;
	}

	T m_x, m_y;
};

template<typename T>
Vec<2, T> operator-(const Vec<2, T>& vec) {
	return (Vec<2, T>(-vec.m_x, -vec.m_y));
}

template<typename T>
Vec<2, T> operator+(const Vec<2, T>& lhs, const Vec<2, T>& rhs) {
	return (Vec<2, T>(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y));
}

template<typename T>
Vec<2, T> operator-(const Vec<2, T>& lhs, const Vec<2, T>& rhs) {	 	  	 	     	   		   	      	 	    	 	
	return (Vec<2, T>(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y));
}

template<typename T>
void operator+=(Vec<2, T>& lhs, const Vec<2, T>& rhs) {
	lhs.m_x += rhs.m_x;
	lhs.m_y += rhs.m_y;
}

template<typename T>
void operator-=(Vec<2, T>& lhs, const Vec<2, T>& rhs) {
	lhs.m_x -= rhs.m_x;
	lhs.m_y -= rhs.m_y;
}

template<typename T, typename U>
U dot(const Vec<2, T>& lhs, const Vec<2, U>& rhs) {
	return U(lhs.m_x*rhs.m_x + lhs.m_y*rhs.m_y);
}

template<typename T>
Vec<2, T> operator+(const Vec<2, T>& lhs, const T& rhs) {
	return (Vec<2, T>(lhs.m_x + rhs, lhs.m_y + rhs));
}
template<typename T>
Vec<2, T> operator-(const Vec<2, T>& lhs, const T& rhs) {
	return (Vec<2, T>(lhs.m_x - rhs, lhs.m_y - rhs));
}
template<typename T>
Vec<2, T> operator*(const Vec<2, T>& lhs, const T& rhs) {
	return (Vec<2, T>(lhs.m_x * rhs, lhs.m_y * rhs));
}
template<typename T>
Vec<2, T> operator/(const Vec<2, T>& lhs, const T& rhs) {
	return (Vec<2, T>(lhs.m_x / rhs, lhs.m_y / rhs));
}	 	  	 	     	   		   	      	 	    	 	
template<typename T>
void operator+=(Vec<2, T>& lhs, const T& rhs) {
	lhs.m_x += rhs;
	lhs.m_y += rhs;
}
template<typename T>
void operator-=(Vec<2, T>& lhs, const T& rhs) {
	lhs.m_x -= rhs;
	lhs.m_y -= rhs;
}
template<typename T>
void operator*=(Vec<2, T>& lhs, const T& rhs) {
	lhs.m_x *= rhs;
	lhs.m_y *= rhs;
}
template<typename T>
void operator/=(Vec<2, T>& lhs, const T& rhs) {
	lhs.m_x /= rhs;
	lhs.m_y /= rhs;
}



using Vec2i = Vec<2, int>;
using Vec2f = Vec<2, double>;

#endif	 	  	 	     	   		   	      	 	    	 	
