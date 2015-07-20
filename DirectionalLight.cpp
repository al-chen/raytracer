#include "classes.h"

DirectionalLight::DirectionalLight(Vector dir, Color clr) {
	direction = dir;
	c = clr;
}

Vector DirectionalLight::generateLightRay(Point local) {
	Vector l = direction;
	l.normalize();
	l = l.scalarMult(-1, l);
	return l;
}