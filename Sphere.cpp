#include "classes.h"
#include <math.h>

Sphere::Sphere() {
	isTri = false;
	center = Point(0,0,0);
	radius = 1;
}

Sphere::Sphere(Point ctr, float r, Color ka, Color kd, Color ks, Color kr, float sp, Matrix transform) {
	m_inv.set(transform);
	isTri = false;

	radius = r;
	center = ctr;

	ka_r = ka.r;
	ka_g = ka.g;
	ka_b = ka.b;

	kd_r = kd.r;
	kd_g = kd.g;
	kd_b = kd.b;

	ks_r = ks.r;
	ks_g = ks.g;
	ks_b = ks.b;

	kr_r = kr.r;
	kr_g = kr.g;
	kr_b = kr.b;

	p = sp;
}

Sphere::Sphere(Point ctr, float r) {
	isTri = false;
	radius = r;
	center = ctr;

	ka_r = 0.1;
	ka_g = 0.1;
	ka_b = 0.1;

	kd_r = 1.0;
	kd_g = 1.0;
	kd_b = 1.0;

	ks_r = 1.0;
	ks_g = 1.0;
	ks_b = 1.0;

	kr_r = 1.0;
	kr_g = 1.0;
	kr_b = 1.0;

	p = 64;
}

bool Sphere::intersect(Ray R) {
	Point e = R.position;
	Vector direction = R.direction;

	// Matrix
	e = m_inv.pointMult(m_inv, e);
	direction = m_inv.vectorMult(m_inv, direction);
	// direction.normalize();

	float a = direction.dotProduct(direction, direction);
	Vector twoD = direction.scalarMult(2.0, direction);
	Vector eMinusC = e.subtract(e, center);
	float b = twoD.dotProduct(twoD, eMinusC);
	float c = eMinusC.dotProduct(eMinusC, eMinusC) - pow(radius, 2);
	float discriminant = pow(b, 2) - 4*a*c;
	if (discriminant < 0) {
		return false;
	}

	return true;
}

float Sphere::getT(Ray r) {
	Point e = r.position;
	Vector d = r.direction;

	// Matrix
	e = m_inv.pointMult(m_inv, e);
	d = m_inv.vectorMult(m_inv, d);
	// d.normalize();

	Vector minusD = d.scalarMult(-1,d);
	float dDotD = d.dotProduct(d,d);
	Vector eMinusC;
	eMinusC = e.subtract(e, center);

	float t;
	float t1,t2;
	t = minusD.dotProduct(minusD, eMinusC);
	t1 = (t + pow( pow(d.dotProduct(d,eMinusC), 2) - dDotD * (eMinusC.dotProduct(eMinusC,eMinusC)-pow(radius,2)), 0.5)) / dDotD;
	t2 = (t - pow( pow(d.dotProduct(d,eMinusC), 2) - dDotD * (eMinusC.dotProduct(eMinusC,eMinusC)-pow(radius,2)), 0.5)) / dDotD;
	t1 = max(t1, 0.0f);
	t2 = max(t2, 0.0f);
	t = min(t1,t2);
	return t;
}

Vector Sphere::getNormal(Point p) {
	Vector n = p.subtract(p, center);
	// Vector n = p.subtract(p, m_inv.pointMult(m_inv, center));
	// n.normalize();
	// return n;
	Matrix m_inv_transpose = m_inv.transpose(m_inv);
	n = m_inv_transpose.vectorMult(m_inv_transpose, n);
	n.normalize();
	return n;
}