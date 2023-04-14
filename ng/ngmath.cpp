
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
// 35 cycles.
double ng::bhaskara (double x) {
	// Error computed from the graph of y = f(x) - sin((pi*x)/180).
	// max error of 0.165%. error -> 0 for x -> 0, 30, 90, 150, 180.
	double p = x * (180.0 - x);
	return ((4.0 * p) / (40500.0 - p));
}

// given degrees x [0, 360), produces sin(x) [-1, 1].
// 35-40 cycles.
double ng::qsin (double x) {
	if (x <= 180.0) {
		return ng::bhaskara(x);
	} else {
		return -ng::bhaskara(x - 180.0);
	}
}

// given degrees x [0, 360), produces cos(x) [-1, 1].
// 35-40 cycles.
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

double ng::units (double columns, double width) {
	return width/columns;
}

double ng::columns (double units, double width) {
	return width/units;
}

double ng::determinant (double a, double b, double c, double d) {
	return (a * d) - (b * c);
}

ng::Vec2::Vec2 () {
	this->x = 0.0;
	this->y = 0.0;
}

ng::Vec2::Vec2 (double x, double y) {
	this->x = x;
	this->y = y;
}

ng::Vec2::Vec2 (const Vec2* v) {
	this->x = v->x;
	this->y = v->y;
}

ng::Vec2::~Vec2 () {}

void ng::Vec2::set (double x, double y) {
	this->x = x;
	this->y = y;
}

void ng::Vec2::rotate (double a) {
	double cosa, sina, x, y;
	cosa = cos(a);
	sina = sin(a);
	x = (this->x * cosa) - (this->y * sina);
	y = (this->x * sina) + (this->y * cosa);
	this->x = x;
	this->y = y;
}

void ng::Vec2::rotate (double sina, double cosa) {
	double x, y;
	x = (this->x * cosa) - (this->y * sina);
	y = (this->x * sina) + (this->y * cosa);
	this->x = x;
	this->y = y;
}

void ng::Vec2::normalize () {
	double len = this->length();
	this->x /= len;
	this->y /= len;
}

void ng::Vec2::normalize (double length) {
	this->x /= length;
	this->y /= length;
}

double ng::Vec2::length () const {
	return std::hypot(this->x, this->y);
}

double ng::Vec2::lengthsq () const {
	return (this->x * this->x) + (this->y * this->y);
}

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


ng::Vec::Vec () {
	this->x = 0.0;
	this->y = 0.0;
}

ng::Vec::~Vec () {}

void ng::Vec::set2 (double x, double y) {
	this->x = x;
	this->y = y;
}

// Set this to the vector from p1 to p2.
void ng::Vec::set2 (const Vec* p1, const Vec* p2) {
	this->x = p2->x - p1->x;
	this->y = p2->y - p1->y;
}

// Set this to the scale between relative to src and relative to dest.
// For example, a virtual camera with one side in game, and other side on screen:
// - To draw to screen, src in game world and dest on screen.
// - To get mouse point, src on screen and dest in game world.
void ng::Vec::set2 (const Space* src, const Space* dest) {
	this->x = dest->c / src->c;
	this->y = dest->r / src->r;
}

void ng::Vec::set2 (const Space* src, const Rect* dest) {
	this->x = dest->w / src->c;
	this->y = dest->h / src->r;
}

void ng::Vec::set2 (const Rect* src, const Space* dest) {
	this->x = dest->c / src->w;
	this->y = dest->r / src->h;
}

void ng::Vec::set2 (const Rect* src, const Rect* dest) {
	this->x = dest->w / src->w;
	this->y = dest->h / src->h;
}

// this - v
void ng::Vec::sub2 (const Vec* v) {
	this->x -= v->x;
	this->y -= v->y;
}

// flip this over EnumSide.
void ng::Vec::flip2 (int side) {
	switch (side) {
		case ng::SideX: {
			this->y = -this->y;
			break;
		} case ng::SideY: {
			this->x = -this->x;
			break;
		} default: {}
	}
}

