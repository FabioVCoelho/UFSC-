#ifndef VEC_H
#define VEC_H


#include <vector>
#include <cmath>
#include <cassert>

template <size_t dim, typename T>
class Vec {
public:
	Vec() {
		assert(dim > 0);
		for (size_t i = 0; i < dim; i++) { m_data[i] = T(); }
	}

	T& operator[](const size_t i) {
		assert(i<dim);
		return m_data[i];
	}
	const T& operator[](const size_t i) const {
		assert(i<dim);
		return m_data[i];
	}

	T m_data[dim];
};

///////////////////////////////////////////////////////////////////////////////
// (vector, vector) operations

template<size_t dim, typename T>
Vec<dim, T> operator+(const Vec<dim, T>& lhs, const Vec<dim, T>& rhs) {
	vec<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] + rhs[i];
	}
	return ret;
}

template<size_t dim, typename T>
Vec<dim, T> operator-(const Vec<dim, T>& lhs, const Vec<dim, T>& rhs) {
	vec<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] - rhs[i];
	}
	return ret;
}

template<size_t dim, typename T>
void operator+=(Vec<dim, T>& lhs, const Vec<dim, T>& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] += rhs[i];
	}
}

template<size_t dim, typename T>
void operator-=(Vec<dim, T>& lhs, const Vec<dim, T>& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] -= rhs[i];
	}
}


///////////////////////////////////////////////////////////////////////////////
// (vector, scalar) operations

template<size_t dim, typename T>
Vec<dim, T> operator+(const Vec<dim, T>& lhs, const T& rhs) {
	vec<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] + rhs;
	}
	return ret;
}

template<size_t dim, typename T>
Vec<dim, T> operator-(const Vec<dim, T>& lhs, const T& rhs) {
	vec<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] - rhs;
	}
	return ret;
}

template<size_t dim, typename T>
Vec<dim, T> operator*(const Vec<dim, T>& lhs, const T& rhs) {
	vec<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] * rhs;
	}
	return ret;
}

template<size_t dim, typename T>
Vec<dim, T> operator/(const Vec<dim, T>& lhs, const T& rhs) {
	vec<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] / rhs;
	}
	return ret;
}

template<size_t dim, typename T>
void operator+=(Vec<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] += rhs;
	}
}

template<size_t dim, typename T>
void operator-=(Vec<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] -= rhs;
	}
}

template<size_t dim, typename T>
void operator*=(Vec<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] *= rhs;
	}
}

template<size_t dim, typename T>
void operator/=(Vec<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] /= rhs;
	}
}



#endif