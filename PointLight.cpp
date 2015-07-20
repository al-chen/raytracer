#include "classes.h"

PointLight::PointLight(Point pos, Color clr) {
	position = pos;
	c = clr;
}

Vector PointLight::generateLightRay(Point local) {
	Vector l = local.subtract(position, local);
	l.normalize();
	return l;
}