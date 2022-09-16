
#include "tis_vector.h"
#include <math.h>

// Unary Operations:

double vector2d_length (vector2d a) {
	double d;
	d = sqrt((a.x * a.x) + (a.y * a.y));
	return d;
}

vector2d vector2d_unit (vector2d a, double p) {
	vector2d v = {0.0, 0.0};
	double len = vector2d_length(a);
	if (!d_equals(len, 0.0, p)) {
		v.x = a.x / len; v.y = a.y / len;
	}
	return v;
}

matrix2d matrix2d_transpose (matrix2d A) {
	matrix2d M;
	M.xx = A.xx; M.xy = A.yx;
	M.yx = A.xy; M.yy = A.yy;
	return M;
}

double matrix2d_determinant (matrix2d A) {
	double d;
	//(A11 * A22) - (A12 * A21)
	d = (A.xx * A.yy) - (A.xy * A.yx);
	return d;
}

matrix2d matrix2d_adjoint (matrix2d A) {
	matrix2d M;
	//matrix(A22, -A12, -A21, A11)
	M.xx = A.yy; M.xy = -A.xy;
	M.yx = -A.yx; M.yy = A.xx;
	return M;
}

matrix2d matrix2d_inverse (matrix2d A, double p) {
	matrix2d M = {0.0, 0.0, 0.0, 0.0};
	//scale(1 / determinate(A), adjoint(A))
	double d = matrix2d_determinant(A);
	if (!d_equals(d, 0.0, p)) {
		M = matrix2d_scale(1.0 / matrix2d_determinant(A), matrix2d_adjoint(A));
	}
	return M;
}

// Scalar, Scalar-Vector, and Scalar-Matrix Operations:

bool d_equals (double a, double b, double p) {
	bool c;
	//a == b, at precision p
	c = (a > b - p) && (a < b + p);
	return c;
}

vector2d vector2d_scale (double r, vector2d a) {
	vector2d v;
	v.x = r * a.x; v.y = r * a.y;
	return v;
}

matrix2d matrix2d_scale (double r, matrix2d A) {
	matrix2d M;
	M.xx = r * A.xx; M.xy = r * A.xy;
	M.yx = r * A.yx; M.yy = r * A.yy;
	return M;
}

// Vector-Vector and Matrix-Vector Operations:

bool vector2d_equals (vector2d a, vector2d b, double p) {
	bool c = false;
	//a == b, at precision p
	c = d_equals(a.x, b.x, p) && d_equals(a.y, b.y, p);
	return c;
}

vector2d vector2d_add (vector2d a, vector2d b) {
	vector2d v;
	v.x = a.x + b.x; v.y = a.y + b.y;
	return v;
}

double vector2d_dot (vector2d a, vector2d b) {
	double d;
	//(a1 * b1) + (a2 * b2)
	d = (a.x * b.x) + (a.y * b.y);
	return d;
}

double vector2d_theta (vector2d a, vector2d b, double p) {
	double d = 0.0;
	//invcos(dot(a, b) / (length(a) * length(b)))
	double len = vector2d_length(a) * vector2d_length(b);
	if (!d_equals(len, 0.0, p)) {
		d = acos(vector2d_dot(a, b) / len);
	}
	return d;
}

double vector2d_cross (vector2d a, vector2d b, double theta) {
	double d = 0.0;
	//length(a) * length(b) * sin(theta)
	d = vector2d_length(a) * vector2d_length(b) * sin(theta);
	return d;
}

vector2d matrixvector2d_dot (matrix2d A, vector2d b) {
	vector2d v = {0.0, 0.0};
	//vector(dot(A1, b), dot(A2, b))
	vector2d A1, A2;
	A1.x = A.xx; A1.y = A.xy;
	A2.x = A.yx; A2.y = A.yy;
	v.x = vector2d_dot(A1, b); v.y = vector2d_dot(A2, b);
	return v;
}

// Matrix-Matrix Operations:

bool matrix2d_equals (matrix2d A, matrix2d B, double p) {
	bool b = false;
	//A == B, at precision p
	b = d_equals(A.xx, B.xx, p) && d_equals(A.xy, B.xy, p) &&
	d_equals(A.yx, B.yx, p) && d_equals(A.yy, B.yy, p);
	return b;
}

matrix2d matrix2d_add (matrix2d A, matrix2d B) {
	matrix2d M = {0.0, 0.0, 0.0, 0.0};
	M.xx = A.xx + B.xx; M.xy = A.xy + B.xy;
	M.yx = A.yx + B.yx; M.yy = A.yy + B.yy;
	return M;
}

matrix2d matrix2d_dot (matrix2d A, matrix2d B) {
	matrix2d M = {0.0, 0.0, 0.0, 0.0};
	//matrix(dot(A1, T1), dot(A1, T2), dot(A2, T1), dot(A2, T2))
	//where T := transpose(B)
	matrix2d T = matrix2d_transpose(B);
	vector2d A1, A2;
	vector2d T1, T2;
	A1.x = A.xx; A1.y = A.xy;
	A2.x = A.yx; A2.y = A.yy;
	T1.x = T.xx; T1.y = T.xy;
	T2.x = T.yx; T2.y = T.yy;
	M.xx = vector2d_dot(A1, T1); M.xy = vector2d_dot(A1, T2);
	M.yx = vector2d_dot(A2, T1); M.yy = vector2d_dot(A2, T2);
	return M;
}

