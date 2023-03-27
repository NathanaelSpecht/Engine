
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngmath.h"

// if (x, y) + (dx, dy) intercepts py axis, find (px, py) and return true.
// else return false.
bool ng::xint (int x, int y, int dx, int dy, int* const px, int py) {
	if ((y < py && y + dy < py) || (y > py && y + dy > py)) {
		return false;
	} else if (y == py) {
		*px = x;
		return true;
	} else {
		int64_t x1, y1, dx1, dy1, b1;
		x1 = static_cast<int64_t>(x);
		y1 = static_cast<int64_t>(y - py);
		dx1 = static_cast<int64_t>(dx);
		dy1 = static_cast<int64_t>(dy);
		
		// x = my + b
		// m = dx/dy
		// b = x-intercept = x - my
		b1 = x1 - ((dx1 * y1)/dy1);
		
		*px = static_cast<int>(b1);
		return true;
	}
}

bool ng::xint (double x, double y, double dx, double dy, double* const px, double py) {
	if ((y < py && y + dy < py) || (y > py && y + dy > py)) {
		return false;
	} else if (y == py) {
		*px = x;
		return true;
	} else {
		*px = x - ((dx * (y - py))/dy);
		return true;
	}
}

// if (x, y) + (dx, dy) intercepts px axis, find (px, py) and return true.
// else return false.
bool ng::yint (int x, int y, int dx, int dy, int px, int* const py) {
	if ((x < px && x + dx < px) || (x > px && x + dx > px)) {
		return false;
	} else if (x == px) {
		*py = y;
		return true;
	} else {
		int64_t x1, y1, dx1, dy1, b1;
		x1 = static_cast<int64_t>(x - px);
		y1 = static_cast<int64_t>(y);
		dx1 = static_cast<int64_t>(dx);
		dy1 = static_cast<int64_t>(dy);
		
		// y = mx + b
		// m = dy/dx
		// b = y-intercept = y - mx
		b1 = y1 - ((dy1 * x1)/dx1);
		
		*py = static_cast<int>(b1);
		return true;
	}
}

bool ng::yint (double x, double y, double dx, double dy, double px, double* const py) {
	if ((x < px && x + dx < px) || (x > px && x + dx > px)) {
		return false;
	} else if (x == px) {
		*py = y;
		return true;
	} else {
		*py = y - ((dy * (x - px))/dx);
		return true;
	}
}

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
int ng::distance_l1 (int x1, int y1, int x2, int y2) {
	return std::abs(x2 - x1) + std::abs(y2 - y1);
}

double ng::distance_l1 (double x1, double y1, double x2, double y2) {
	return std::abs(x2 - x1) + std::abs(y2 - y1);
}

// squared euclidean/pythagorean distance.
int64_t ng::distance_sq (int x1, int y1, int x2, int y2) {
	return ng::sq(x2 - x1) + ng::sq(y2 - y1);
}

double ng::distance_sq (double x1, double y1, double x2, double y2) {
	double xd, yd, d;
	xd = x2 - x1;
	yd = y2 - y1;
	d = (xd * xd) + (yd * yd);
	return d;
}

// euclidean/pythagorean distance.
int ng::distance (int x1, int y1, int x2, int y2) {
	return ng::sqrt(ng::distance_sq(x1, y1, x2, y2));
}

