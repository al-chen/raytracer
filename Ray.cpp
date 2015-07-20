#include "classes.h"    
// ray(t) = pos + t * dir, where t_min <= t <= t_max

Ray::Ray(Point pt, Vector dir) {
    position = pt;
    direction = dir;
    t_min = 0;
    t_max = 1;
}

Ray::Ray(Point input_start, Vector input_direction, float input_t_max, float input_t_min) {
    position = input_start;
    direction = input_direction;
    t_min = input_t_min;
    t_max = input_t_max;
}

// void Ray::setRay(Point input_start, Vector input_direction, float input_t_max, float input_t_min) {
//     position = input_start;
//     direction = input_direction;
//     t_min = input_t_min;
//     t_max = input_t_max;
// }

// Ray Ray::getRay(float t) {
//     if (t < t_max && t > t_min) {
//         Vector start = Vector(position.x, position.y, position.z); 
//         return add(start , scalarMult(t, direction); 
//     }else{

//     }
// }
