#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix.h"
#include "types.h"
#include "dimensions.h"
#include "transforms.h"
#include <cmath>


template<typename T>
struct Shift3 : public Matrix<3, T> {
	Shift3() {}
	Shift3(T sx, T sy) {
		Matrix<3, T>::m_data[0][0] = Matrix<3, T>::m_data[1][1] = Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][2] = sx;
		Matrix<3, T>::m_data[1][2] = sy;
	}
	Shift3(const Vec<2, T>& vec) {
		Matrix<3, T>::m_data[0][0] = Matrix<3, T>::m_data[1][1] = Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][2] = vec[0];
		Matrix<3, T>::m_data[1][2] = vec[1];
	}
};

template<typename T>
struct Scale3 : public Matrix<3, T> {
	Scale3() {}
	Scale3(double sx, double sy) {
		Matrix<3, T>::m_data[0][0] = sx;
		Matrix<3, T>::m_data[1][1] = sy;
		Matrix<3, T>::m_data[2][2] = 1;
	}
};

template<typename T>
struct ScaleCenter3 : public Matrix<3, T> {	 	  	 	     	   		   	      	 	    	 	
	ScaleCenter3() {}
	ScaleCenter3(double sx, double sy, const Vec<2, T>& center) {
		Matrix<3, T>::m_data[0][0] = sx;
		Matrix<3, T>::m_data[1][1] = sy;
		Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][2] = center[0] * (1 - sx);
		Matrix<3, T>::m_data[1][2] = center[1] * (1 - sy);
	}
};

template<typename T>
struct Rotate3 : public Matrix<3, T> {
	Rotate3() {}
	Rotate3(angle_t angle) {
		double s = sin(angle);
		double c = cos(angle);
		Matrix<3, T>::m_data[0][0] = c;
		Matrix<3, T>::m_data[1][1] = c;
		Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][1] = -s;
		Matrix<3, T>::m_data[1][0] = s;
	}
};

template<typename T>
struct RotateCenter3 : public Matrix<3, T> {
	RotateCenter3() {}
	RotateCenter3(angle_t angle, const Vec<2, T>& center) {
		double s = sin(angle);
		double c = cos(angle);
		Matrix<3, T>::m_data[0][0] = c;
		Matrix<3, T>::m_data[1][1] = c;
		Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][1] = -s;
		Matrix<3, T>::m_data[1][0] = s;
		Matrix<3, T>::m_data[0][2] = center[0] * (1 - c) + center[1] * s;
		Matrix<3, T>::m_data[1][2] = center[1] * (1 - c) - center[0] * s;
		/*m_data[0][2] = center[0] * (c - 1) + center[1] * s;
		m_data[1][2] = center[1] * (c - 1) - center[0] * s;*/
	}	 	  	 	     	   		   	      	 	    	 	
};

template<typename T>
struct ShiftRotate3 : public Matrix<3, T> {
	ShiftRotate3() {}
	ShiftRotate3(const Vec<2, T>& shift, angle_t angle) {
		double s = sin(angle);
		double c = cos(angle);
		Matrix<3, T>::m_data[0][0] = c;
		Matrix<3, T>::m_data[1][1] = c;
		Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][1] = -s;
		Matrix<3, T>::m_data[1][0] = s;
		Matrix<3, T>::m_data[0][2] = c*shift[0] - s*shift[1];
		Matrix<3, T>::m_data[1][2] = c*shift[1] + s*shift[0];
	}
};

template<typename T>
struct RotateShift3 : public Matrix<3, T> {
	RotateShift3() {}
	RotateShift3(angle_t angle, const Vec<2, T>& shift) {
		double s = sin(angle);
		double c = cos(angle);
		Matrix<3, T>::m_data[0][0] = c;
		Matrix<3, T>::m_data[1][1] = c;
		Matrix<3, T>::m_data[2][2] = 1;
		Matrix<3, T>::m_data[0][1] = -s;
		Matrix<3, T>::m_data[1][0] = s;
		Matrix<3, T>::m_data[0][2] = shift[0];
		Matrix<3, T>::m_data[1][2] = shift[1];
	}
};

