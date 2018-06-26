//#ifndef MATRIX3_H
//#define MATRIX3_H
//
//#include "matrix.h"
//
//template <typename T>
//class Matrix<3,T> {
//public:
//	Matrix() {}
//
//	template <typename U>
//	Matrix<3,T>(const Matrix<3, U>& p);
//
//	decltype(T[3])* operator[](const size_t dim) {
//		assert(dim < 3);
//		return rows[dim];
//	}
//	const T& operator[](const size_t dim) const {
//		assert(dim < 3);
//		return dim <= 0 ? m_x : m_y;
//	}
//
//	T[3][3] data;
//};
//
//template<typename T>
//Matrix<3,T> operator+(const Matrix<3,T>& lhs, const Matrix<3,T>& rhs) {
//	Matrix<3, T> ret;
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	ret.data[0][0] = lhs.data[0][0] + rhs.data[0][0];
//	return (Matrix<3,T>(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y));
//}
//
//template<typename T>
//Matrix<3,T> operator-(const Matrix<3,T>& lhs, const Matrix<3,T>& rhs) {
//	return (Matrix<3,T>(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y));
//}
//
//template<typename T>
//void operator+=(Matrix<3,T>& lhs, const Matrix<3,T>& rhs) {
//	lhs.m_x += rhs.m_x;
//	lhs.m_y += rhs.m_y;
//}
//
//template<typename T>
//void operator-=(Matrix<3,T>& lhs, const Matrix<3,T>& rhs) {
//	lhs.m_x -= rhs.m_x;
//	lhs.m_y -= rhs.m_y;
//}
//
//template<typename T>
//T dot(const Matrix<3,T>& lhs, const Matrix<3,T>& rhs) {
//	return T(lhs.m_x*rhs.m_x + lhs.m_y*rhs.m_y);
//}
//
//
//template<typename T>
//Matrix<3,T> operator+(const Matrix<3,T>& lhs, const T& rhs) {
//	return (Matrix<3,T>(lhs.m_x + rhs, lhs.m_y + rhs));
//}
//template<typename T>
//Matrix<3,T> operator-(const Matrix<3,T>& lhs, const T& rhs) {
//	return (Matrix<3,T>(lhs.m_x - rhs, lhs.m_y - rhs));
//}
//template<typename T>
//Matrix<3,T> operator*(const Matrix<3,T>& lhs, const T& rhs) {
//	return (Matrix<3,T>(lhs.m_x * rhs, lhs.m_y * rhs));
//}
//template<typename T>
//Matrix<3,T> operator/(const Matrix<3,T>& lhs, const T& rhs) {
//	return (Matrix<3,T>(lhs.m_x / rhs, lhs.m_y / rhs));
//}
//template<typename T>
//void operator+=(Matrix<3,T>& lhs, const T& rhs) {
//	lhs.m_x += rhs;
//	lhs.m_y += rhs;
//}
//template<typename T>
//void operator-=(Matrix<3,T>& lhs, const T& rhs) {
//	lhs.m_x -= rhs;
//	lhs.m_y -= rhs;
//}
//template<typename T>
//void operator*=(Matrix<3,T>& lhs, const T& rhs) {
//	lhs.m_x *= rhs;
//	lhs.m_y *= rhs;
//}
//template<typename T>
//void operator/=(Matrix<3,T>& lhs, const T& rhs) {
//	lhs.m_x /= rhs;
//	lhs.m_y /= rhs;
//}
//
//
//
//using Vec2i = Vec<2, int>;
//using Vec2f = Vec<2, double>;
//
//#endif