double ng::distance (double x1, double y1, double x2, double y2) {
	return std::sqrt(ng::distance_sq(x1, y1, x2, y2));
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

double ng::scale (const Range* src, const Range* dest) {
	return (dest->b - dest->a) / (src->b - src->a);
}

double ng::scale (const Range* src, const Axis* dest) {
	return dest->n / (src->b - src->a);
}

double ng::scale (const Axis* src, const Range* dest) {
	return (dest->b - dest->a) / src->n;
}

double ng::scale (const Axis* src, const Axis* dest) {
	return dest->n / src->n;
}

void ng::Range::init (int p, int q) {
	if (p <= q) {
		this->a = static_cast<double>(p);
		this->b = static_cast<double>(q);
	} else {
		this->a = static_cast<double>(q);
		this->b = static_cast<double>(p);
	}
}

void ng::Range::init (double p, double q) {
	if (p <= q) {
		this->a = p;
		this->b = q;
	} else {
		this->a = q;
		this->b = p;
	}
}

// a*=s, b*=s
void ng::Range::scale (double s) {
	this->a *= s;
	this->b *= s;
}

bool ng::Range::contains (int x) const {
	return (this->a <= static_cast<double>(x) && static_cast<double>(x) < this->b);
}

bool ng::Range::contains (double x) const {
	return (this->a <= x && x < this->b);
}

bool ng::Range::overlaps (const Range* range) const {
	return (range->a < this->b && range->b > this->a);
}

bool ng::Range::overlaps (const Axis* axis) const {
	return (axis->a < this->b && axis->b > this->a);
}

// true if the vector crosses either edge of this.
bool ng::Range::intersects (int x, int dx) const {
	Range r;
	r.init(x, x+dx);
	return (r.contains(this->a) || r.contains(this->b));
}

bool ng::Range::intersects (double x, double dx) const {
	Range r;
	r.init(x, x+dx);
	return (r.contains(this->a) || r.contains(this->b));
}

// true if this crosses either edge of range.
bool ng::Range::intersects (const Range* range) const {
	return (this->contains(range->a) || this->contains(range->b));
}

bool ng::Range::intersects (const Axis*) const {
	return (this->contains(axis->a) || this->contains(axis->b));
}

void ng::Range::absolute_to_relative (const Range* range) {
	this->a -= range->a;
	this->b -= range->a;
}

void ng::Range::absolute_to_relative (const Axis* axis) {
	this->a -= axis->a;
	this->b -= axis->a;
	this->scale(1.0/axis->u);
}

void ng::Range::relative_to_absolute (const Range* range) {
	this->a += range->a;
	this->b += range->a;
}

void ng::Range::relative_to_absolute (const Axis* axis) {
	this->scale(axis->u);
	this->a += axis->a;
	this->b += axis->a;
}

// n=b-a, u=1
void ng::Axis::init (int p, int q) {
	if (p <= q) {
		this->a = static_cast<double>(p);
		this->b = static_cast<double>(q);
	} else {
		this->a = static_cast<double>(q);
		this->b = static_cast<double>(p);
	}
	this->n = this->b - this->a;
	this->u = 1.0;
}

void ng::Axis::init (double p, double q) {
	if (p <= q) {
		this->a = p;
		this->b = q;
	} else {
		this->a = q;
		this->b = p;
	}
	this->n = this->b - this->a;
	this->u = 1.0;
}

// u=(b-a)/n
void ng::Axis::init_n (double p, double q, double n) {
	if (p <= q) {
		this->a = p;
		this->b = q;
	} else {
		this->a = q;
		this->b = p;
	}
	this->n = n;
	this->u = (this->b - this->a) / n;
}

// n=(b-a)/u
void ng::Axis::init_u (double p, double q, double u) {
	if (p <= q) {
		this->a = p;
		this->b = q;
	} else {
		this->a = q;
		this->b = p;
	}
	this->n = (this->b - this->a) / u;
	this->u = u;
}

// 2 ways to scale axis such that (b-a)*s = (n*u)*s
// scale n, keeping u constant. a*=s, b*=s, n*=s
void ng::Axis::scale_n (double s) {
	this->a *= s;
	this->b *= s;
	this->n *= s;
}

// scale u, keeping n constant. a*=s, b*=s, u*=s
void ng::Axis::scale_u (double s) {
	this->a *= s;
	this->b *= s;
	this->u *= s;
}

bool ng::Axis::contains (int x) const {
	return (this->a <= static_cast<double>(x) && static_cast<double>(x) < this->b);
}

bool ng::Axis::contains (double x) const {
	return (this->a <= x && x < this->b);
}

bool ng::Axis::overlaps (const Range* range) const {
	return (range->a < this->b && range->b > this->a);
}

bool ng::Axis::overlaps (const Axis* axis) const {
	return (axis->a < this->b && axis->b > this->a);
}

// true if the vector crosses either edge of this.
bool ng::Axis::intersects (int x, int dx) const {
	Axis a;
	a.init(x, x+dx);
	return (a.contains(this->a) || a.contains(this->b));
}

bool ng::Axis::intersects (double x, double dx) const {
	Axis a;
	a.init(x, x+dx);
	return (a.contains(this->a) || a.contains(this->b));
}

// true if this crosses either edge of range.
bool ng::Axis::intersects (const Range* range) const {
	return (this->contains(range->a) || this->contains(range->b));
}

bool ng::Axis::intersects (const Axis* axis) const {
	return (this->contains(axis->a) || this->contains(axis->b));
}

void ng::Axis::absolute_to_relative (const Range* range) {
	this->a -= range->a;
	this->b -= range->a;
}

void ng::Axis::absolute_to_relative_n (const Axis* axis) {
	this->a -= axis->a;
	this->b -= axis->a;
	this->scale_n(1.0/axis->u);
}

void ng::Axis::absolute_to_relative_u (const Axis* axis) {
	this->a -= axis->a;
	this->b -= axis->a;
	this->scale_u(1.0/axis->u);
}

void ng::Axis::relative_to_absolute (const Range* range) {
	this->a += range->a;
	this->b += range->a;
}

void ng::Axis::relative_to_absolute_n (const Axis* axis) {
	this->scale_n(axis->u);
	this->a += axis->a;
	this->b += axis->a;
}

void ng::Axis::relative_to_absolute_u (const Axis* axis) {
	this->scale_u(axis->u);
	this->a += axis->a;
	this->b += axis->a;
}


