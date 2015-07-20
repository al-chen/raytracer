#include "classes.h"

Color::Color() {
	r = 0.0;
	g = 0.0;
	b = 0.0;
}

Color::Color(float red, float green, float blue) {
	r = red;
	g = green;
	b = blue;
}

Color Color::add(Color one, Color two) {
	Color c(0.0,0.0,0.0);
	c.r = one.r + two.r;
	c.g = one.g + two.g;
	c.b = one.b + two.b;
	return c;
}