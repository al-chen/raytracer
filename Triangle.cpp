#include "classes.h"
#include <math.h>

Triangle::Triangle() {
    isTri = true;
    has_n = false;
}

Triangle::Triangle(Point a_in, Point b_in, Point c_in, Color ka, Color kd, Color ks, Color kr, float sp, Vector a_n, Vector b_n, Vector c_n) {
    isTri = true;
    has_n = true;

    a = a_in;
    b = b_in;
    c = c_in;

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

    an = a_n;
    bn = b_n;
    cn = c_n;       
}

Triangle::Triangle(Point a_in, Point b_in, Point c_in, Vector a_n, Vector b_n, Vector c_n) {
    isTri = true;
    has_n = true;
    a = a_in;
    b = b_in;
    c = c_in;

    an = a_n;
    bn = b_n;
    cn = c_n;
}

Triangle::Triangle(Point a_in, Point b_in, Point c_in, Color ka, Color kd, Color ks, Color kr, float sp) {
    isTri = true;
    has_n = false;

    a = a_in;
    b = b_in;
    c = c_in;

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

Triangle::Triangle(Point a_in, Point b_in, Point c_in) {
    isTri = true;
    has_n = false;
    a = a_in;
    b = b_in;
    c = c_in;
    kd_r = 1.0;
    kd_g = 1.0;
    kd_b = 1.0;
    ks_r = 1.0;
    ks_g = 1.0;
    ks_b = 1.0;
    p = 64;
}


bool Triangle::intersect(Ray R) {
    Point e = R.position;
    Vector d = R.direction;

    float aa = a.x - b.x;
    float bb = a.y - b.y;
    float cc = a.z - b.z;

    float dd = a.x - c.x;
    float ee = a.y - c.y;
    float ff = a.z - c.z;

    float gg = d.x;
    float hh = d.y;
    float ii = d.z;

    float jj = a.x - e.x;
    float kk = a.y - e.y;
    float ll = a.z - e.z;

    float M = aa*(ee*ii - hh*ff) + bb*(gg*ff - dd*ii) + cc*(dd*hh - ee*gg);

    float lambda = (ii * (aa*kk - jj*bb) + hh*(jj*cc - aa*ll) + gg*(bb*ll - kk*cc)) / M;
    if (lambda < 0 || lambda > 1) {
        return false;
    }

    float beta = (jj*(ee*ii - hh*ff) + kk*(gg*ff - dd*ii) + ll*(dd*hh - ee*gg)) / M;

    

    if (beta < 0 || beta > (1-lambda)) {
        return false;
    }
    return true;
}


float Triangle::getT(Ray r) {
    Point e = r.position;
    Vector d = r.direction;

    float aa = a.x - b.x;
    float bb = a.y - b.y;
    float cc = a.z - b.z;

    float dd = a.x - c.x;
    float ee = a.y - c.y;
    float ff = a.z - c.z;

    float gg = d.x;
    float hh = d.y;
    float ii = d.z;

    float jj = a.x - e.x;
    float kk = a.y - e.y;
    float ll = a.z - e.z;

    float M = aa*(ee*ii - hh*ff) + bb*(gg*ff - dd*ii) + cc*(dd*hh - ee*gg);

    float t = -(ff*(aa*kk - jj*bb) + ee*(jj*cc - aa*ll) + dd*(bb*ll - kk*cc)) / M;
    return t;
}
Vector Triangle::getNormal(Point p) {
    if (has_n) {
        Vector bMinusA = b.subtract(b,a);
        Vector cMinusA = c.subtract(c,a);
        Vector normal = bMinusA.crossProduct(bMinusA, cMinusA);
        normal.normalize();
        return normal;   
    } else {
        Vector bMinusA = b.subtract(b,a);
        Vector cMinusA = c.subtract(c,a);
        Vector normal = bMinusA.crossProduct(bMinusA, cMinusA);
        normal.normalize();
        return normal;    
    }
    
}