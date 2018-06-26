#ifndef MATRIX_H
#define MATRIX_H

#include "vec.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

template <size_t dim, typename T >
class Matrix {
public:
	Matrix() {
		assert(dim > 0);
		//for (size_t i = 0; i < dim; i++) { m_data[i] = T() }
	}

	Matrix(const std::vector<Vec<dim, T>>& rows) {
		assert(dim == rows.size() && dim > 0);
		for (size_t i = 0; i < dim; i++) { m_data[i] = rows[i]; }
	}

	Vec<dim, T>& operator[](const size_t i) {
		assert(i<dim);
		return m_data[i];
	}
	const Vec<dim, T>& operator[](const size_t i) const {
		assert(i<dim);
		return m_data[i];
	}

	void transpose() {
		T temp;
		for (size_t i = 0; i < dim; i++) {
			for (size_t j = i + 1; j < dim; j++) {
				temp = m_data[i][j];
				m_data[i][j] = m_data[j][i];
				m_data[j][i] = temp;
			}
		}
		return;
	}

	Vec<dim, T> m_data[dim];
};

///////////////////////////////////////////////////////////////////////////////
// matrix operations

template<size_t dim, typename T>
Matrix<dim, T> transpose(const Matrix<dim, T>& m) {
	Matrix<dim, T> ret = m;
	transpose(ret);
	return ret;
}


///////////////////////////////////////////////////////////////////////////////
// (matrix, matrix) operations

template<size_t dim, typename T>
Matrix<dim, T> operator+(const Matrix<dim, T>& lhs, const Matrix<dim, T>& rhs) {
	Matrix<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] + rhs[i];
	}
	return ret;
}

template<size_t dim, typename T>
Matrix<dim, T> operator-(const Matrix<dim, T>& lhs, const Matrix<dim, T>& rhs) {
	Matrix<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] - rhs[i];
	}
	return ret;
}

template<size_t dim, typename T>
Matrix<dim, T> operator*(const Matrix<dim, T>& lhs, const Matrix<dim, T>& rhs) {
	Matrix<dim, T> ret = transpose(rhs);
	for (size_t j = 0; j < dim; ++j) {
		Vec<dim, T> row = ret[j];
		for (size_t i = 0; i < dim; ++i) {
			ret[i][j] = dot(lhs[i], row);
		}
	}
	return ret;
}

template<size_t dim, typename T>
void operator*(const Matrix<dim, T>& lhs, std::vector<Vec<dim, T>>& rhs) {
	for (size_t j = 0; j < rhs.size(); ++j) {
		Vec<dim, T> col = rhs[j];
		for (size_t i = 0; i < dim; ++i) {
			rhs[j][i] = dot(lhs[i], col);
		}
	}
}

template<size_t dim, typename T>
void operator*(const Matrix<dim+1, T>& lhs, std::vector<Vec<dim, T>>& rhs) {
	for (size_t j = 0; j < rhs.size(); ++j) {
		Vec<dim, T> col = rhs[j];
		for (size_t i = 0; i < dim; ++i) {
			rhs[j][i] = dot(lhs[i], col);
		}
	}
}

template<size_t dim, typename T>
void operator*(const Matrix<dim + 1, T>& lhs, Vec<dim, T>& rhs) {
		Vec<dim, T> col = rhs;
		for (size_t i = 0; i < dim; ++i) {
			rhs[i] = dot(lhs[i], col);
		}
}

template<size_t dim, typename T>
void operator+=(Matrix<dim, T>& lhs, const Matrix<dim, T>& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] += rhs[i];
	}
}

template<size_t dim, typename T>
void operator-=(Matrix<dim, T>& lhs, const Matrix<dim, T>& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] -= rhs[i];
	}
}


///////////////////////////////////////////////////////////////////////////////
// (vector, scalar) operations

template<size_t dim, typename T>
Matrix<dim, T> operator+(const Matrix<dim, T>& lhs, const T& rhs) {
	Matrix<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] + rhs;
	}
	return ret;
}

template<size_t dim, typename T>
Matrix<dim, T> operator-(const Matrix<dim, T>& lhs, const T& rhs) {
	Matrix<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] - rhs;
	}
	return ret;
}

template<size_t dim, typename T>
Matrix<dim, T> operator*(const Matrix<dim, T>& lhs, const T& rhs) {
	Matrix<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] * rhs;
	}
	return ret;
}

template<size_t dim, typename T>
Matrix<dim, T> operator/(const Matrix<dim, T>& lhs, const T& rhs) {
	Matrix<dim, T> ret;
	for (size_t i = 0; i < dim; i++) {
		ret[i] = lhs[i] / rhs;
	}
	return ret;
}

template<size_t dim, typename T>
void operator+=(Matrix<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] += rhs;
	}
}

template<size_t dim, typename T>
void operator-=(Matrix<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] -= rhs;
	}
}

template<size_t dim, typename T>
void operator*=(Matrix<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] *= rhs;
	}
}

template<size_t dim, typename T>
void operator/=(Matrix<dim, T>& lhs, const T& rhs) {
	for (size_t i = 0; i < dim; i++) {
		lhs[i] /= rhs;
	}
}

using matrix3f = Matrix<3, double>;
	
#endif