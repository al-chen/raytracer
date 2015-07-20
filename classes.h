#ifndef CLASSES_H
#define CLASSES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class Vector;
class Point;
class Ray;
class Color;
class Light;
class PointLight;
class DirectionalLight;
class Matrix;
class Shape;
class Sphere;
class Triangle;
class Scene;
class Film;
class Raytracer;
class ObjParser;

class Vector {
public:
    float x, y, z;

    // Constructors for the class
    Vector();
    Vector(float input_x, float input_y, float input_z);

    //Functions for the class
    float length();
    Vector add(Vector one, Vector two);
    Vector subtract(Vector one, Vector two);
    Vector scalarMult(float num, Vector vec);
    Vector scalarDiv(float num, Vector vec);
    Vector normal(Vector vec);
    void normalize();
    float dotProduct(Vector one, Vector two);
    Vector crossProduct(Vector one, Vector two);
    Vector makeVector(Point one, Point two);
};

class Point {
public:
    float x, y, z; // the coordinate of the point

    // Constructors for the class
    Point();
    Point(float input_x, float input_y, float input_z);

    // Functions for the class 
    Vector add(Point one, Point two);
    Vector subtract(Point one, Point two);
};

class Ray {
    // ray(t) = pos + t * dir, where t_min <= t <= t_max
public:
    Point position;
    Vector direction;
    float t_min, t_max;

    Ray(Point pt, Vector dir);
    Ray(Point input_start, Vector input_direction, float input_t_max, float input_t_min);

    // void setRay(Point input_start, Vector input_direction, float input_t_max, float input_t_min);
    // Ray getRay(float t);
};

class Color {
public:
    float r, g, b;

    Color();
    Color(float red, float green, float blue);
    Color add(Color one, Color two);
};

class Light {
public:
    Color c;
    Light();
    Light(Color clr);
    // generate a ray starting from the position stored in local to the position of the light source
    virtual Vector generateLightRay(Point local);
};

class PointLight : public Light {
public:
    Point position;

    PointLight(Point pos, Color clr);

    Vector generateLightRay(Point local);
};

class DirectionalLight : public Light {
public:
    Vector direction;
    DirectionalLight(Vector dir, Color clr);

    Vector generateLightRay(Point local);
};

class Matrix {
public:
    float mat[4][4]; 

    Matrix();
    // Matrix(float a[4][4]);

    Matrix rotateMatrixX(Vector vec);
    Matrix rotateMatrixY(Vector vec);
    Matrix rotateMatrixZ(Vector vec);
    Matrix translationMatrix(Vector center);
    Matrix scaleMatrix(Vector scale);
    Matrix matrixMult(Matrix mat1, Matrix mat2);
    void set(Matrix m);
    Matrix scaleInverse(Matrix m);
    Matrix translationInverse(Matrix m);
    Matrix rotationInverseX(Matrix m);
    Matrix rotationInverseY(Matrix m);
    Matrix rotationInverseZ(Matrix m);
    Point pointMult(Matrix m, Point p);
    Vector vectorMult(Matrix m, Vector v);
    Matrix transpose(Matrix m);

};


class Shape {
public:
    bool isTri;

    float ka_r;
    float ka_g;
    float ka_b;

    float kd_r;
    float kd_g;
    float kd_b;

    float ks_r;
    float ks_g;
    float ks_b;

    float kr_r;
    float kr_g;
    float kr_b;

    float p;

    Matrix m_inv;

    Shape();
    virtual bool intersect(Ray R);
    virtual float getT(Ray r);
    virtual Vector getNormal(Point p);
};

class Sphere : public Shape {
public:
    Point center;
    float radius;

    Sphere();
    Sphere(Point ctr, float r);
    Sphere(Point ctr, float r, Color ka, Color kd, Color ks, Color kr, float sp, Matrix transform);

    bool intersect(Ray R);
    float getT(Ray r);
    Vector getNormal(Point p);
};

class Triangle : public Shape {
public:

    Point a;
    Point b;
    Point c;
    Vector an;
    Vector bn;
    Vector cn;
    float alp, bet, lam;

    bool has_n;

    Triangle();
    Triangle(Point a_in, Point b_in, Point c_in);
    Triangle(Point a_in, Point b_in, Point c_in, Color ka, Color kd, Color ks, Color kr, float sp);
    Triangle(Point a_in, Point b_in, Point c_in, Color ka, Color kd, Color ks, Color kr, float sp, Vector a_n, Vector b_n, Vector c_n);
    Triangle(Point a_in, Point b_in, Point c_in, Vector a_n, Vector b_n, Vector c_n);

    bool intersect(Ray R);
    float getT(Ray r);
    Vector getNormal(Point p);
};

class ObjParser {
public:
    ObjParser();
    ObjParser(const char* file);
    vector<Point> v;
    vector<Triangle*> triangles;
    vector<Vector> vn;
};


class Scene {
public:
	string output_image;
	int width, height;
	Point eye;
	Point ul;
	Point ur;
	Point ll;
	Point lr;

    Light lta;
    vector<Shape*> shapes;
    vector<Light*> lights;

    ObjParser obj;

	// Constructor
    Scene(string file, int w, int h);
	Scene(int w, int h, Point eyePos, Point upperLeft, Point upperRight, Point lowerLeft, Point lowerRight, Color ltac);

	void render(Film film, Raytracer raytracer);
};

// extern Scene *scene;

class Film {
public:
    Scene* scene;
	string output_image;
	int width, height, size, stride_in_bytes, comp;
	char *data;
    

	Film(Scene* scene_in);

	void testCircle();
	void set(int i, int j, float r, float g, float b);
    void set(int i, int j, Color clr);
	// void commit(Sample& sample, Color& color);
	void writeImage();
};

class Raytracer {
public:
    Scene* scene;
    Raytracer(Scene* scene_in);

    Color trace(Ray r, int depth=1);
};


#endif

