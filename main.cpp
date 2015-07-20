#include "classes.h"

int main(int argc, char *argv[]) {
	// Point eye(0,0,0);
	// Point LL(-1,-1,-3);
	// Point LR(1,-1,-3);
	// Point UL(-1,1,-3);
	// Point UR(1,1,-3);
	
	// Student example reflection
	// Point eye(0,0,2);
	// Point LL(-1,-1,1);
	// Point LR(1,-1,1);
	// Point UL(-1,1,1);
	// Point UR(1,1,1);

	// Color lta(1,1,1);

	// Matrix m;
	// Matrix m_inv;
	// Matrix s;
	// Matrix t;
	// Matrix r;

	// Scene scene(500, 500, eye, UL, UR, LL, LR, lta);

	// Example scene to test reflection
	// mat   kar kag kab   kdr kdg kdb  ksr ksg ksb  ksp  krr  krg  krb 
	// mat   0.1 0.1 0.1   0.5 0.5 0.5   0   0   0   64   0.8  0.8  0.8
	// scene.lights.push_back(new PointLight(Point(1,1,1), Color(255,255,255)));
	// scene.shapes.push_back(new Sphere(Point(1,-0.8,0.3), 0.3, Color(0.1,0.1,0.1), Color(0.5,0.5,0.5), Color(0,0,0), Color(0.8,0.8,0.8), 64, m));
	// scene.shapes.push_back(new Triangle(Point(-2,-2,0), Point(2,-2,-1), Point(2,2,0), Color(0.1,0.1,0.1), Color(0.5,0.5,0.5), Color(0,0,0), Color(0.8,0.8,0.8), 64));

	// Example scene
	// scene.lights.push_back(new DirectionalLight(Vector(0.57737027, -0.57737027, -0.57737027), Color(255,255,255)));
	// scene.lights.push_back(new DirectionalLight(Vector(0.57737027, 0.57737027, -0.57737027), Color(0,0,255)));
	// scene.shapes.push_back(new Sphere(Point(0,0,-20),  3, Color(0.1,0.1,0.1), Color(1,0,1), Color(1,1,1), Color(0,0,0), 50, m_inv));
	// scene.shapes.push_back(new Sphere(Point(-2,2,-15), 1, Color(0.1,0.1,0.1), Color(1,1,0), Color(1,1,1), Color(0,0,0), 50, m_inv));
	// scene.shapes.push_back(new Sphere(Point(-2,-2,-15),1, Color(0.1,0.1,0.1), Color(0,1,1), Color(1,1,1), Color(0,0,0), 50, m_inv));
	// scene.shapes.push_back(new Triangle(Point(5,5,-17), Point(1,4,-20), Point(6,-1,-20), Color(0.1,0.1,0.1), Color(0.1,0.1,0.1), Color(1,1,1), Color(1,1,1), 50));

	// t = t.translationMatrix(Vector(-1,1,0));
	// m = m.matrixMult(m,t);
	// m_inv = m.matrixMult(t.translationInverse(t), m_inv);

	// s = s.scaleMatrix(Vector(1.5,1,1));
	// m = m.matrixMult(m,s);
	// m_inv = m.matrixMult(s.scaleInverse(s), m_inv);

	// m = m.rotateMatrixX(Vector(0,0,0));
	// m_inv = m.rotationInverseX(m);

	// for (int i = 0; i < 4; i++) {
	// 	cout << endl;
	// 	for (int j = 0; j < 4; j++) {
	// 		cout << m.mat[i][j] << " ";
	// 	}
	// }
	// cout << endl;
	// for (int i = 0; i < 4; i++) {
	// 	cout << endl;
	// 	for (int j = 0; j < 4; j++) {
	// 		cout << m_inv.mat[i][j] << " ";
	// 	}
	// }
	// cout << endl;

	// scene.shapes.push_back(new Sphere(Point(0,0,-8),1, Color(0.1,0.1,0.1), Color(1,1,1), Color(1,1,1), Color(1,1,1), 64, m_inv));
	// scene.lights.push_back(new PointLight(Point(-3,0,0), Color(255,255,255)));
	// scene.lights.push_back(new DirectionalLight(Vector(0,0,-1), Color(255,255,255)));

	Scene scene(argv[1], 1000, 1000);

	Film testFilm(&scene);
	Raytracer raytracer(&scene);
	scene.render(testFilm, raytracer);
	testFilm.writeImage();
	return 0;
}