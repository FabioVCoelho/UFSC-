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

#endif