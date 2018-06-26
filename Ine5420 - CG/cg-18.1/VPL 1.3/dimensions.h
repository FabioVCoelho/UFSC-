#ifndef DIMENSIONS_H
#define DIMENSIONS_H

template <typename T>
struct WinDims {
	WinDims() : WinDims(0, 0, 0, 0) {}
	WinDims(T xmin_, T ymin_, T width_, T height_)
		: xmin(xmin_), ymin(ymin_), width(width_), height(height_) {}

	void resize(T xmin_, T ymin_, T width_, T height_) {
		xmin = xmin_;
		ymin = ymin_;
		width = width_;
		height = height_;
	}

	template <typename T2> WinDims(const WinDims<T2> &other)
	{
		xmin = other.xmin;
		ymin = other.ymin;
		width = other.width;
		height = other.height;
	}

	T xmin, ymin, width, height;
};
//
//template <typename T>
//struct Dim2d {
//	Dim2d() : Dim2d(0, 0) {}
//	Dim2d(T wid, T hei)
//		: width(wid), height(hei) {}
//
//	void resize(T wid, T hei) {
//		width = wid;
//		height = hei;
//	}
//	void copy(const Dim2d<T>& src) {
//		width = src.width;
//		height = src.height;
//	}
//
//	T width, height;
//};

//template <typename T>
//struct Dims2d {
//    Dims2d() : Dims2d(0,0,0,0) {}
//    Dims2d(T xmin, T xmax, T ymin, T ymax)
//        : xMin(xmin), xMax(xmax), yMin(ymin), yMax(ymax) {}
//
//    void resize(T xmin, T xmax, T ymin, T ymax) {
//        xMin = xmin;
//        xMax = xmax;
//        yMin = ymin;
//        yMax = ymax;
//    }
//    void copy(const Dims2d<T>& src) {
//        xMin = src.xMin;
//        xMax = src.xMax;
//        yMin = src.yMin;
//        yMax = src.yMax;
//    }
//
//    T xMin, xMax, yMin, yMax;
//};
//
//template <typename T>
//struct Dim2d {
//	Dim2d() : Dim2d(0, 0) {}
//	Dim2d(T wid, T hei)
//		: width(wid), height(hei){}
//
//	void resize(T wid, T hei) {
//		width = wid;
//		height = hei;
//	}
//	void copy(const Dim2d<T>& src) {
//		width = src.width;
//		height = src.height;
//	}
//
//	T width, height;
//};

#endif