// this * s
void ng::Vec::scale2 (double s) {
	this->x *= s;
	this->y *= s;
}

void ng::Vec::scale2 (double x, double y) {
	this->x *= x;
	this->y *= y;
}

void ng::Vec::absolute_to_relative2 (const Space* s) {
	this->x -= s->rect.x;
	this->y -= s->rect.y;
	this->scale2(1.0/s->i, 1.0/s->j);
}

void ng::Vec::relative_to_absolute2 (const Space* s) {
	this->scale2(s->i, s->j);
	this->x += s->rect.x;
	this->y += s->rect.y;
}

// distance from this to p.
// L1 distance.
double ng::Vec::distance2_l1 (const Vec* p) const {
	return (std::abs(p->x - this->x) + std::abs(p->y - this->y));
}

// squared euclidean distance.
double ng::Vec::distance2_sq (const Vec* p) const {
	double dx, dy;
	dx = p->x - this->x;
	dy = p->y - this->y;
	return ((dx * dx) + (dy * dy));
}

// euclidean distance.
double ng::Vec::distance2 (const Vec* p) const {
	return std::hypot(p->x - this->x, p->y - this->y);
}

// if p+v intersects this axis, then return true and this is intercept.
// else return false.
// x-intercept along this y.
bool ng::Vec::xint2 (const Vec* p, const Vec* v) {
	// (x,y) is p, 1/m is dx/dy (v->x/v->y), b is x-intercept (this->x), axis is this->y.
	// x = (1/m)(axis - y) + b
	// b = x - (1/m)(axis - y)
	if ((p->y < this->y && p->y + v->y < this->y) ||
	(p->y > this->y && p->y + v->y > this->y)) {
		// p+v does not intersect axis.
		return false;
		
	} else if (p->y == this->y) {
		// p is already on axis. b is x.
		this->x = p->x;
		return true;
		
	} else {
		// p+v intersects axis. find b.
		this->x = p->x - ((v->x / v->y) * (this->y - p->y));
		return true;
	}
}

// y-intercept along this x.
bool ng::Vec::yint2 (const Vec* p, const Vec* v) {
	// (x,y) is p, m is dy/dx (v->y/v->x), b is y-intercept (this->y), axis is this->x.
	// y = m(axis - x) + b
	// b = y - m(axis - x)
	if ((p->x < this->x && p->x + v->x < this->x) ||
	(p->x > this->x && p->x + v->x > this->x)) {
		// p+v does not intersect axis.
		return false;
		
	} else if (p->x == this->x) {
		// p is already on axis. b is y.
		this->y = p->y;
		return true;
		
	} else {
		// p+v intersects axis. find b.
		this->y = p->y - ((v->y / v->x) * (this->x - p->x));
		return true;
	}
}

ng::Rect::Rect () {
	this->x = 0.0;
	this->y = 0.0;
	this->w = 0.0;
	this->h = 0.0;
}

ng::Rect::~Rect () {}

