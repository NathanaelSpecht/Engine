
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngmath.h"

// given x (-int32, int32) and m [1, int16), produces [0, m).
// unlike std::mod(x, m), does NOT mirror positive and negative x.
// adds a multiple of m (say, p) to x, such that x+p >= 0 for any x.
// equivalent to std::mod(x+p, m).
int ng::wrap (int x, int m) {
	// cast to int64 to avoid overflow
	int64_t x1, m1, y;
	int result;
	x1 = static_cast<int64_t>(x);
	m1 = static_cast<int64_t>(m);
	y = (x1 + (INT64_C(2147483648) * m1)) % m1;
	result = static_cast<int>(y);
	return result;
}

double ng::wrap (double x, double m) {
	return std::fmod(x + (2147483648.0 * m), m);
}

// Bhaskara I's sine approximation
// given degrees x [0, 180], produces sin(x) [0, 1].
double ng::bhaskara (double x) {
	// max error of 0.165%. error -> 0 for x -> 0, 30, 90, 150, 180.
	double p = x * (180.0 - x);
	return ((4.0 * p) / (40500.0 - p));
}

// Quick sine approximation
// given degrees x [0, 360), produces sin(x) [-1, 1].
double ng::qsin (double x) {
	if (x <= 180.0) {
		return ng::bhaskara(x);
	} else {
		return -ng::bhaskara(x - 180.0);
	}
}

// Quick cosine approximation
// given degrees x [0, 360), produces cos(x) [-1, 1].
double ng::qcos (double x) {
	if (x <= 90.0) {
		return ng::bhaskara(x + 90.0);
	} else if (x < 270.0) {
		return -ng::bhaskara(x - 90.0);
	} else {
		return ng::bhaskara(x - 270.0);
	}
}

// Given x in [x_min, x_max], produce y in [0, 1].
float ng::normalize (float x, float x_min, float x_max) {
	float y;
	y = (x - x_min) / (x_max - x_min);
	return y;
}

// Given x in [0, 1], produce y in [y_min, y_max].
float ng::denormalize (float x, float y_min, float y_max) {
	float y;
	y = (x * (y_max - y_min)) + y_min;
	return y;
}

// Force x into the range [x_min, x_max].
float ng::clamp (float x, float x_min, float x_max) {
	float y;
	if (x < x_min) {
		y = x_min;
	} else if (x > x_max) {
		y = x_max;
	} else {
		y = x;
	}
	return y;
}

// Given amplitude [0, 1], produce decibels [-inf, 0].
float ng::amp_to_dB (float amp) {
	float dB;
	dB = 20.0f * std::log10(amp);
	return dB;
}

// Given decibels [-inf, 0], produce amplitude [0, 1].
float ng::dB_to_amp (float dB) {
	float amp;
	amp = std::pow(10.0f, dB/20.0f);
	return amp;
}

// Convert decibels to amplitude, mix, then convert back to decibels.
float ng::mix_dB (float dB1, float dB2) {
	float y;
	y = ng::amp_to_dB(ng::dB_to_amp(dB1) + ng::dB_to_amp(dB2));
	return y;
}

// Given linear volume x [0, 1], produce exponential volume y [0, 1].
// Multiply decibels by y to apply volume x.
float ng::dB_volume (float x) {
	float y;
	y = ng::normalize(std::exp(x) - 1.0f, 0.0f, 2.719f - 1.0f);
	return y;
}

float ng::dB_silence () {
	return -144.0f;
}

double ng::radians (double degrees) {
	return degrees*0.0174532925199; // radians = degrees*pi/180
}

double ng::degrees (double radians) {
	return radians*57.295779513082; // degrees = radians*180/pi
}

/*
double ng::units (double columns, double width) {
	return width/columns;
}

double ng::columns (double units, double width) {
	return width/units;
}


double ng::determinant (double a, double b, double c, double d) {
	return (a * d) - (b * c);
}


double ng::scale (double src_w, double dest_w) {
	return dest_w/src_w;
}
*/

ng::Box2::Box2 () :
	x(0.0), y(0.0), rx(0.0), ry(0.0)
{}

