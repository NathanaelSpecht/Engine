
#ifndef TIS_VECTOR_H
#define TIS_VECTOR_H

#include <stdbool.h>

typedef struct vector2d {
	double x;
	double y;
} vector2d;

typedef struct matrix2d {
	double xx; double xy;
	double yx; double yy;
} matrix2d;

// Unary Operations:
double vector2d_length (vector2d a);
vector2d vector2d_unit (vector2d a, double p);
matrix2d matrix2d_transpose (matrix2d A);
double matrix2d_determinant (matrix2d A);
matrix2d matrix2d_adjoint (matrix2d A);
matrix2d matrix2d_inverse (matrix2d A, double p);

// Scalar, Scalar-Vector, and Scalar-Matrix Operations:
bool d_equals (double a, double b, double p);
vector2d vector2d_scale (double r, vector2d a);
matrix2d matrix2d_scale (double r, matrix2d A);

// Vector-Vector and Matrix-Vector Operations:
bool vector2d_equals (vector2d a, vector2d b, double p);
vector2d vector2d_add (vector2d a, vector2d b);
double vector2d_dot (vector2d a, vector2d b);
double vector2d_theta (vector2d a, vector2d b, double p);
double vector2d_cross (vector2d a, vector2d b, double theta);
vector2d matrixvector2d_dot (matrix2d A, vector2d b);

// Matrix-Matrix Operations:
bool matrix2d_equals (matrix2d A, matrix2d B, double p);
matrix2d matrix2d_add (matrix2d A, matrix2d B);
matrix2d matrix2d_dot (matrix2d A, matrix2d B);

#endif

