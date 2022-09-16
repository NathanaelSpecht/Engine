
#include "tis_vector.h"

// Unary Operations:

double vector2d_length (vector2d a) {
	double d = 0.0;
	return d;
}

vector2d vector2d_unit (vector2d a) {
	vector2d v = {0.0, 0.0};
	return v;
}

matrix2d matrix2d_transpose (matrix2d A) {
	matrix2d m = {0.0, 0.0, 0.0, 0.0};
	return m;
}

double matrix2d_determinant (matrix2d A) {
	double d = 0.0;
	return d;
}

matrix2d matrix2d_adjoint (matrix2d A) {
	matrix2d m = {0.0, 0.0, 0.0, 0.0};
	return m;
}

matrix2d matrix2d_inverse (matrix2d A) {
	matrix2d m = {0.0, 0.0, 0.0, 0.0};
	return m;
}

// Scalar-Vector and Scalar-Matrix Operations:

vector2d vector2d_scale (double r, vector2d a) {
	vector2d v = {0.0, 0.0};
	return v;
}

matrix2d matrix2d_scale (double r, matrix2d A) {
	matrix2d m = {0.0, 0.0, 0.0, 0.0};
	return m;
}

// Vector-Vector and Matrix-Vector Operations:

bool vector2d_equals (vector2d a, vector2d b) {
	double d = 0.0;
	return d;
}

vector2d vector2d_add (vector2d a, vector2d b) {
	vector2d v = {0.0, 0.0};
	return v;
}

double vector2d_dot (vector2d a, vector2d b) {
	double d = 0.0;
	return d;
}

double vector2d_theta (vector2d a, vector2d b) {
	double d = 0.0;
	return d;
}

double vector2d_cross (vector2d a, vector2d b) {
	double d = 0.0;
	return d;
}

vector2d matrixvector2d_dot (matrix2d A, vector2d b) {
	vector2d v = {0.0, 0.0};
	return v;
}

// Matrix-Matrix Operations:

bool matrix2d_equals (matrix2d A, matrix2d B) {
	return false;
}

matrix2d matrix2d_add (matrix2d A, matrix2d B) {
	matrix2d m = {0.0, 0.0, 0.0, 0.0};
	return m;
}

matrix2d matrix2d_dot (matrix2d A, matrix2d B) {
	matrix2d m = {0.0, 0.0, 0.0, 0.0};
	return m;
}

