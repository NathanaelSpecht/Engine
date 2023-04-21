
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngvec.h"

// matrix functions in R2
double ng::sqlen (const Vec2& a) {
	return (a.x*a.x)+(a.y*a.y);
}

double ng::len (const Vec2& a) {
	return std::sqrt((a.x*a.x)+(a.y*a.y));
}

double ng::trace (const Mat2& A) {
	return A.a+A.d;
}

double ng::det (const Mat2& A) {
	return (A.a*A.d)-(A.b*A.c);
}

double ng::det (double a, double b, double c, double d) {
	return (a*d)-(b*c);
}

double ng::dot (const Vec2& a, const Vec2& b) {
	return (a.x*b.x)+(a.y*b.y);
}

Vec2 ng::unit (const Vec2& a) {
	double len = ng::len(a);
	Vec2 c(a.x/len,
	       a.y/len);
	return c;
}

Vec2 ng::project (const Vec3& a) {
	Vec2 c(a.x,
	       a.y);
	return c;
}

Mat2 ng::project (const Mat3& A) {
	Mat2 C(A.a, A.b,
	       A.d, A.e);
	return C;
}

Mat2 ng::transpose (const Mat2& A) {
	Mat2 C(A.a,A.c,
	       A.b,A.d);
	return C;
}

Mat2 ng::adj (const Mat2& A) {
	Mat2 C(A.d,-A.b,
	      -A.c, A.a);
	return C;
}

Mat2 ng::inv (const Mat2& A) {
	return ng::adj(A)*(1.0/ng::det(A));
}

// matrix functions in R3
double ng::sqlen (const Vec3& a) {
	return (a.x*a.x)+(a.y*a.y)+(a.z*a.z);
}

double ng::len (const Vec3& a) {
	return std::sqrt((a.x*a.x)+(a.y*a.y)+(a.z*a.z));
}

double ng::trace (const Mat3& A) {
	return A.a+A.e+A.i;
}

double ng::det (const Mat3& A) {
	return ((A.a*ng::det(A.e,A.f,A.h,A.i))
		   -(A.b*ng::det(A.d,A.f,A.g,A.i)))
		  +(A.c*ng::det(A.d,A.e,A.g,A.h));
}

