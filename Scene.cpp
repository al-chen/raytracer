#include "classes.h"
#include "fstream"
#include "string"
#include "sstream"

Scene::Scene(string file, int w, int h) {

    std::ifstream infile(file.c_str());

    // std::string line;
    


    Color ka = Color(0, 0, 0);
    float kspower = 0.0;
    Color kd = Color(0, 0, 0);
    Color ks = Color(0, 0, 0);
    Color kr = Color(0, 0, 0);
    Matrix m, m_inv;


    while (infile){
        string line;
        while (getline(infile, line)) {

            istringstream is(line);
            string cmd;
            is >> cmd;


            if (cmd == "cam") {
                float ex, ey, ez, llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz;
                is >> ex >> ey >> ez >> llx >> lly >> llz >> lrx >> lry >> lrz >> ulx >> uly >> ulz >> urx >> ury >> urz;
                eye = Point(ex, ey, ez);
                ll = Point(llx, lly, llz);
                lr = Point(lrx, lry, lrz);
                ul = Point(ulx, uly, ulz);
                ur = Point(urx, ury, urz);
                // cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz 
                

            }else if ( cmd == "sph") {
                float cx, cy, cz, r;
                // sph cx cy cz r 
                is >> cx >> cy >> cz >> r;
                Sphere* sphere = new Sphere(Point(cx, cy, cz), r,  ka, kd, ks, kr, kspower, m_inv);
                shapes.push_back(sphere);

            }else if (cmd == "tri"){
                float ax, ay, az, bx, by, bz, cx, cy, cz;
                // tri ax ay az bx by bz cx cy cz
                is >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;
                Triangle* triangle = new Triangle(Point(ax, ay, az), Point(bx, by, bz), Point(cx, cy, cz), ka, kd, ks, kr, kspower);
                shapes.push_back(triangle);

            }else if (cmd == "obj") {
                // parse in the obj file
                string objFile;
                is >> objFile;
                obj = ObjParser(objFile.c_str());
                for (int i = 0; i < obj.triangles.size(); i++){
                    Triangle* triangle = obj.triangles[i];
                    Triangle* toPush;
                    // if (triangle->has_n) {
                    //     toPush = new Triangle(triangle->a, triangle->b, triangle->c, ka, kd, ks, kr, kspower, triangle->an, triangle->bn, triangle->cn);
                    // } else {
                    //     toPush = new Triangle(triangle->a, triangle->b, triangle->c, ka, kd, ks, kr, kspower);    
                    // }
                    toPush = new Triangle(triangle->a, triangle->b, triangle->c, ka, kd, ks, kr, kspower);    
                    
                	shapes.push_back(toPush);
                }

            }else if (cmd == "ltp") {
                float px, py, pz, r, g, b;
                float falloff = 0; 
                // ltp px py pz r g b [falloff] 
                is >> px >> py >> pz >> r >> g >> b ; 
                PointLight* pl = new PointLight(Point(px, py, pz), Color(r*255, g*255, b*255)); 
                lights.push_back(pl);

            }else if (cmd == "ltd") {
                float dx, dy, dz, r, g, b;
                // ltd dx dy dz r g b 
                is >> dx >> dy >> dz >> r >> g >> b; 
                DirectionalLight* dl = new DirectionalLight(Vector(dx, dy, dz), Color(r*255, g*255, b*255)); 
                lights.push_back(dl);

            }else if (cmd == "lta") {
                float r, g, b;
                // lta r g b 
                is >> r >> g >> b; 
                lta.c = Color(r, g, b);

            }else if (cmd == "mat") {
                float kar, kag, kab, kdr, kdg, kdb, ksr, ksg, ksb, ksp, krr, krg, krb;
                // mat kar kag kab kdr kdg kdb ksr ksg ksb ksp krr krg krb
                // Where ka, kd, ks, and kr are the coefficients for ambient, diffuse, specular, and reflective.
                is >> kar >> kag >> kab >> kdr >> kdg >> kdb >> ksr >> ksg >> ksb >> ksp >> krr >> krg >> krb;
                ka = Color(kar, kag, kab);
                kd = Color(kdr, kdg, kdb);
                kspower = ksp;
                ks = Color(ksr, ksg, ksb);
                kr = Color(krr, krg, krb);
                // cout << ka.r << ka.g << ka.b << kd.r << kd.g << kd.b << "\n";
            }else if (cmd == "xft") {
                // xft tx ty tz
                float tx, ty, tz;
                is >> tx >> ty >> tz;
                Matrix t = m.translationMatrix(Vector(tx,ty,tz));
                m = m.matrixMult(m, t);
                m_inv = m_inv.matrixMult(t.translationInverse(t), m_inv);
                // for (int i = 0; i < 4; i++) {
                //     cout << endl;
                //     for (int j = 0; j < 4; j++) {
                //         cout << m.mat[i][j] << " ";
                //     }
                // }
                // for (int i = 0; i < 4; i++) {
                //     cout << endl;
                //     for (int j = 0; j < 4; j++) {
                //         cout << m_inv.mat[i][j] << " ";
                //     }
                // }
            }else if (cmd == "xfr") {
                // xfr rx ry rz
                float rx, ry, rz;
                is >> rx >> ry >> rz;
                Matrix r;
                if (rx != 0) {
                    r = m.rotateMatrixX(Vector(rx,ry,rz));
                    m = m.matrixMult(m,r);
                    m_inv = m_inv.matrixMult(r.rotationInverseX(r), m_inv);
                } else if (ry != 0) {
                    r = m.rotateMatrixY(Vector(rx,ry,rz));
                    m = m.matrixMult(m,r);
                    m_inv = m_inv.matrixMult(r.rotationInverseY(r), m_inv);
                } else if (rz != 0) {
                    r = m.rotateMatrixZ(Vector(rx,ry,rz));
                    m = m.matrixMult(m,r);
                    m_inv = m_inv.matrixMult(r.rotationInverseZ(r), m_inv);
                }
            }else if (cmd == "xfs") {
                // xfs sx sy sz 
                float sx, sy, sz;
                is >> sx >> sy >> sz;
                Matrix s = m.scaleMatrix(Vector(sx,sy,sz));
                m = m.matrixMult(m, s);
                m_inv = m_inv.matrixMult(s.scaleInverse(s), m_inv);
                
            }else if (cmd == "xfz") {
                Matrix identity;
                m.set(identity); 
                m_inv.set(identity);
            }

 
        }

    }

    output_image = "testImage.png";
    width = w;
    height = h;

    infile.close();
}

Scene::Scene(int w, int h, Point eyePos, Point upperLeft, Point upperRight, Point lowerLeft, Point lowerRight, Color ltac) {
	output_image = "testImage.png";
	width = w;
	height = h;
	eye = eyePos;
	ul = upperLeft;
	ur = upperRight;
	ll = lowerLeft;
	lr = lowerRight;

	lta.c = ltac;
}

void Scene::render(Film film, Raytracer raytracer) {
	float l,r,b,t;
	l = ul.x;
	r = lr.x;
	t = ul.y;
	b = lr.y;
	float u,v;

	Color c;
	for (int i = 0; i < width; i++) {
		for (int j=0; j < height; j++) {
			u = l + (r-l)*(i+0.5)/width;
			v = b + (t-b)*(j+0.5)/height;
			Vector direction(u, v, ul.z-eye.z);
			direction.normalize();
			Ray r(eye, direction);

			c = raytracer.trace(r, 1);
			film.set(i,j,c);

		}
	}
}

// void Scene::parseFile(file) {
// 	return null;
// }