ng::Box2::Box2 (double x, double y, double rx, double ry) :
	x(x), y(y), rx(rx), ry(ry)
{}

ng::Box2::Box2 (const Box2& box) :
	x(box.x), y(box.y), rx(box.rx), ry(box.ry)
{}

ng::Box2::Box2 (const Rect2& rect) {
	this->x = rect.x + (rect.w*0.5);
	this->y = rect.y + (rect.h*0.5);
	this->rx = rect.w*0.5;
	this->ry = rect.h*0.5;
}

void ng::Box2::set (double x, double y, double rx, double ry) {
	this->x = x;
	this->y = y;
	this->rx = rx;
	this->ry = ry;
}

void ng::Box2::set_p (const Vec2& p) {
	this->x = p.x;
	this->y = p.y;
}

void ng::Box2::set_dim (const Vec2& dim) {
	this->rx = dim.x;
	this->ry = dim.y;
}

Vec2 ng::Box2::p () const {
	Vec2 p(this->x, this->y);
	return p;
}

Vec2 ng::Box2::dim () const {
	Vec2 dim(this->rx, this->ry);
	return dim;
}

Vec2 ng::Box2::i () const {
	Vec2 i(this->rx, 0.0);
	return i;
}

Vec2 ng::Box2::j () const {
	Vec2 j(0.0, this->ry);
	return j;
}

Box2& ng::Box2::operator= (const Rect2& rect) {
	this->x = rect.x + (rect.w*0.5);
	this->y = rect.y + (rect.h*0.5);
	this->rx = rect.w*0.5;
	this->ry = rect.h*0.5;
	return *this;
}

bool ng::Box2::contains (const Vec2& p) const {
	return !(p.x < this->x - this->rx || p.x >= this->x + this->rx ||
		p.y < this->y - this->ry || p.y >= this->y + this->ry);
}

ng::Rect2::Rect2 () :
	x(0.0), y(0.0), w(0.0), h(0.0)
{}

ng::Rect2::Rect2 (double x, double y, double w, double h) :
	x(x), y(y), w(w), h(h)
{}

ng::Rect2::Rect2 (const Rect2& rect) :
	x(rect.x), y(rect.y), w(rect.w), h(rect.h)
{}

ng::Rect2::Rect2 (const Box2& box) {
	this->x = box.x - box.rx;
	this->y = box.y - box.ry;
	this->w = box.rx*2.0;
	this->h = box.ry*2.0;
}

