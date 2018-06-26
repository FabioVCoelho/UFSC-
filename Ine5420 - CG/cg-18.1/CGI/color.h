#ifndef COLOR_H
#define COLOR_H

struct Color {
	Color() : Color(255, 255, 255) {}

	Color(double r, double g, double b)
		: red(r), green(g), blue(b) {}

	double red, green, blue;
};

#endif
