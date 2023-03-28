
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngmath.h"

// given x (-inf, inf) and m [1, inf), produces [0, m).
// unlike mod(x, m), does NOT mirror x over y-axis.
// eg: for m=360, wrap(-359)=1, wrap(-1)=359, wrap(1)=1, wrap(359)=359.
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
	return std::mod(x + (2147483648.0 * m), m);
}

// Bhaskara I's sine approximation
// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
int ng::bhaskara (int x, int r) {
	// max absolute error is 0.00166, and max relative error is 1.9 percent.
	// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
	// cast to int64 to avoid overflow for large r.
	int64_t x1, r1, p, y;
	int result;
	x1 = static_cast<int64_t>(x);
	r1 = static_cast<int64_t>(r);
	p = x1 * (INT64_C(180) - x1);
	y = (INT64_C(4) * p * r1) / (INT64_C(40500) - p);
	result = static_cast<int>(y);
	return result;
}

// given degrees x [0, 180], produces sin(x) [0, 1].
double ng::bhaskara (double x) {
	double p, y;
	p = x * (180.0 - x);
	y = (4.0 * p) / (40500.0 - p);
	return y;
}

// quick integer sine.
// given degrees x [0, 360), and radius r (-inf, inf), produces sin(x) [-r, r].
int ng::qsin (int x, int r) {
	if (x <= 180) {
		return ng::bhaskara(x, r);
	} else {
		return -ng::bhaskara(x - 180, r);
	}
}

// given degrees x [0, 360), produces sin(x) [-1, 1].
double ng::qsin (double x) {
	if (x <= 180.0) {
		return ng::bhaskara(x);
	} else {
		return -ng::bhaskara(x - 180.0);
	}
}

// quick integer cosine.
// given degrees x [0, 360), and radius r (-inf, inf), produces cos(x) [-r, r].
int ng::qcos (int x, int r) {
	if (x <= 90) {
		return ng::bhaskara(x + 90, r);
	} else if (x < 270) {
		return -ng::bhaskara(x - 90, r);
	} else {
		return ng::bhaskara(x - 270, r);
	}
}

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

// integer square root.
// int wrapper for float sqrt function in math.h
// assumes x >= 0.
int ng::sqrt (int64_t x) {
	double x1, y;
	int result;
	x1 = static_cast<double>(x);
	y = std::sqrt(x1);
	result = static_cast<int>(y);
	return result;
}

// x squared.
int64_t ng::sq (int x) {
	int64_t x1, y;
	x1 = static_cast<int64_t>(x);
	y = x1 * x1;
	return y;
}

// L1 distance, taxicab distance, or manhattan distance.
int ng::distance_l1 (const Vec* a, const Vec* a) {
	Vec d;
	d.init(b->x - a->x, b->y - a->y);
	return d.len_l1();
}

double ng::distance_l1 (const Vec* a, const Vec* b) {
	Vec d;
	d.init(b->x - a->x, b->y - a->y);
	return d.len_l1();
}

// squared euclidean/pythagorean distance.
int ng::distance_sq (const Vec* a, const Vec* b) {
	Vec d;
	d.init(b->x - a->x, b->y - a->y);
	return d.len_sq();
}

double ng::distance_sq (const Vec* a, const Vec* b) {
	Vec d;
	d.init(b->x - a->x, b->y - a->y);
	return d.len_sq();
}

// euclidean/pythagorean distance.
int ng::distance (const Vec* a, const Vec* b) {
	Vec d;
	d.init(b->x - a->x, b->y - a->y);
	return d.len();
}

double ng::distance (const Vec* a, const Vec* b) {
	Vec d;
	d.init(b->x - a->x, b->y - a->y);
	return d.len();
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

void ng::Vec::init2 (double x, double y) {
	this->x = x;
	this->y = y;
}

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

void ng::Rect::init2 (double x, double y, double w, double h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
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
	s.init2(this->x - a, this->y - b, this->w + r->w, this->h + r->h);
	return s.contains2(r->x + a, r->y + b);
}

void ng::Space::init2_n (const Rect* rect, double c, double r) {
	this->rect = *rect;
	this->c = c;
	this->r = r;
	this->i = rect->w / c;
	this->j = rect->h / r;
}

void ng::Space::init2_u (const Rect* rect, double i, double j) {
	this->rect = *rect;
	this->c = rect->w / i;
	this->r = rect->h / j;
	this->i = i;
	this->j = j;
}

void ng::Space::scale2_n (double s) {
	this->rect.scale2(s);
	this->c *= s;
	this->r *= s;
}

void ng::Space::scale2_n (double x, double y) {
	this->rect.scale2(x, y);
	this->c *= x;
	this->r *= y;
}

void ng::Space::scale2_u (double s) {
	this->rect.scale2(s);
	this->i *= s;
	this->j *= s;
}

void ng::Space::scale2_u (double x, double y) {
	this->rect.scale2(x, y);
	this->i *= x;
	this->j *= y;
}

void ng::Space::absolute_to_relative2_n (const Space* s) {
	this->rect.x -= s->rect.x;
	this->rect.y -= s->rect.y;
	this->scale2_n(1.0/s->i, 1.0/s->j);
}

void ng::Space::absolute_to_relative2_u (const Space* s) {
	this->rect.x -= s->rect.x;
	this->rect.y -= s->rect.y;
	this->scale2_u(1.0/s->i, 1.0/s->j);
}

void ng::Space::relative_to_absolute2_n (const Space* s) {
	this->scale2_n(s->i, s->j);
	this->rect.x += s->rect.x;
	this->rect.y += s->rect.y;
}

void ng::Space::relative_to_absolute2_u (const Space* s) {
	this->scale2_u(s->i, s->j);
	this->rect.x += s->rect.x;
	this->rect.y += s->rect.y;
}

void ng::Mass::init2 (const Rect* rect, double m) {
	this->rect = *rect;
	this->vec.init2(0.0, 0.0);
	this->m = m;
}

void ng::Mass::init2 (const Rect* rect, const Vec* vec, double m) {
	this->rect = *rect;
	this->vec = *vec;
	this->m = m;
}

void ng::Mass::move2 () {
	this->rect.x += this->vec.x;
	this->rect.y += this->vec.y;
}

void ng::Mass::move2 (const Vec* vec) {
	this->rect.x += vec->x;
	this->rect.y += vec->y;
}

// if this collides with rect, returns true and vec to collision.
// else, returns false.
bool ng::Mass::collides2 (const Rect* rect, Vec* const vec) {
	//TODO
	return false;
}

// inelastic collision
void ng::Mass::collide2 (const Rect* rect) {
	//TODO
}

// inelastic collision with momentum transfer
void ng::Mass::collide2 (Mass* const mass) {
	//TODO
}


