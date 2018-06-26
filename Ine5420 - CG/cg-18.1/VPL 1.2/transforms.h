#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix.h"
#include <cmath>
using angle_t = double;

template<typename T>
struct Shift3 : public Matrix<3, T> {
	Shift3(T sx, T sy) {
		m_data[0][0] = m_data[1][1] = m_data[2][2] = 1;
		m_data[0][2] = sx;
		m_data[1][2] = sy;
	}
};

template<typename T>
struct Scale3 : public Matrix<3, T> {
	Scale3(double sx, double sy) {
		m_data[0][0] = sx;
		m_data[1][1] = sy;
		m_data[2][2] = 1;
	}
};

template<typename T>
struct ScaleCenter3 : public Matrix<3, T> {
	ScaleCenter3(double sx, double sy, const Vec<2, T>& center) {
		m_data[0][0] = sx;
		m_data[1][1] = sy;
		m_data[2][2] = 1;
		m_data[0][2] = center[0] * (1 - sx);
		m_data[1][2] = center[1] * (1 - sy);
	}
};

template<typename T>
struct Rotate3 : public Matrix<3, T> {
	Rotate3(angle_t angle) {
		double s = sin(angle);
		double c = cos(angle);
		m_data[0][0] = c;
		m_data[1][1] = c;
		m_data[2][2] = 1;
		m_data[0][1] = s;
		m_data[1][0] = -s;
	}
};

template<typename T>
struct RotateCenter3 : public Matrix<3, T> {
	RotateCenter3(angle_t angle, const Vec<2, T>& center) {
		double s = sin(angle);
		double c = cos(angle);
		m_data[0][0] = c;
		m_data[1][1] = c;
		m_data[2][2] = 1;
		m_data[0][1] = s;
		m_data[1][0] = -s;
		m_data[0][2] = center[0] * (1 - c) - center[1] * s;
		m_data[1][2] = center[1] * (1 - c) + center[0] * s;
	}
};




using shift3f = Shift3<double>;
using scale3f = Scale3<double>;
using scalec3f = ScaleCenter3<double>;
using rotate3f = Rotate3<double>;
using rotatec3f = RotateCenter3<double>;

#endif
