#include "classes.h"

// Constructors for the class
Point::Point() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Point::Point(float input_x, float input_y, float input_z) {
	x = input_x;
	y = input_y;
	z = input_z;
}

// Functions for the class 
Vector Point::add(Point one, Point two) {
	Vector answer;
    answer.x = one.x + two.x;
    answer.y = one.y + two.y;
    answer.z = one.z + two.z;
    return answer;
}

Vector Point::subtract(Point one, Point two) {
	Vector answer;
    answer.x = one.x - two.x;
    answer.y = one.y - two.y;
    answer.z = one.z - two.z;
    return answer;
}

// int main() {
//     return 0;
// }