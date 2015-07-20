#include "classes.h"
#include <math.h>

// Constructors for the class
Vector::Vector(){
    x = 0.0, y = 0.0, z = 0.0;
}

float Vector::length() {
    return pow( pow(x,2) + pow(y,2) + pow(z,2) , 0.5);
}

Vector::Vector(float input_x, float input_y, float input_z){
    x = input_x;
    y = input_y;
    z = input_z;
}
//Functions for the class
Vector Vector::add(Vector one, Vector two){
    Vector answer;
    answer.x = one.x + two.x;
    answer.y = one.y + two.y;
    answer.z = one.z + two.z;
    return answer;
}
Vector Vector::subtract(Vector one, Vector two){
    Vector answer;
    answer.x = one.x - two.x;
    answer.y = one.y - two.y;
    answer.z = one.z - two.z;
    return answer;
}
Vector Vector::scalarMult(float num, Vector vec){
    Vector answer;
    answer.x = num * vec.x;
    answer.y = num * vec.y;
    answer.z = num * vec.z;
    return answer;
}
Vector Vector::scalarDiv(float num, Vector vec){
    Vector answer;
    if (num != 0){
        answer.x = vec.x/num;
        answer.y = vec.y/num;
        answer.z = vec.z/num;
        return answer;
    }else{
        answer.x = 0;
        answer.y = 0;
        answer.z = 0;
    }
}
Vector Vector::normal(Vector vec){
    Vector answer;
    float divide;
    divide = pow(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2), 0.5);
    answer.x = vec.x / divide;
    answer.y = vec.y / divide;
    answer.z = vec.z / divide;
    return answer;
}

void Vector::normalize() {
    float divide = pow(pow(x,2) + pow(y,2) + pow(z,2), 0.5);
    x = x / divide;
    y = y / divide;
    z = z / divide;
}

float Vector::dotProduct(Vector one, Vector two){
    float answer;
    answer = one.x * two.x + one.y * two.y + one.z * two.z;
    return answer;
}

Vector Vector::crossProduct(Vector one, Vector two){
    Vector answer;
    answer.x = one.y * two.z - two.y * one.z;
    answer.y = one.x * two.z - two.x * one.z;
    answer.z = one.x * two.y - two.x * one.y;
    return answer;
}

Vector Vector::makeVector(Point one, Point two){
    Vector answer;
    answer.x = one.x - two.x;
    answer.y = one.y - two.y;
    answer.z = one.z - two.z;
    return answer;
}

// int main() {
//     return 0;
// }