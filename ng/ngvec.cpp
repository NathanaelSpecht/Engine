
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngvec.h"

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


