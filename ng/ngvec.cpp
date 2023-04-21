
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngvec.h"

// matrix functions in R2
double ng::sqlen (const Vec2& a) {
	return (a.x*a.x)+(a.y*a.y);
}

double ng::len (const Vec2& a) {
	return std::hypot(a.x, a.y);
}

double ng::trace (const Mat2& A) {
	return A.a+A.d;
}

double ng::det (const Mat2& A) {
	return (A.a*A.d)-(A.b*A.c);
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
	Vec2 c(a.x, a.y);
	return c;
}

Mat2 ng::project (const Mat3& A) {
	Mat2 C(A.a, A.b, A.d, A.e);
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

// TODO
// matrix functions in R3
double ng::sqlen (const Vec3& a) {
	
}

double ng::len (const Vec3& a) {
	
}

double ng::trace (const Mat3& A) {
	
}

double ng::det (const Mat3& A) {
	
}

double ng::dot (const Vec3& a, const Vec3& b) {
	
}

Vec3 ng::unit (const Vec3& a) {
	
}

Vec3 ng::augment (const Vec2& a) {
	
}

Mat3 ng::augment (const Mat2& A, const Vec2& b) {
	
}

Mat3 ng::transpose (const Mat3& A) {
	
}

Mat3 ng::adj (const Mat3& A) {
	
}

Mat3 ng::inv (const Mat3& A) {
	
}

// TODO
// affine transforms in R2
Mat3 ng::translate (const Vec2& p) {
	
}

Mat3 ng::basis (const Vec2& i, const Vec2& j) {
	
}

Mat3 ng::rotate (double a) {
	
}

Mat3 ng::space (const Mat3& translate) {
	
}

Mat3 ng::space (const Mat3& translate, const Mat3& basis) {
	
}

Mat3 ng::space (const Mat3& translate, const Mat3& basis, const Mat3& rotate) {
	
}

Mat3 ng::portal (const Mat3& src_space, const Mat3& dest_space) {
	
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

double ng::Vec2::dot (const Vec2& b) const {
	return ng::dot(*this,b);
}

double ng::Vec2::sqlen () const {
	return ng::sqlen(*this);
}

double ng::Vec2::len () const {
	return ng::len(*this);
}

Vec2 ng::Vec2::unit () const {
	return ng::unit(*this);
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

double ng::Mat2::trace () const {
	return ng::trace(*this);
}

double ng::Mat2::det () const {
	return ng::det(*this);
}

Mat2 ng::Mat2::transpose () const {
	return ng::transpose(*this);
}

Mat2 ng::Mat2::adj () const {
	return ng::adj(*this);
}

Mat2 ng::Mat2::inv () const {
	return ng::inv(*this);
}

// TODO
// vector in R3, or augmented vector in R2
ng::Vec3::Vec3 () :
	
{}

ng::Vec3::Vec3 (double x, double y, double z) :
	
{}

ng::Vec3::Vec3 (const Vec3& a) :
	
{}

void ng::Vec3::set (double x, double y) {
	
}

Vec3 ng::Vec3::operator+ (double x) const {
	
}

Vec3 ng::Vec3::operator+ (const Vec3& b) const {
	
}

Vec3 ng::Vec3::operator* (double x) const {
	
}

double ng::Vec3::operator* (const Vec3& b) const {
	
}

double ng::Vec3::dot (const Vec3& b) const {
	
}

double ng::Vec3::sqlen () const {
	
}

double ng::Vec3::len () const {
	
}

Vec3 ng::Vec3::unit () const {
	
}

// TODO
// matrix in R3x3, or affine transformation in R2
ng::Mat3::Mat3 () :
	
{}

ng::Mat3::Mat3 (const Vec3& a, const Vec3& b, const Vec3& c) :
	
{}

ng::Mat3::Mat3 (const Mat3& A) :
	
{}

void ng::Mat3::set (const Vec3& a, const Vec3& b, const Vec3& c) {
	
}

void ng::Mat3::set_cols (const Vec3& a, const Vec3& b, const Vec3& c) {
	
}

void ng::Mat3::set_rows (const Vec3& a, const Vec3& b, const Vec3& c) {
	
}

Vec3 ng::Mat3::col1 () const {
	
}

Vec3 ng::Mat3::col2 () const {
	
}

Vec3 ng::Mat3::col3 () const {
	
}

Vec3 ng::Mat3::row1 () const {
	
}

Vec3 ng::Mat3::row2 () const {
	
}

Vec3 ng::Mat3::row3 () const {
	
}

Mat3 ng::Mat3::operator+ (double x) const {
	
}

Mat3 ng::Mat3::operator+ (const Mat3& B) const {
	
}

Mat3 ng::Mat3::operator* (double x) const {
	
}

Vec3 ng::Mat3::operator* (const Vec3& b) const {
	
}

Mat3 ng::Mat3::operator* (const Mat3& B) const {
	
}

double ng::Mat3::trace () const {
	
}

double ng::Mat3::det () const {
	
}

Mat3 ng::Mat3::transpose () const {
	
}

Mat3 ng::Mat3::adj () const {
	
}

Mat3 ng::Mat3::inv () const {
	
}