void ng::Rect::set2 (double x, double y, double w, double h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void ng::Rect::moveby2 (const Vec* v) {
	this->x += v->x;
	this->y += v->y;
}

void ng::Rect::scale2 (double s) {
	this->x *= s;
	this->y *= s;
	this->w *= s;
	this->h *= s;
}

void ng::Rect::scale2 (double x, double y) {
	this->x *= x;
	this->y *= y;
	this->w *= x;
	this->h *= y;
}

void ng::Rect::absolute_to_relative2 (const Space* s) {
	this->x -= s->rect.x;
	this->y -= s->rect.y;
	this->scale2(1.0/s->i, 1.0/s->j);
}

void ng::Rect::relative_to_absolute2 (const Space* s) {
	this->scale2(s->i, s->j);
	this->x += s->rect.x;
	this->y += s->rect.y;
}

bool ng::Rect::contains2 (double x, double y) const {
	return ((this->x < x && x < this->x + this->w) &&
		(this->y < y && y < this->y + this->h));
}

bool ng::Rect::overlaps2 (const Rect* r) const {
	double a, b;
	a = r->w * 0.5;
	b = r->h * 0.5;
	Rect s;
	s.set2(this->x - a, this->y - b, this->w + r->w, this->h + r->h);
	return s.contains2(r->x + a, r->y + b);
}

// if p+v intersects the edge of this, returns true, and
// sets vint to the part of v which produces an intersection, and
// sets side to the intersecting side (see EnumSide).
// else, returns false, and sets vint to v.
bool ng::Rect::intersect2 (const Vec* p, const Vec* v, Vec* const vint, int* const side) const {
	Rect c = *this; // collider
	bool intersect = false;
	Vec p1, p2, p3, p4, pint;
	p1.x = c.x;
	p2.x = c.x + c.w;
	p3.y = c.y;
	p4.y = c.y + c.h;
	
	if (p1.yint2(p, v) && c.y <= p1.y && p1.y < c.y + c.h) {
		intersect = true;
		pint = p1;
		*side = ng::SideY;
	}
	if (p2.yint2(p, v) && c.y <= p2.y && p2.y < c.y + c.h &&
	(!intersect || p->distance2_l1(&p2) < p->distance2_l1(&pint))) {
		intersect = true;
		pint = p2;
		*side = ng::SideY;
	}
	if (p3.xint2(p, v) && c.x <= p3.x && p3.x < c.x + c.w &&
	(!intersect || p->distance2_l1(&p3) < p->distance2_l1(&pint))) {
		intersect = true;
		pint = p3;
		*side = ng::SideX;
	}
	if (p4.xint2(p, v) && c.x <= p4.x && p4.x < c.x + c.w &&
	(!intersect || p->distance2_l1(&p4) < p->distance2_l1(&pint))) {
		intersect = true;
		pint = p4;
		*side = ng::SideX;
	}
	
	if (intersect) {
		vint->set2(p, &pint);
	} else {
		*vint = *v;
	}
	return intersect;
}

ng::Space::Space () {
	this->c = 0.0;
	this->r = 0.0;
	this->i = 1.0;
	this->j = 1.0;
}

ng::Space::~Space () {}

void ng::Space::set2 (double x, double y, double w, double h) {
	this->rect.set2(x, y, w, h);
	this->c = w;
	this->r = h;
	this->i = 1.0;
	this->j = 1.0;
	this->const_c = true;
}

void ng::Space::set2 (const Rect* rect) {
	this->rect = *rect;
	this->c = rect->w;
	this->r = rect->h;
	this->i = 1.0;
	this->j = 1.0;
	this->const_c = true;
}

void ng::Space::set2_c (double x, double y, double w, double h, double c, double r) {
	this->rect.set2(x, y, w, h);
	this->c = c;
	this->r = r;
	this->i = w / c;
	this->j = h / r;
	this->const_c = true;
}

void ng::Space::set2_c (const Rect* rect, double c, double r) {
	this->rect = *rect;
	this->c = c;
	this->r = r;
	this->i = rect->w / c;
	this->j = rect->h / r;
	this->const_c = true;
}

void ng::Space::set2_i (double x, double y, double w, double h, double i, double j) {
	this->rect.set2(x, y, w, h);
	this->c = w / i;
	this->r = h / j;
	this->i = i;
	this->j = j;
	this->const_c = false;
}

void ng::Space::set2_i (const Rect* rect, double i, double j) {
	this->rect = *rect;
	this->c = rect->w / i;
	this->r = rect->h / j;
	this->i = i;
	this->j = j;
	this->const_c = false;
}

void ng::Space::resize2 (double w, double h) {
	if (this->const_c) {
		this->i *= w / this->rect.w;
		this->j *= h / this->rect.h;
	} else {
		this->c *= w / this->rect.w;
		this->r *= h / this->rect.h;
	}
	this->rect.w = w;
	this->rect.h = h;
}

void ng::Space::scale2 (double s) {
	this->rect.scale2(s);
	if (this->const_c) {
		this->i *= s;
		this->j *= s;
	} else {
		this->c *= s;
		this->r *= s;
	}
}

void ng::Space::scale2 (double x, double y) {
	this->rect.scale2(x, y);
	if (this->const_c) {
		this->i *= x;
		this->j *= y;
	} else {
		this->c *= x;
		this->r *= y;
	}
}

void ng::Space::absolute_to_relative2 (const Space* s) {
	this->rect.x -= s->rect.x;
	this->rect.y -= s->rect.y;
	this->scale2(1.0/s->i, 1.0/s->j);
}

void ng::Space::relative_to_absolute2 (const Space* s) {
	this->scale2(s->i, s->j);
	this->rect.x += s->rect.x;
	this->rect.y += s->rect.y;
}

ng::Mass::Mass () {
	this->m = 0.0;
}

ng::Mass::~Mass () {}

void ng::Mass::set2 (double x, double y, double w, double h, double m) {
	this->rect.set2(x, y, w, h);
	this->vec.set2(0.0, 0.0);
	this->m = m;
}

void ng::Mass::set2 (const Rect* rect, double m) {
	this->rect = *rect;
	this->vec.set2(0.0, 0.0);
	this->m = m;
}

void ng::Mass::set2 (const Rect* rect, const Vec* vec, double m) {
	this->rect = *rect;
	this->vec = *vec;
	this->m = m;
}

void ng::Mass::move2 () {
	this->rect.moveby2(&this->vec);
}

// intersect this rect+vec with r. (see Rect::intersect)
bool ng::Mass::intersect2 (const Rect* r, Vec* const vint, int* const side) {
	// (this center+vec) intersects edge of (r center, r radius + this radius).
	Rect c; // collider
	Vec p, v; // this center and vec
	double a, b; // this radius
	a = this->rect.w * 0.5;
	b = this->rect.h * 0.5;
	p.set2(this->rect.x + a, this->rect.y + b);
	v = this->vec;
	c.set2(r->x - a, r->y - b, r->w + this->rect.w, r->h + this->rect.h);
	
	return c.intersect2(&p, &v, vint, side);
}

// Elastic collision without momentum transfer.
// qbounce ignores all other possible collisions!
// vint and side are the same parameters returned by intersect.
void ng::Mass::qbounce2 (const Vec* vint, int side) {
	Vec v = this->vec;
	this->rect.moveby2(vint);
	v.sub2(vint);
	v.flip2(side);
	this->rect.moveby2(&v);
	this->vec.flip2(side);
}

// Elastic collision without momentum transfer.
// bounce allows for more collisions along the remaining path of this mass.
// vint and side are the same parameters returned by intersect.
void ng::Mass::bounce2 (const Vec* vint, int side) {
	this->rect.moveby2(vint);
	this->vec.sub2(vint);
	this->vec.flip2(side);
}

// Perfectly inelastic momentum transfer.
// For when two moving masses collide and stick together, without deformation.
// For example: you're moving, an object is moving, and you pick it up.
// 2 versions: one like qbounce and the other like bounce.
void ng::Mass::qcollide2_inelastic (Mass* const) {
	// TODO
}

void ng::Mass::collide2_inelastic (Mass* const) {
	// TODO
}

// Perfectly elastic momentum transfer and bounce.
// For when two moving masses collide and bounce, transfering energy perfectly
// without deformation.
// For example: an object hits another object and they ricochet off each other.
// 2 versions: one like qbounce and the other like bounce.
void ng::Mass::qcollide2_elastic (Mass* const) {
	// TODO
}

void ng::Mass::collide2_elastic (Mass* const) {
	// TODO
}