void ng::Rect2::set (double x, double y, double w, double h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void ng::Rect2::set_p (const Vec2& p) {
	this->x = p.x;
	this->y = p.y;
}

void ng::Rect2::set_dim (const Vec2& dim) {
	this->w = dim.x;
	this->h = dim.y;
}

Vec2 ng::Rect2::p () const {
	Vec2 p(this->x, this->y);
	return p;
}

Vec2 ng::Rect2::dim () const {
	Vec2 dim(this->w, this->h);
	return dim;
}

Vec2 ng::Rect2::i () const {
	Vec2 i(this->w, 0.0);
	return i;
}

Vec2 ng::Rect2::j () const {
	Vec2 j(0.0, this->h);
	return j;
}

Rect2& ng::Rect2::operator= (const Box2& box) {
	this->x = box.x - box.rx;
	this->y = box.y - box.ry;
	this->w = box.rx*2.0;
	this->h = box.ry*2.0;
	return *this;
}

bool ng::Rect2::contains (const Vec2& p) const {
	return !(p.x < this->x || p.x >= this->x + this->w ||
		p.y < this->y || p.y >= this->y + this->h);
}

/*
ng::Line2::Line2 () {
	this->p.set(0.0, 0.0);
	this->v.set(0.0, 0.0);
}

ng::Line2::Line2 (double px, double py, double vx, double vy) {
	this->p.set(px, py);
	this->v.set(vx, vy);
}

ng::Line2::Line2 (const Vec2* p, const Vec2* v) {
	this->p = *p;
	this->v = *v;
}

ng::Line2::Line2 (const Line2* line) {
	this->p = line->p;
	this->v = line->v;
}

ng::Line2::~Line2 () {}
	
void ng::Line2::set (double px, double py, double vx, double vy) {
	this->p.set(px, py);
	this->v.set(vx, vy);
}

void ng::Line2::set (const Vec2* p, const Vec2* v) {
	this->p = *p;
	this->v = *v;
}

// If this intersects line, return true and set i to intersection point.
// Else return false.
bool ng::Line2::intersect (const Line2* line, Vec2* const i) const {
	// TODO
	return false;
}

ng::Rect2::Rect2 () {
	this->p.set(0.0, 0.0);
	this->w = 0.0;
	this->h = 0.0;
	this->a = 0.0;
}

ng::Rect2::Rect2 (double x, double y, double w, double h) {
	this->p.set(x, y);
	this->w = w;
	this->h = h;
	this->a = 0.0;
}

ng::Rect2::Rect2 (double x, double y, double w, double h, double a) {
	this->p.set(x, y);
	this->w = w;
	this->h = h;
	this->a = a;
}

ng::Rect2::Rect2 (const Vec2* p, double w, double h) {
	this->p = *p;
	this->w = w;
	this->h = h;
	this->a = 0.0;
}

ng::Rect2::Rect2 (const Vec2* p, double w, double h, double a) {
	this->p = *p;
	this->w = w;
	this->h = h;
	this->a = a;
}

ng::Rect2::Rect2 (const Rect2* rect) {
	this->p = rect->p;
	this->w = rect->w;
	this->h = rect->h;
	this->a = rect->a;
}

ng::Rect2::~Rect2 () {}

void ng::Rect2::set (double x, double y, double w, double h) {
	this->p.set(x, y);
	this->w = w;
	this->h = h;
	this->a = 0.0;
}

void ng::Rect2::set (double x, double y, double w, double h, double a) {
	this->p.set(x, y);
	this->w = w;
	this->h = h;
	this->a = a;
}

void ng::Rect2::set (const Vec2* p, double w, double h) {
	this->p = *p;
	this->w = w;
	this->h = h;
	this->a = 0.0;
}

void ng::Rect2::set (const Vec2* p, double w, double h, double a) {
	this->p = *p;
	this->w = w;
	this->h = h;
	this->a = a;
}

bool ng::Rect2::contains (double x, double y) const {
	double a, b;
	a = this->w * 0.5;
	b = this->h * 0.5;
	return !(x < this->p.x - a || x >= this->p.x + a ||
		y < this->p.y - b || y >= this->p.y + b);
}

bool ng::Rect2::contains (const Vec2* p) const {
	double a, b;
	a = this->w * 0.5;
	b = this->h * 0.5;
	return !(p->x < this->p.x - a || p->x >= this->p.x + a ||
		p->y < this->p.y - b || p->y >= this->p.y + b);
}

ng::Basis2::Basis2 () {
	this->u.set(1.0, 0.0);
	this->v.set(0.0, 1.0);
}

ng::Basis2::Basis2 (double i, double j) {
	this->u.set(i, 0.0);
	this->v.set(0.0, j);
}

ng::Basis2::Basis2 (double ux, double uy, double vx, double vy) {
	this->u.set(ux, uy);
	this->v.set(vx, vy);
}

ng::Basis2::Basis2 (const Vec2* u, const Vec2* v) {
	this->u = *u;
	this->v = *v;
}

ng::Basis2::Basis2 (const Basis2* basis) {
	this->u = basis->u;
	this->v = basis->v;
}

ng::Basis2::~Basis2 () {}

void ng::Basis2::set (double i, double j) {
	this->u.set(i, 0.0);
	this->v.set(0.0, j);
}

void ng::Basis2::set (double ux, double uy, double vx, double vy) {
	this->u.set(ux, uy);
	this->v.set(vx, vy);
}

void ng::Basis2::set (const Vec2* u, const Vec2* v) {
	this->u = *u;
	this->v = *v;
}

void ng::Basis2::rescale (double i, double j) {
	this->u.normalize();
	this->v.normalize();
	this->u.set(this->u.x * i, this->u.y * i);
	this->v.set(this->v.x * j, this->v.y * j);
}

void ng::Basis2::rotate (double a) {
	double cosa, sina;
	cosa = cos(a);
	sina = sin(a);
	this->u.rotate(sina, cosa);
	this->v.rotate(sina, cosa);
}

void ng::Basis2::rotate (double sina, double cosa) {
	this->u.rotate(sina, cosa);
	this->v.rotate(sina, cosa);
}

void ng::Basis2::inverse () {
	double det, idet, ux, vy;
	det = ng::determinant(this->u.x, this->v.x, this->u.y, this->v.y);
	if (det == 0.0) {
		return;
	}
	idet = 1.0/det;
	vy = this->v.y;
	ux = this->u.x;
	this->u.set(idet * vy, idet * -this->u.y);
	this->v.set(idet * -this->v.x, idet * ux);
}

void ng::Basis2::inverse (const Basis2* basis) {
	double det, idet, ux, vy;
	det = ng::determinant(basis->u.x, basis->v.x, basis->u.y, basis->v.y);
	if (det == 0.0) {
		return;
	}
	idet = 1.0/det;
	this->u.set(idet * basis->v.y, idet * -basis->u.y);
	this->v.set(idet * -basis->v.x, idet * basis->u.x);
}

ng::Space2::Space2 () {
	this->p.set(0.0, 0.0);
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->inverse.set(1.0, 1.0);
	this->a = 0.0;
}

ng::Space2::Space2 (double x, double y) {
	this->p.set(x, y);
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->inverse.set(1.0, 1.0);
	this->a = 0.0;
}

ng::Space2::Space2 (double x, double y, double a) {
	this->p.set(x, y);
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

ng::Space2::Space2 (double x, double y, double i, double j) {
	this->p.set(x, y);
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->inverse.inverse(&this->basis);
	this->a = 0.0;
}

ng::Space2::Space2 (double x, double y, double i, double j, double a) {
	this->p.set(x, y);
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

ng::Space2::Space2 (const Vec2* p) {
	this->p = *p;
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->inverse.set(1.0, 1.0);
	this->a = 0.0;
}

ng::Space2::Space2 (const Vec2* p, double a) {
	this->p = *p;
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

ng::Space2::Space2 (const Vec2* p, double i, double j) {
	this->p = *p;
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->inverse.inverse(&this->basis);
	this->a = 0.0;
}

ng::Space2::Space2 (const Vec2* p, double i, double j, double a) {
	this->p = *p;
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

ng::Space2::Space2 (const Space2* space) {
	this->p = space->p;
	this->basis = space->basis;
	this->inverse = space->inverse;
	this->i = space->i;
	this->j = space->j;
	this->a = space->a;
}

ng::Space2::~Space2 () {}

void ng::Space2::set (double x, double y) {
	this->p.set(x, y);
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->inverse.set(1.0, 1.0);
	this->a = 0.0;
}

void ng::Space2::set (double x, double y, double a) {
	this->p.set(x, y);
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

void ng::Space2::set (double x, double y, double i, double j) {
	this->p.set(x, y);
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->inverse.inverse(&this->basis);
	this->a = 0.0;
}

void ng::Space2::set (double x, double y, double i, double j, double a) {
	this->p.set(x, y);
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

void ng::Space2::set (const Vec2* p) {
	this->p = *p;
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->inverse.set(1.0, 1.0);
	this->a = 0.0;
}

void ng::Space2::set (const Vec2* p, double a) {
	this->p = *p;
	this->i = 1.0;
	this->j = 1.0;
	this->basis.set(1.0, 1.0);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

void ng::Space2::set (const Vec2* p, double i, double j) {
	this->p = *p;
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->inverse.inverse(&this->basis);
	this->a = 0.0;
}

void ng::Space2::set (const Vec2* p, double i, double j, double a) {
	this->p = *p;
	this->i = i;
	this->j = j;
	this->basis.set(i, j);
	this->basis.rotate(a);
	this->inverse.inverse(&this->basis);
	this->a = a;
}

// Change from this to parent space.
void ng::Space2::absolute (Vec2* const vec) const {
	double x, y;
	x = vec->x;
	y = vec->y;
	vec->x = (this->basis.u.x * x) + (this->basis.v.x * y) + this->p.x;
	vec->y = (this->basis.u.y * x) + (this->basis.v.y * y) + this->p.y;
}

void ng::Space2::absolute (Line2* const line) const {
	this->absolute(&line->p);
	this->absolute(&line->v);
}

void ng::Space2::absolute (Rect2* const rect) const {
	this->absolute(&rect->p);
	rect->w *= this->i;
	rect->h *= this->j;
	rect->a += this->a;
}

void ng::Space2::absolute (Basis2* const basis) const {
	this->absolute(&basis->u);
	this->absolute(&basis->v);
}

void ng::Space2::absolute (Space2* const space) const {
	this->absolute(&space->p);
	this->absolute(&space->basis);
	space->inverse.inverse(&space->basis);
	space->i *= this->i;
	space->j *= this->j;
	space->a += this->a;
}

// Change from parent to this space.
void ng::Space2::relative (Vec2* const vec) const {
	double x, y;
	x = vec->x - this->p.x;
	y = vec->y - this->p.y;
	vec->x = (this->inverse.u.x * x) + (this->inverse.v.x * y);
	vec->y = (this->inverse.u.y * x) + (this->inverse.v.y * y);
}

void ng::Space2::relative (Line2* const line) const {
	this->relative(&line->p);
	this->relative(&line->v);
}

void ng::Space2::relative (Rect2* const rect) const {
	this->relative(&rect->p);
	rect->w /= this->i;
	rect->h /= this->j;
	rect->a -= this->a;
}

void ng::Space2::relative (Basis2* const basis) const {
	this->relative(&basis->u);
	this->relative(&basis->v);
}

void ng::Space2::relative (Space2* const space) const {
	this->relative(&space->p);
	this->relative(&space->basis);
	space->inverse.inverse(&space->basis);
	space->i /= this->i;
	space->j /= this->j;
	space->a -= this->a;
}

ng::Grid2::Grid2 () {
	this->p.set(0.0, 0.0);
	this->i = 1.0;
	this->j = 1.0;
	this->c = 0.0;
	this->r = 0.0;
}

ng::Grid2::Grid2 (double i, double j, double c, double r) {
	this->p.set(0.0, 0.0);
	this->i = i;
	this->j = j;
	this->c = c;
	this->r = r;
}

ng::Grid2::Grid2 (double x, double y, double i, double j, double c, double r) {
	this->p.set(x, y);
	this->i = i;
	this->j = j;
	this->c = c;
	this->r = r;
}

ng::Grid2::Grid2 (const Vec2* p, double i, double j, double c, double r) {
	this->p = *p;
	this->i = i;
	this->j = j;
	this->c = c;
	this->r = r;
}

ng::Grid2::Grid2 (const Grid2* grid) {
	this->p = grid->p;
	this->i = grid->i;
	this->j = grid->j;
	this->c = grid->c;
	this->r = grid->r;
}

ng::Grid2::~Grid2 () {}

void ng::Grid2::set (double i, double j, double c, double r) {
	this->p.set(0.0, 0.0);
	this->i = i;
	this->j = j;
	this->c = c;
	this->r = r;
}

void ng::Grid2::set (double x, double y, double i, double j, double c, double r) {
	this->p.set(x, y);
	this->i = i;
	this->j = j;
	this->c = c;
	this->r = r;
}

void ng::Grid2::set (const Vec2* p, double i, double j, double c, double r) {
	this->p = *p;
	this->i = i;
	this->j = j;
	this->c = c;
	this->r = r;
}

void ng::Grid2::absolute (Vec2* const vec) const {
	// vec*{i, j}
	// +p
	vec->x = (vec->x * this->i) + this->p.x;
	vec->y = (vec->y * this->j) + this->p.y;
}

void ng::Grid2::absolute (Rect2* const rect) const {
	this->absolute(&rect->p);
	rect->w *= this->i;
	rect->h *= this->j;
}

void ng::Grid2::relative (Vec2* const vec) const {
	// vec-p
	// /{i, j}
	vec->x = (vec->x - this->p.x) / this->i;
	vec->y = (vec->y - this->p.y) / this->j;
}

void ng::Grid2::relative (Rect2* const rect) const {
	this->relative(&rect->p);
	rect->w /= this->i;
	rect->h /= this->j;
}
*/


