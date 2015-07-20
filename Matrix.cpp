#include "classes.h"
#include <math.h>

//row by column [row][column] 
// Generate the identic matrix 
Matrix::Matrix() { 
	for (int r = 0; r < 4; ++r){ 
		for (int c = 0; c < 4 ; ++c){ 
			if (r == c){ 
				mat[r][c] = 1; 
			} else { 
				mat[r][c] = 0;
			}
		}
	}
} 

// Matrix::Matrix(float a[4][4]) {
// 	mat = a;
// }

 // Rotation matrix 
 // suppose rotate along X-axis 
Matrix Matrix::rotateMatrixX(Vector vec){ 
	float angle; 
	// angle = acos(vec.dotProduct(Vector(0,0,0), vec) / vec.length(vec)); 
	angle = vec.length();
	Matrix answer;
	answer.mat[1][1] = cos(angle);
	answer.mat[1][2] = -sin(angle); 
	answer.mat[2][1] = sin(angle); 
	answer.mat[2][2] = cos(angle); 
	return answer; 
} 

 // Rotation matrix 
 // suppose rotate along Y-axis 
 Matrix Matrix::rotateMatrixY(Vector vec){ 
	 float angle; 
	 // angle = acos(vec.dotProduct(Vector(0,0,0), vec) / vec.length(vec)); 
	 angle = vec.length();
	 Matrix answer;
	 answer.mat[0][0] = cos(angle); 
	 answer.mat[0][2] = sin(angle); 
	 answer.mat[2][0] = -sin(angle); 
	 answer.mat[2][2] = cos(angle); 
	 return answer; 
 } 
 // Rotation matrix 
 // suppose rotate along X-axis 
Matrix Matrix::rotateMatrixZ(Vector vec){ 
	float angle; 
	// angle = acos(vec.dotProduct(Vector(0,0,0), vec) / vec.length(vec)); 
	angle = vec.length();
	Matrix answer;
	answer.mat[0][0] = cos(angle); 
	answer.mat[0][1] = -sin(angle); 
	answer.mat[1][0] = sin(angle); 
	answer.mat[1][1] = cos(angle); 
	return answer; 
} 
 // Translation matrix 
 // move the vector to center(0,0,0) 
Matrix Matrix::translationMatrix(Vector center){ 
	Matrix answer; 
	answer.mat[0][3] = center.x; 
	answer.mat[1][3] = center.y; 
	answer.mat[2][3] = center.z; 
	// answer.mat[3][3] = 1;
	return answer;
 } 
 //Scaling matrix 
 Matrix Matrix::scaleMatrix(Vector scale){
 	Matrix answer;
 	answer.mat[0][0] = scale.x;
 	answer.mat[1][1] = scale.y;
 	answer.mat[2][2] = scale.z;
 	answer.mat[3][3] = 1;
 	return answer;
 } 

Matrix Matrix::matrixMult(Matrix mat1, Matrix mat2){ 
 	Matrix answer; 
 	for (int i = 0; i < 4; i++){ 
 		for (int j = 0; j < 4; ++j){ 
 			answer.mat[i][j] = 0; 
 			for (int k = 0; k < 4 ; ++k){ 
 				answer.mat[i][j] = answer.mat[i][j] + mat1.mat[i][k] * mat2.mat[k][j]; 
 			} 
 		} 
 	} 
 	return answer;
}

Point Matrix::pointMult(Matrix m, Point p) {
	Point answer;
	answer.x = m.mat[0][0]*p.x + m.mat[0][1]*p.y + m.mat[0][2]*p.z + m.mat[0][3]*1;
	answer.y = m.mat[1][0]*p.x + m.mat[1][1]*p.y + m.mat[1][2]*p.z + m.mat[1][3]*1;
	answer.z = m.mat[2][0]*p.x + m.mat[2][1]*p.y + m.mat[2][2]*p.z + m.mat[2][3]*1;
	return answer;
}

Vector Matrix::vectorMult(Matrix m, Vector v) {
	Vector answer;
	answer.x = m.mat[0][0]*v.x + m.mat[0][1]*v.y + m.mat[0][2]*v.z;
	answer.y = m.mat[1][0]*v.x + m.mat[1][1]*v.y + m.mat[1][2]*v.z;
	answer.z = m.mat[2][0]*v.x + m.mat[2][1]*v.y + m.mat[2][2]*v.z;
	return answer;
}

void Matrix::set(Matrix m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = m.mat[i][j];
		}
	}
}

Matrix Matrix::scaleInverse(Matrix m) {
	Matrix answer;
	answer.mat[0][0] = 1.0 / m.mat[0][0];
	answer.mat[1][1] = 1.0 / m.mat[1][1];
	answer.mat[2][2] = 1.0 / m.mat[2][2];
	answer.mat[3][3] = 1.0;
	return answer;
}

Matrix Matrix::translationInverse(Matrix m) {
	Matrix answer;
	answer.mat[0][3] = -m.mat[0][3];
	answer.mat[1][3] = -m.mat[1][3];
	answer.mat[2][3] = -m.mat[2][3];
	return answer;
}

Matrix Matrix::rotationInverseX(Matrix m) {
	Matrix answer;
	answer.mat[1][1] = m.mat[1][1];
	answer.mat[1][2] = -m.mat[1][2]; 
	answer.mat[2][1] = -m.mat[2][1]; 
	answer.mat[2][2] = m.mat[2][2]; 
	return answer;
}

Matrix Matrix::rotationInverseY(Matrix m) {
	Matrix answer;
	// answer.mat[0][0] = cos(angle); 
	answer.mat[0][2] = -m.mat[0][2]; 
	answer.mat[2][0] = -m.mat[2][0]; 
	// answer.mat[2][2] = cos(angle); 
	return answer; 
}


Matrix Matrix::rotationInverseZ(Matrix m) {
	Matrix answer;
	// answer.mat[0][0] = cos(angle); 
	answer.mat[0][1] = -m.mat[0][1]; 
	answer.mat[1][0] = -m.mat[1][0]; 
	// answer.mat[1][1] = cos(angle); 
	return answer; 
} 

Matrix Matrix::transpose(Matrix m) {
	Matrix answer;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer.mat[i][j] = m.mat[j][i];
		}
	}
	return answer;
}
// class Transformation : public Matrix{ public: Matrix m, invm; Transformation(Vector vec){ m = m.matrixMult( m.rotateMatrixY(vec), m.translationMatrix(vec) ) ; invm = inverse(m); } Matrix inverse(Matrix mat){ Matrix answer; for (r = 0; r < 4; ++r){ for (c = 0; c < 4 ; ++c){ answer[r][c] = mat[c][r]; } } return Matrix(answer); } };