double ng::dot (const Vec3& a, const Vec3& b) {
	return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

Vec3 ng::unit (const Vec3& a) {
	double len = ng::len(a);
	Vec3 c(a.x/len,
	       a.y/len,
	       a.z/len);
	return c;
}

Vec3 ng::affine (const Vec2& a) {
	Vec3 c(a.x,
	       a.y,
	       1.0);
	return c;
}

Mat3 ng::affine (const Mat2& A, const Vec2& b) {
	Mat3 C(A.a,A.b,b.x,
	       A.c,A.d,b.y,
	       0.0,0.0,1.0);
	return C;
}

Mat3 ng::transpose (const Mat3& A) {
	Mat3 C(A.a,A.d,A.g,
	       A.b,A.e,A.h,
	       A.c,A.f,A.i);
	return C;
}

Mat3 ng::minor (const Mat3& A) {
	// A = (a, b, c,
	//      d, e, f,
	//      g, h, i)
	Mat3 C(ng::det(A.e,A.f,A.h,A.i),ng::det(A.d,A.f,A.g,A.i),ng::det(A.d,A.e,A.g,A.h),
	       ng::det(A.b,A.c,A.h,A.i),ng::det(A.a,A.c,A.g,A.i),ng::det(A.a,A.b,A.g,A.h),
	       ng::det(A.b,A.c,A.e,A.f),ng::det(A.a,A.c,A.d,A.f),ng::det(A.a,A.b,A.d,A.e));
	return C;
}

Mat3 ng::adj (const Mat3& A) {
	Mat3 C = ng::minor(A);
	// transpose of cofactor
	C.set( C.a,-C.d, C.g,
	      -C.b, C.e,-C.h,
	       C.c,-C.f, C.i);
	return C;
}

Mat3 ng::inv (const Mat3& A) {
	return ng::adj(A)*(1.0/ng::det(A));
}

// affine transforms in R2
Mat3 ng::scale (double i, double j) {
	Mat3 C(  i, 0.0, 0.0,
	       0.0,   j, 0.0,
	       0.0, 0.0, 1.0);
	return C;
}

Mat3 ng::scale (double srci, double srcj, double desti, double destj) {
	Mat3 C(desti/srci,        0.0, 0.0,
	              0.0, destj/srcj, 0.0,
	              0.0,        0.0, 1.0);
	return C;
}

Mat3 ng::origin (const Vec2& p) {
	Mat3 C(1.0, 0.0, p.x,
	       0.0, 1.0, p.y,
	       0.0, 0.0, 1.0);
	return C;
}

Mat3 ng::origin (double x, double y) {
	Mat3 C(1.0, 0.0,   x,
	       0.0, 1.0,   y,
	       0.0, 0.0, 1.0);
	return C;
}

Mat3 ng::basis (const Vec2& i, const Vec2& j) {
	Mat3 C(i.x, j.x, 0.0,
	       i.y, j.y, 0.0,
	       0.0, 0.0, 1.0);
	return C;
}

Mat3 ng::basis (double i, double j) {
	Mat3 C(  i, 0.0, 0.0,
	       0.0,   j, 0.0,
	       0.0, 0.0, 1.0);
	return C;
}

Mat3 ng::rotate (double a) {
	double s, c;
	s = std::sin(a);
	c = std::cos(a);
	Mat3 C(  c,  -s, 0.0,
	         s,   c, 0.0,
	       0.0, 0.0, 1.0);
	return C;
}

Mat3 ng::space (const Mat3& origin) {
	return origin;
}

Mat3 ng::space (const Mat3& origin, const Mat3& basis) {
	// space is the transform from relative to absolute.
	// multiply transforms in reverse order to combine them.
	return origin*basis;
}

Mat3 ng::space (const Mat3& origin, const Mat3& basis, const Mat3& rotate) {
	return (origin*basis)*rotate;
}

Mat3 ng::space (double x, double y) {
	return ng::origin(x, y);
}

Mat3 ng::space (double x, double y, double i, double j) {
	return ng::origin(x, y)*ng::basis(i, j);
}

Mat3 ng::space (double x, double y, double i, double j, double a) {
	return (ng::origin(x, y)*ng::basis(i, j))*ng::rotate(a);
}

// vector in R2
ng::Vec2::Vec2 () :
	x(0.0),
	y(0.0)
{}

ng::Vec2::Vec2 (double x, double y) :
	x(x),
	y(y)
{}

ng::Vec2::Vec2 (const Vec& a) :
	x(a.x),
	y(a.y)
{}

void ng::Vec2::set (double x, double y) {
	this->x = x;
	this->y = y;
}

Vec2 ng::Vec2::operator+ (double x) const {
	Vec2 c(this->x+x,
	       this->y+x);
	return c;
}

Vec2 ng::Vec2::operator+ (const Vec2& b) const {
	Vec2 c(this->x+b.x,
	       this->y+b.y);
	return c;
}

Vec2 ng::Vec2::operator* (double x) const {
	Vec2 c(this->x*x,
	       this->x*x);
	return c;
}

double ng::Vec2::operator* (const Vec2& b) const {
	return ng::dot(*this,b);
}

// matrix in R2x2
ng::Mat2::Mat2 () :
	a(1.0), b(0.0),
	c(0.0), d(1.0)
{}

ng::Mat2::Mat2 (double a, double b, double c, double d) :
	a(a), b(b),
	c(c), d(d)
{}

ng::Mat2::Mat2 (const Mat2& A) :
	a(A.a), b(A.b),
	c(A.c), d(A.d)
{}

void ng::Mat2::set (double a, double b, double c, double d) {
	this->a = a; this->b = b;
	this->c = c; this->d = d;
}

void ng::Mat2::set_cols (const Vec2& a, const Vec2& b) {
	this->a = a.x; this->b = b.x;
	this->c = a.y; this->d = b.y;
}

void ng::Mat2::set_rows (const Vec2& a, const Vec2& b) {
	this->a = a.x; this->b = a.y;
	this->c = b.x; this->d = b.y;
}

Vec2 ng::Mat2::col1 () const {
	Vec2 a(this->a,
	       this->c);
	return a;
}

Vec2 ng::Mat2::col2 () const {
	Vec2 b(this->b,
	       this->d);
	return b;
}

Vec2 ng::Mat2::row1 () const {
	Vec2 a(this->a,this->b);
	return a;
}

Vec2 ng::Mat2::row2 () const {
	Vec2 b(this->c,this->d);
	return b;
}

Mat2 ng::Mat2::operator+ (double x) const {
	Mat2 C(this->a+x,this->b+x,
	       this->c+x,this->d+x);
	return C;
}

Mat2 ng::Mat2::operator+ (const Mat2& B) const {
	Mat2 C(this->a+B.a,this->b+B.b,
	       this->c+B.c,this->d+B.d);
	return C;
}

Mat2 ng::Mat2::operator* (double x) const {
	Mat2 C(this->a*x,this->b*x,
	       this->c*x,this->d*x);
	return C;
}

Vec2 ng::Mat2::operator* (const Vec2& b) const {
	Vec2 c((this->a*b.x)+(this->b*b.y),
	       (this->c*b.x)+(this->d*b.y));
	return c;
}

Mat2 ng::Mat2::operator* (const Mat2& B) const {
	Vec2 a1(this->row1());
	Vec2 a2(this->row2());
	Vec2 b1(B.col1()); Vec2 b2(B.col2());
	Mat2 C(a1*b1,a1*b2,
	       a2*b1,a2*b2);
	return C;
}

// vector in R3, or augmented vector in R2
ng::Vec3::Vec3 () :
	x(0.0),
	y(0.0),
	z(0.0)
{}

ng::Vec3::Vec3 (double x, double y, double z) :
	x(x),
	y(y),
	z(z)
{}

ng::Vec3::Vec3 (const Vec3& a) :
	x(a.x),
	y(a.y),
	z(a.z)
{}

void ng::Vec3::set (double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 ng::Vec3::operator+ (double x) const {
	Vec3 c(this->x+x,
	       this->y+x,
	       this->z+x);
	return c;
}

Vec3 ng::Vec3::operator+ (const Vec3& b) const {
	Vec3 c(this->x+b.x,
	       this->y+b.y,
	       this->z+b.z);
	return c;
}

Vec3 ng::Vec3::operator* (double x) const {
	Vec3 c(this->x*x,
	       this->y*x,
	       this->z*x);
	return c;
}

double ng::Vec3::operator* (const Vec3& b) const {
	return ng::dot(*this, b);
}

// matrix in R3x3, or affine transformation in R2
ng::Mat3::Mat3 () :
	a(1.0), b(0.0), c(0.0),
	d(0.0), e(1.0), f(0.0),
	g(0.0), h(0.0), i(1.0)
{}

ng::Mat3::Mat3 (double a, double b, double c,
double d, double e, double f,
double g, double h, double i) :
	a(a), b(b), c(c),
	d(d), e(e), f(f),
	g(g), h(h), i(i)
{}

ng::Mat3::Mat3 (const Mat3& A) :
	a(A.a), b(A.b), c(A.c),
	d(A.d), e(A.e), f(A.f),
	g(A.g), h(A.h), i(A.i)
{}

void ng::Mat3::set (double a, double b, double c,
double d, double e, double f,
double g, double h, double i) {
	this->a = a; this->b = b; this->c = c;
	this->d = d; this->e = e; this->f = f;
	this->g = g; this->h = h; this->i = i;
}

void ng::Mat3::set_cols (const Vec3& a, const Vec3& b, const Vec3& c) {
	this->a = a.x; this->b = b.x; this->c = c.x;
	this->d = a.y; this->e = b.y; this->f = c.y;
	this->g = a.z; this->h = b.z; this->i = c.z;
}

void ng::Mat3::set_rows (const Vec3& a, const Vec3& b, const Vec3& c) {
	this->a = a.x; this->b = a.y; this->c = a.z;
	this->d = b.x; this->e = b.y; this->f = b.z;
	this->g = c.x; this->h = c.y; this->i = c.z;
}

Vec3 ng::Mat3::col1 () const {
	Vec3 a(this->a,
	       this->d,
	       this->g);
	return c;
}

Vec3 ng::Mat3::col2 () const {
	Vec3 b(this->b,
	       this->e,
	       this->h);
	return c;
}

Vec3 ng::Mat3::col3 () const {
	Vec3 c(this->c,
	       this->f,
	       this->i);
	return c;
}

Vec3 ng::Mat3::row1 () const {
	Vec3 a(this->a, this->b, this->c);
	return a;
}

Vec3 ng::Mat3::row2 () const {
	Vec3 b(this->d, this->e, this->f);
	return b;
}

Vec3 ng::Mat3::row3 () const {
	Vec3 c(this->g, this->h, this->i);
	return c;
}

Mat3 ng::Mat3::operator+ (double x) const {
	Mat3 C(this->a+x, this->b+x, this->c+x,
	       this->d+x, this->e+x, this->f+x,
	       this->g+x, this->h+x, this->i+x);
	return C;
}

Mat3 ng::Mat3::operator+ (const Mat3& B) const {
	Mat3 C(this->a+B.a, this->b+B.b, this->c+B.c,
	       this->d+B.d, this->e+B.e, this->f+B.f,
	       this->g+B.g, this->h+B.h, this->i+B.i);
	return C;
}

Mat3 ng::Mat3::operator* (double x) const {
	Mat3 C(this->a*x, this->b*x, this->c*x,
	       this->d*x, this->e*x, this->f*x,
	       this->g*x, this->h*x, this->i*x);
	return C;
}

Vec3 ng::Mat3::operator* (const Vec3& b) const {
	Vec3 c(this->row1()*b,
	       this->row2()*b,
	       this->row3()*b);
	return c;
}

Mat3 ng::Mat3::operator* (const Mat3& B) const {
	Vec3 a1(this->row1());
	Vec3 a2(this->row2());
	Vec3 a3(this->row3());
	Vec3 b1(B.col1()); Vec3 b2(B.col2()); Vec3 b3(B.col3());
	Mat3 C(a1*b1, a1*b2, a1*b3,
	       a2*b1, a2*b2, a2*b3,
	       a3*b1, a3*b2, a3*b3);
	return C;
}


