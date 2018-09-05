#ifndef VEC4_H
#define VEC4_H

#include "vec.h"
#include "vec2.h"

template <typename T>
class Vec<4, T> {
public:
	Vec() : m_data{ T(), T(), T(), T() } {}
	Vec(T x, T y, T z, T w) : m_data{ x, y, z, w } {}
	template <typename U>
	Vec<4, T>(const Vec<4, U>& p);

	T& operator[](const size_t dim) {
		assert(dim < 4);
		return m_data[dim];
	}
	const T& operator[](const size_t dim) const {
		assert(dim < 4);
		return m_data[dim];
	}

	T m_data[4];
};

template<typename T>
Vec<4, T> operator-(const Vec<4, T>& vec) {
	return (Vec<4, T>(-vec.m_data[0], -vec.m_data[1], -vec.m_data[2], -vec.m_data[3]));
}

template<typename T>
Vec<4, T> operator+(const Vec<4, T>& lhs, const Vec<4, T>& rhs) {
	return (Vec<4, T>(lhs.m_data[0] + rhs.m_data[0], lhs.m_data[1] + rhs.m_data[1], lhs.m_data[2] + rhs.m_data[2], lhs.m_data[3] + rhs.m_data[3]));
}

template<typename T>
Vec<4, T> operator-(const Vec<4, T>& lhs, const Vec<4, T>& rhs) {	 	  	 	     	   		   	      	 	    	 	
	return (Vec<4, T>(lhs.m_data[0] - rhs.m_data[0], lhs.m_data[1] - rhs.m_data[1], lhs.m_data[2] - rhs.m_data[2], lhs.m_data[3] - rhs.m_data[3]));
}

//template<typename T>
//std::vector<Vec<2, T>> operator*(const std::vector<Vec<4, T>>& lhs, const std::vector<Vec<2, T>>&& rhs) {
//	std::vector<Vec<4, T>> ret;
//	ret.reserve(lhs.size());
//	for (size_t i = 0; i < lhs.size(); ++i) {
//		ret.emplace_back(dot(lhs[i]));
//	}
//	return (Vec<4, T>(lhs.m_data[0] - rhs.m_data[0], lhs.m_data[1] - rhs.m_data[1], lhs.m_data[2] - rhs.m_data[2], lhs.m_data[3] - rhs.m_data[3]));
//}



template<typename T>
void operator+=(Vec<4, T>& lhs, const Vec<4, T>& rhs) {
	lhs.m_data[0] += rhs.m_data[0];
	lhs.m_data[1] += rhs.m_data[1];
	lhs.m_data[2] += rhs.m_data[2];
	lhs.m_data[3] += rhs.m_data[3];
}

template<typename T>
void operator-=(Vec<4, T>& lhs, const Vec<4, T>& rhs) {
	lhs.m_data[0] -= rhs.m_data[0];
	lhs.m_data[1] -= rhs.m_data[1];
	lhs.m_data[2] -= rhs.m_data[2];
	lhs.m_data[3] -= rhs.m_data[3];
}

template<typename T>
T dot(const Vec<4, T>& lhs, const Vec<4, T>& rhs) {
	return T(lhs.m_data[0]*rhs.m_data[0] + lhs.m_data[1]*rhs.m_data[1] + lhs.m_data[2]*rhs.m_data[2] + lhs.m_data[3]*rhs.m_data[3]);
}

template<typename T>
T dot(const Vec<4, T>& lhs, const Vec<3, T>& rhs) {	 	  	 	     	   		   	      	 	    	 	
	return T(lhs.m_data[0]*rhs.m_data[0] + lhs.m_data[1]*rhs.m_data[1] + lhs.m_data[2]*rhs.m_data[2] + lhs.m_data[3]);
}

template<typename T, typename U>
U dot(const Vec<4, T>& lhs, const Vec<3, U>& rhs) {
	return U(lhs.m_data[0]*rhs.m_data[0] + lhs.m_data[1]*rhs.m_data[1] + lhs.m_data[2] * rhs.m_data[2] + lhs.m_data[3]);
}

//template<typename T, typename U>
//U dot(const Vec<4, T>& lhs, const Vec<4, U>& rhs) {
//	return U(lhs.m_data[0]*rhs.m_data[0] + lhs.m_data[1]*rhs.m_data[1] + lhs.m_data[2]*rhs.m_data[2]);
//}
//
//template<typename T, typename U>
//U dot(const Vec<4, T>& lhs, const Vec<3, U>& rhs) {
//	return U(lhs.m_data[0]*rhs.m_data[0] + lhs.m_data[1]*rhs.m_data[1] + lhs.m_data[2]);
//}

template<typename T>
Vec<4, T> operator+(const Vec<4, T>& lhs, const T& rhs) {
	return (Vec<4, T>(lhs.m_data[0] + rhs, lhs.m_data[1] + rhs, lhs.m_data[2] + rhs, lhs.m_data[3] + rhs));
}
template<typename T>
Vec<4, T> operator-(const Vec<4, T>& lhs, const T& rhs) {
	return (Vec<4, T>(lhs.m_data[0] - rhs, lhs.m_data[1] - rhs, lhs.m_data[2] - rhs, lhs.m_data[3] - rhs));
}
template<typename T>
Vec<4, T> operator*(const Vec<4, T>& lhs, const T& rhs) {
	return (Vec<4, T>(lhs.m_data[0] * rhs, lhs.m_data[1] * rhs, lhs.m_data[2] * rhs, lhs.m_data[3] * rhs));
}
template<typename T>
Vec<4, T> operator/(const Vec<4, T>& lhs, const T& rhs) {
	return (Vec<4, T>(lhs.m_data[0] / rhs, lhs.m_data[1] / rhs, lhs.m_data[2] / rhs, lhs.m_data[3] / rhs));
}
template<typename T>
void operator+=(Vec<4, T>& lhs, const T& rhs) {	 	  	 	     	   		   	      	 	    	 	
	lhs.m_data[0] += rhs;
	lhs.m_data[1] += rhs;
	lhs.m_data[2] += rhs;
	lhs.m_data[3] += rhs;
}
template<typename T>
void operator-=(Vec<4, T>& lhs, const T& rhs) {
	lhs.m_data[0] -= rhs;
	lhs.m_data[1] -= rhs;
	lhs.m_data[2] -= rhs;
	lhs.m_data[3] -= rhs;
}
template<typename T>
void operator*=(Vec<4, T>& lhs, const T& rhs) {
	lhs.m_data[0] *= rhs;
	lhs.m_data[1] *= rhs;
	lhs.m_data[2] *= rhs;
	lhs.m_data[3] *= rhs;
}
template<typename T>
void operator/=(Vec<4, T>& lhs, const T& rhs) {
	lhs.m_data[0] /= rhs;
	lhs.m_data[1] /= rhs;
	lhs.m_data[2] /= rhs;
	lhs.m_data[3] /= rhs;
}

using Vec4i = Vec<4, int>;
using Vec4f = Vec<4, double>;

#endif
	 	  	 	     	   		   	      	 	    	 	