template<typename T>
struct WinVp3: public Matrix<3, T> {	 	  	 	     	   		   	      	 	    	 	
	WinVp3() {}
	WinVp3(const WinDims<unit>& windims, const WinDims<int>& vpdims) {
		double dx = vpdims.width / windims.width;
		double dy = vpdims.height / windims.height;

		Matrix<3, T>::m_data[0][0] = dx;
		Matrix<3, T>::m_data[1][1] = -dy;
		Matrix<3, T>::m_data[2][2] = 1;

		Matrix<3, T>::m_data[0][1] = 0;
		Matrix<3, T>::m_data[1][0] = 0;
		
		Matrix<3, T>::m_data[0][2] = -dx*windims.xmin + vpdims.xmin;
		Matrix<3, T>::m_data[1][2] = (1 + windims.ymin / windims.height) * vpdims.height + vpdims.ymin;
		
	}
};

//template<typename T>
//void winVpTransf(
//	const WinVp3<T>& transf,
//	const std::vector<Vec<2, T>>& winCoords)
//{
//	for (size_t j = 0; j < winCoords.size(); ++j) {
//		Vec<2, T> col = winCoords[j];
//		for (size_t i = 0; i < 2; ++i) {
//			vpcoords[j][i] = transf[i][0] * col[0] + transf[i][1] * col[1] + transf[i][2];
//		}
//	}
//}


template<typename T>
void winVpTransf(
	const WinVp3<T>& transf,
	const std::vector<Vec<2, T>>& winCoords,
	std::vector<Vec<2, int>>& vpcoords)
{	 	  	 	     	   		   	      	 	    	 	
	assert(winCoords.size() == vpcoords.size());
	for (size_t j = 0; j < winCoords.size(); ++j) {
		Vec<2, T> col = winCoords[j];
		for (size_t i = 0; i < 2; ++i) {
			vpcoords[j][i] = transf[i][0] * col[0] + transf[i][1] * col[1] + transf[i][2];
		}
	}
}

template<typename T>
void winVpTransf(
	const WinVp3<T>& transf, 
	const std::vector<Vec<2, T>>& clippedWinCoords, 
	size_t numClippedPoints, 
	std::vector<Vec<2, int>>& vpcoords) 
{
	assert(numClippedPoints <= vpcoords.size());
	for (size_t j = 0; j < numClippedPoints; ++j) {
		Vec<2, T> col = clippedWinCoords[j];
		for (size_t i = 0; i < 2; ++i) {
			vpcoords[j][i] = transf[i][0] * col[0] + transf[i][1] * col[1] + transf[i][2];
		}
	}
}

template<typename T>
std::vector<Vec<2, int>> winVpTransf(const WinVp3<T>& transf, const std::vector<Vec<2, T>>& wincoords) {
	std::vector<Vec<2, int>> ret(wincoords.size());
	winVpTransf(transf, wincoords, ret);
	return ret;
}

//template<typename T>
//std::vector<Vec<2, int>> winVpTransf(const WinVp3<T>& transf, const std::vector<Vec<2, T>>& wincoords) {
//	std::vector<Vec<2, int>> ret(wincoords.size());
//	for (size_t j = 0; j < wincoords.size(); ++j) {	 	  	 	     	   		   	      	 	    	 	
//		Vec<2, T> col = wincoords[j];
//		for (size_t i = 0; i < 2; ++i) {
//			ret[j][i] = transf[i][0] * col[0] + transf[i][1] * col[1] + transf[i][2];
//		}
//	}
//	return ret;
//}


using shift3f = Shift3<double>;
using scale3f = Scale3<double>;
using scalec3f = ScaleCenter3<double>;
using rotate3f = Rotate3<double>;
using rotatec3f = RotateCenter3<double>;
using shiftrotate3f = ShiftRotate3<double>;
using rotateshift3f = RotateShift3<double>;
using winvp3f = WinVp3<double>;


#endif
