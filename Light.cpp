#include "classes.h"

Light::Light() {
	c = Color(0,0,0);
}

Light::Light(Color clr) {
	c = clr;
}
// generate a ray starting from the position stored in local to the position of the light source
Vector Light::generateLightRay(Point local) {};
