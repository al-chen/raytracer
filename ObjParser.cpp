#include "classes.h"

#include "fstream"
#include "string"
#include "sstream"

using namespace std;

ObjParser::ObjParser(){

}


ObjParser::ObjParser(const char * file){
    
    std::ifstream infile(file);

    // std::string line;


    while (infile){
        string line;
        while (getline(infile, line)){

            istringstream is(line);
            string cmd;
            is >> cmd;

            float x, y, z;
            int i, j, k;

            if (cmd == "v") {
                is >> x >> y >> z;
                Point newV(x,y,z);
                v.push_back(newV);
                // cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz 
                
            }else if ( cmd == "f") {
                is >> i >> j >> k;
                //find vi, vj, vk to form the triangle
                // Point x, y, z;
                // x = Point(v[i-1]->x, v[i-1]->y, v[i-1]->z) ;
                // y = Point(v[j-1]->x, v[j-1]->y, v[j-1]->z) ;
                // z = Point(v[k-1]->x, v[k-1]->y, v[k-1]->z) ;
                // Triangle* tri = new Triangle(x,y,z);
                // triangles.push_back(tri);
                triangles.push_back(new Triangle(v[i-1], v[j-1], v[k-1]));

            }

 
        }

    }
    infile.close();

}