
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngmath.h"

bool intersects (int x, int dx, int axis) {
	return !((x < axis && x + dx < axis) || (x > axis && x + dx > axis));
}

bool intersects (double x, double dx, double axis) {
	return !((x < axis && x + dx < axis) || (x > axis && x + dx > axis));
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
int ng::distance_l1 (const Vec* p1, const Vec* p2) {
	Vec d;
	d.init(p2->x - p1->x, p2->y - p1->y);
	return d.len_l1();
}

double ng::distance_l1 (const Vec* p1, const Vec* p2) {
	Vec d;
	d.init(p2->x - p1->x, p2->y - p1->y);
	return d.len_l1();
}

// squared euclidean/pythagorean distance.
int ng::distance_sq (const Vec* p1, const Vec* p2) {
	Vec d;
	d.init(p2->x - p1->x, p2->y - p1->y);
	return d.len_sq();
}

double ng::distance_sq (const Vec* p1, const Vec* p2) {
	Vec d;
	d.init(p2->x - p1->x, p2->y - p1->y);
	return d.len_sq();
}

// euclidean/pythagorean distance.
int ng::distance (const Vec* p1, const Vec* p2) {
	Vec d;
	d.init(p2->x - p1->x, p2->y - p1->y);
	return d.len();
}

double ng::distance (const Vec* p1, const Vec* p2) {
	Vec d;
	d.init(p2->x - p1->x, p2->y - p1->y);
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

void ng::Range::absolute_to_relative (const Axis* axis) {
	this->a -= axis->a;
	this->b -= axis->a;
	this->scale(1.0/axis->u);
}

void ng::Range::relative_to_absolute (const Axis* axis) {
	this->scale(axis->u);
	this->a += axis->a;
	this->b += axis->a;
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

void ng::Diameter::init (int p, int r) {
	this->p = p;
	this->r = std::abs(r);
}

void ng::Diameter::init (double p, double r) {
	this->p = p;
	this->r = std::abs(r);
}

// p*=s, r*=s
void ng::Diameter::scale (double s) {
	this->p *= s;
	this->r *= s;
}

void ng::Diameter::absolute_to_relative (const Axis*) {
	this->p -= axis->a;
	this->scale(1.0/axis->u);
}

void ng::Diameter::relative_to_absolute (const Axis*) {
	this->scale(axis->u);
	this->p += axis->a;
}

bool ng::Diameter::contains (int x) const {
	return (std::abs(static_cast<double>(x) - this->p) < this->r);
}

bool ng::Diameter::contains (double x) const {
	return (std::abs(x - this->p) < this->r);
}

bool ng::Diameter::overlaps (const Diameter* dia) const {
	return (std::abs(dia->p - this->p) < this->r + dia->r);
}

// true if the vector crosses either edge of this.
bool ng::Diameter::intersects (int x, int dx) const {
	return (ng::intersects(x, dx, static_cast<int>(this->p - this->r)) ||
		ng::intersects(x, dx, static_cast<int>(this->p + this->r)));
}

bool ng::Diameter::intersects (double x, double dx) const {
	return (ng::intersects(x, dx, this->p - this->r) || ng::intersects(x, d, this->p + this->r));
}

// true if this crosses either edge of diameter.
bool ng::Diameter::intersects (const Diameter* d) const {
	return (this->contains(d->p - d->r) || this->contains(d->p + d->r));
}

void ng::Vec::init2 (int x, int y) {
	this->x = static_cast<double>(x);
	this->y = static_cast<double>(y);
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

void ng::Vec::absolute_to_relative2 (const Space* space) {
	this->x -= space->x.a;
	this->y -= space->y.a;
	this->scale2(1.0/space->x.u, 1.0/space->y.u);
}

void ng::Vec::relative_to_absolute2 (const Space* space) {
	this->scale2(space->x.u, space->y.u);
	this->x += space->x.a;
	this->y += space->y.a;
}

// if p + v intercepts y axis in R2, find this and return true.
// else return false.
bool ng::Vec::xint2 (const Vec* p, const Vec* v) {
	if ((p->y < this->y && p->y + v->y < this->y) || (p->y > this->y && p->y + v->y > this->y)) {
		return false;
	} else if (p->y == this->y) {
		this->x = p->x;
		return true;
	} else {
		// x = my + b
		// m = dx/dy
		// b = x-intercept = x - my
		this->x = p->x - ((v->x * (p->y - this->y))/v->y);
		return true;
	}
}

// if p + v intercepts x axis in R2, find this and return true.
// else return false.
bool ng::Vec::yint2 (const Vec* p, const Vec* v) {
	if ((p->x < this->x && p->x + v->x < this->x) || (p->x > this->x && p->x + v->x > this->x)) {
		return false;
	} else if (p->x == this->x) {
		this->y = p->y;
		return true;
	} else {
		// y = mx + b
		// m = dy/dx
		// b = y-intercept = y - mx
		this->y = p->y - ((v->y * (p->x - this->x))/v->x);
		return true;
	}
}

// L1/taxicab/manhattan distance in R2.
int ng::Vec::len2_l1 () const {
	return static_cast<int>(std::abs(this->x) + std::abs(this->y));
}

double ng::Vec::len2_l1 () const {
	return std::abs(this->x) + std::abs(this->y);
}

// squared distance in R2.
int64_t ng::Vec::len2_sq () const {
	return static_cast<int>((this->x * this->x) + (this->y * this->y));
}

double ng::Vec::len2_sq () const {
	return (this->x * this->x) + (this->y * this->y);
}

// distance in R2.
int ng::Vec::len2 () const {
	return static_cast<int>(std::hypot(this->x, this->y));
}

double ng::Vec::len2 () const {
	return std::hypot(this->x, this->y);
}

void ng::Rect::init2 (int x1, int y1, int x2, int y2) {
	this->x.init(x1, x2);
	this->y.init(y1, y2);
}

void ng::Rect::init2 (double x1, double y1, double x2, double y2) {
	this->x.init(x1, x2);
	this->y.init(y1, y2);
}

void ng::Rect::init2 (const Range* x, const Range* y) {
	this->x = *x;
	this->y = *y;
}

void ng::Rect::scale2 (double s) {
	this->x.scale(s);
	this->y.scale(s);
}

void ng::Rect::scale2 (double x, double y) {
	this->x.scale(x);
	this->y.scale(y);
}

void ng::Rect::absolute_to_relative2 (const Space* space) {
	this->x.absolute_to_relative(&space->x);
	this->y.absolute_to_relative(&space->y);
}

void ng::Rect::relative_to_absolute2 (const Space* space) {
	this->x.relative_to_absolute(&space->x);
	this->y.relative_to_absolute(&space->y);
}

bool ng::Rect::contains2 (int x, int y) const {
	return (this->x.contains(x) && this->y.contains(y));
}

bool ng::Rect::contains2 (double x, double y) const {
	return (this->x.contains(x) && this->y.contains(y));
}

void ng::Space::init2 (int x1, int y1, int x2, int y2) {
	this->x.init(x1, x2);
	this->y.init(y1, y2);
}

void ng::Space::init2 (double x1, double y1, double x2, double y2) {
	this->x.init(x1, x2);
	this->y.init(y1, y2);
}

void ng::Space::init2_n (const Rect* rect, double n) {
	this->x.init_n(rect->x.a, rect->x.b, n);
	this->y.init_n(rect->y.a, rect->y.b, n);
}

void ng::Space::init2_n (const Rect* rect, double nx, double ny) {
	this->x.init_n(rect->x.a, rect->x.b, nx);
	this->y.init_n(rect->y.a, rect->y.b, ny);
}

void ng::Space::init2_u (const Rect* rect, double u) {
	this->x.init_u(box->x.a, rect->x.b, u);
	this->y.init_u(box->y.a, rect->y.b, u);
}

void ng::Space::init2_u (const Rect* rect, double ux, double uy) {
	this->x.init_u(rect->x.a, rect->x.b, ux);
	this->y.init_u(rect->y.a, rect->y.b, uy);
}

void ng::Space::init2 (const Axis* x, const Axis* y) {
	this->x = *x;
	this->y = *y;
}

void ng::Space::scale2_n (double s) {
	this->x.scale_n(s);
	this->y.scale_n(s);
}

void ng::Space::scale2_n (double x, double y) {
	this->x.scale_n(x);
	this->y.scale_n(y);
}

void ng::Space::scale2_u (double s) {
	this->x.scale_u(s);
	this->y.scale_u(s);
}

void ng::Space::scale2_u (double x, double y) {
	this->x.scale_u(x);
	this->y.scale_u(y);
}

void ng::Space::absolute_to_relative2_n (const Space* space) {
	this->x.absolute_to_relative_n(&space->x);
	this->y.absolute_to_relative_n(&space->y);
}

void ng::Space::absolute_to_relative2_u (const Space* space) {
	this->x.absolute_to_relative_u(&space->x);
	this->y.absolute_to_relative_u(&space->y);
}

void ng::Space::relative_to_absolute2_n (const Space* space) {
	this->x.relative_to_absolute_n(&space->x);
	this->y.relative_to_absolute_n(&space->y);
}

void ng::Space::relative_to_absolute2_u (const Space* space) {
	this->x.relative_to_absolute_u(&space->x);
	this->y.relative_to_absolute_u(&space->y);
}

void ng::Box::init2 (int x, int y, int a, int b) {
	this->x.init(x, a);
	this->y.init(y, b);
}

void ng::Box::init2 (double x, double y, double a, double b) {
	this->x.init(x, a);
	this->y.init(y, b);
}

void ng::Box::init2 (const Rect* rect) {
	double rx, ry;
	rx = (rect->x.b - rect->x.a) * 0.5;
	ry = (rect->y.b - rect->y.a) * 0.5;
	this->x.init(rect->x.a + rx, rx);
	this->y.init(rect->y.a + ry, ry);
}

// get a rect for drawing this box.
void ng::Box::get_rect2 (Rect* const rect) const {
	rect->x.init(this->x.p - this->x.r, this->x.p + this->x.r);
	rect->y.init(this->y.p - this->y.r, this->y.p + this->y.r);
}

void ng::Box::scale2 (double s) {
	this->x.scale(s);
	this->y.scale(s);
}

void ng::Box::scale2 (double x, double y) {
	this->x.scale(x);
	this->y.scale(y);
}

// move this by v, and reduce v to 0.
void ng::Box::moveby2 (Vec* const v) {
	this->x.p += v->x;
	this->y.p += v->y;
	v->x = 0.0;
	v->y = 0.0;
}

// move this to p, and reduce v to remaining motion.
void ng::Box::moveto2 (Vec* const v, const Vec* p) {
	double dx, dy;
	dx = p->x - this->x.p;
	dy = p->y - this->y.p;
	this->x.p = p->x;
	this->y.p = p->y;
	v->x -= dx;
	v->y -= dy;
}

bool ng::Box::contains2_rect (double x, double y) const {
	return (this->x.contains(x) && this->y.contains(y));
}

bool ng::Box::overlaps2_rect (const Box* b) const {
	Box k = *b;
	k.x.r += this->x.r;
	k.y.r += this->y.r;
	return k.contains2_rect(this->x, this->y);
}

// true if this will collide with b as a result of movement by v.
bool ng::Box::collides2_rect (const Vec* v, const Box* b) const {
	Box k = *b;
	k.x.r += this->x.r;
	k.y.r += this->y.r;
	return this->intersects2_rect(v, &k);
}

// collide this with b, and reduce v to remaining motion.
// true if this collides with b.
bool ng::Box::collide2_rect (Vec* const v, const Box* b) {
	Box k = *b;
	k.x.r += this->x.r;
	k.y.r += this->y.r;
	return this->intersect2_rect(v, &k);
}

// true if the point vector (this.x, this.y, v.x, v.y) intersects b.
bool ng::Box::intersects2_rect (const Vec* v, const Box* b) const {
	// point vector intersects box if:
	// - point vector overlaps box (x and y range overlap), and
	// - point vector crosses any edge (x or y range intersect).
	Range vx, vy, bx, by;
	vx.init(this->x.p, this->x.p + v->x);
	vy.init(this->y.p, this->y.p + v->y);
	bx.init(b->x.p - b->x.r, b->x.p + b->x.r);
	by.init(b->y.p - b->y.r, b->y.p + b->y.r);
	return ((vx.overlaps(&hx) && vy.overlaps(&hy)) &&
		(vx.intersects(&hx) || vy.intersects(&hy)));
}

// intersect this with b (as defined above), and reduce v to remaining motion.
// true if this intersects b.
bool ng::Box::intersect2_rect (Vec* const v, const Box* b) {
	Vec q;
	q.init(this->x.p, this->y.p);

	Range bx, by;
	bx.init(b->x.p - b->x.r, b->x.p + b->x.r);
	by.init(b->y.p - b->y.r, b->y.p + b->y.r);
	
	bool i = false; // intersection
	Vec p, p1, p2, p3, p4;
	
	// Find closest intersection point.
	p1.y = b->y.p - b->y.r;
	if (p1.xint(&q, v) && bx.contains(p1.x) &&
	(!i || ng::distance_sq(&q, &p1) < ng::distance_sq(&q, &p))) {
		i = true;
		p = p1;
	}
	p2.y = b->y.p + b->y.r;
	if (p2.xint(&q, v) && bx.contains(p2.x) &&
	(!i || ng::distance_sq(&q, &p2) < ng::distance_sq(&q, &p))) {
		i = true;
		p = p2;
	}
	p3.x = b->x.p - b->x.r;
	if (p3.yint(&q, v) && by.contains(p3.y) &&
	(!i || ng::distance_sq(&q, &p3) < ng::distance_sq(&q, &p))) {
		i = true;
		p = p3;
	}
	p4.x = b->x.p + b->x.r;
	if (p4.yint(&q, v) && by.contains(p4.y) &&
	(!i || ng::distance_sq(&q, &p4) < ng::distance_sq(&q, &p))) {
		i = true;
		p = p4;
	}
	
	if (i) { // intersection
		this->moveto2(v, &p);
	} else { // no intersection
		this->moveby2(v);
	}
	return i;
}


