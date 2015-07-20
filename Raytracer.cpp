#include "classes.h"
#include <math.h>

Raytracer::Raytracer(Scene* scene_in) {
	scene = scene_in;
}

Color Raytracer::trace(Ray r, int depth) {
	Color c(0.0, 0.0, 0.0);

	Point e = r.position;
	Vector d = r.direction;

	int best_sphere = -1;
	int best_shape = -1;
	float best_t = -1.0;
	float t;
	float t1,t2;
	
	Vector minusD = d.scalarMult(-1,d);
	float dDotD = d.dotProduct(d,d);
	Vector eMinusC;

	for (int i = 0; i < scene->shapes.size(); i++) {
		Shape* s = scene->shapes[i];
		if (s->intersect(r)) {
			// return Color(255,255,255);
			t = s->getT(r);
			if (t < best_t || best_t == -1) {
				// cout << t << endl;
				best_shape = i;
				best_t = t;
			}
		}
	}

	if (best_shape < 0) {
		return c;
	}

	Shape* s = scene->shapes[best_shape];

	// Necessary for transformations??
	e = s->m_inv.pointMult(s->m_inv, e);
	d = s->m_inv.vectorMult(s->m_inv, d);
	// d.normalize();
	
	Point p(e.x+best_t*d.x, e.y+best_t*d.y, e.z+best_t*d.z);
	Vector n = s->getNormal(p);

	// Ambient
	c.r += s->ka_r * scene->lta.c.r * 255;
	c.g += s->ka_g * scene->lta.c.g * 255;
	c.b += s->ka_b * scene->lta.c.b * 255;

	Vector view = e.subtract(e, p);
	view.normalize();
	float nDotL, nDotH;

	for (int i = 0; i < scene->lights.size(); i++) {
		Light* li = scene->lights[i];
		Vector l = li->generateLightRay(p);
		nDotL = n.dotProduct(n,l);
		// cout << nDotL << endl;
		nDotL = max(nDotL, 0.0f);

		// Shadow
		bool blocked = false;
		Ray shadow(p, l);
		for (int j = 0; j < scene->shapes.size(); j++) {
			Shape* block = scene->shapes[j];
			if (block != s) {
				if (block->getT(shadow) > 0) {
					blocked = true;
					break;
				}
			}
		}
		if (blocked) {
			continue;
		}

		// Diffuse
		c.r += s->kd_r * li->c.r * nDotL;
		c.g += s->kd_g * li->c.g * nDotL;
		c.b += s->kd_b * li->c.b * nDotL;

		Vector r = l.add(l.scalarMult(-1,l), n.scalarMult(2.0*n.dotProduct(l,n), n));
		r.normalize();
		float viewDotR = view.dotProduct(view,r);
		viewDotR = max(0.0f, viewDotR);

		c.r += s->ks_r * li->c.r * pow(viewDotR, s->p);
		c.g += s->ks_g * li->c.g * pow(viewDotR, s->p);
		c.b += s->ks_b * li->c.b * pow(viewDotR, s->p);

		/* reflect = d - 2(d.n)n */
		// if (depth > 0) {
		// 	Vector ref;
		// 	float dDotN = d.dotProduct(d,n);
		// 	ref = d.subtract(d, n.scalarMult(2*dDotN, n));
		// 	ref.normalize();
		// 	Ray reflect(p, ref);
		// 	Color rc;
		// 	rc = rc.add(rc, trace(reflect, depth-1));
		// 	c.r += s->kr_r * rc.r;
		// 	c.g += s->kr_g * rc.g;
		// 	c.b += s->kr_b * rc.b;
		// }
	}



	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	return c;
}