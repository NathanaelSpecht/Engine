
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

Vec2 ng::origin () {
	Vec2 origin(0.0,
	            0.0);
	return origin;
}

Vec2 ng::origin (double x, double y) {
	Vec2 origin(x,
	            y);
	return origin;
}

Mat2 ng::scale () {
	Mat2 scale;
	return scale;
}

Mat2 ng::scale (double i, double j) {
	Mat2 scale(  i, 0.0,
	           0.0,   j);
	return scale;
}

Mat2 ng::scale (const Vec2& dim) {
	Mat2 scale(dim.x,   0.0,
	             0.0, dim.y);
	return scale;
}

double ng::scale (double src, double dest) {
	return dest/src;
}

Mat2 ng::rotate () {
	Mat2 rotate;
	return rotate;
}

Mat2 ng::rotate (double a) {
	double s, c;
	s = std::sin(a);
	c = std::cos(a);
	Mat2 rotate(c,-s,
	            s, c);
	return rotate;
}

// boxes and rects in R2
Box2 ng::box (double x, double y, double rx, double ry) {
	Box2 b(x, y, rx, ry);
	return b;
}

Box2 ng::box (const Vec2& p, const Vec2& dim) {
	Box2 b(p.x, p.y, dim.x, dim.y);
	return b;
}

Rect2 ng::rect (double x, double y, double w, double h) {
	Rect2 r(x, y, w, h);
	return r;
}

Rect2 ng::rect (const Vec2& p, const Vec2& dim) {
	Rect2 r(p.x, p.y, dim.x, dim.y);
	return r;
}

// spaces in R2
Space2 ng::space (double x, double y) {
	Space2 s(x, y, 1.0, 1.0, 0.0);
	return s;
}

Space2 ng::space (double x, double y, double a) {
	Space2 s(x, y, 1.0, 1.0, a);
	return s;
}

Space2 ng::space (double x, double y, double i, double j) {
	Space2 s(x, y, i, j);
	return s;
}

Space2 ng::space (double x, double y, double i, double j, double a) {
	Space2 s(x, y, i, j, a);
	return s;
}

Space2 ng::space (const Vec2& p) {
	Space2 s(p.x, p.y, 1.0, 1.0, 0.0);
	return s;
}

Space2 ng::space (const Vec2& p, double a) {
	Space2 s(p.x, p.y, 1.0, 1.0, a);
	return s;
}

Space2 ng::space (const Vec2& p, const Vec2& dim) {
	Space2 s(p.x, p.y, dim.x, dim.y, 0.0);
	return s;
}

Space2 ng::space (const Vec2& p, const Vec2& dim, double a) {
	Space2 s(p.x, p.y, dim.x, dim.y, a);
	return s;
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

Vec2 operator- (double x) const {
	Vec2 c(this->x-x,
	       this->y-x);
	return c;
}

Vec2 operator- (const Vec2& b) const {
	Vec2 c(this->x-b.x,
	       this->y-b.y);
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

Mat2 ng::Mat2::operator- (double x) const {
	Mat2 C(this->a-x,this->b-x,
	       this->c-x,this->d-x);
	return C;
}

Mat2 ng::Mat2::operator- (const Mat2& B) const {
	Mat2 C(this->a-B.a,this->b-B.b,
	       this->c-B.c,this->d-B.d);
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

// box in R2
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

/*
Vec2 ng::Box2::i () const {
	Vec2 i(this->rx, 0.0);
	return i;
}

Vec2 ng::Box2::j () const {
	Vec2 j(0.0, this->ry);
	return j;
}
*/

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

// rect in R2
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

/*
Vec2 ng::Rect2::i () const {
	Vec2 i(this->w, 0.0);
	return i;
}

Vec2 ng::Rect2::j () const {
	Vec2 j(0.0, this->h);
	return j;
}
*/

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

// space in R2 and matrix representation
ng::Space2::Space2 () :
	x(0.0),
	y(0.0),
	i(1.0),
	j(1.0),
	a(0.0)
{
	this->origin = ng::origin();
	this->scale = ng::scale();
	this->inv_scale = ng::scale();
	this->rotate = ng::rotate();
	this->inv_rotate = ng::rotate();
}

ng::Space2::Space2 (double x, double y, double i, double j, double a) :
	x(x),
	y(y),
	i(i),
	j(j),
	a(a)
{
	this->origin = ng::origin(x, y);
	this->scale = ng::scale(i, j);
	this->inv_scale = ng::inv(this->scale);
	if (a == 0.0) {
		this->rotate = ng::rotate();
		this->inv_rotate = ng::rotate();
	} else {
		this->rotate = ng::rotate(a);
		this->inv_rotate = ng::inv(this->rotate);
	}
}

ng::Space2::Space2 (const Space2& space) :
	x(space.x),
	y(space.y),
	i(space.i),
	j(space.j),
	a(space.a),
	origin(space.origin),
	scale(space.scale),
	inv_scale(space.inv_scale),
	rotate(space.rotate),
	inv_rotate(space.inv_rotate)
{}

// set and recompute.
void ng::Space2::set (double x, double y, double i, double j, double a) {
	this->x = x;
	this->y = y;
	this->i = i;
	this->j = j;
	this->a = a;
	this->origin = ng::origin(x, y);
	this->scale = ng::scale(i, j);
	this->inv_scale = ng::inv(this->scale);
	if (a == 0.0) {
		this->rotate = ng::rotate();
		this->inv_rotate = ng::rotate();
	} else {
		this->rotate = ng::rotate(a);
		this->inv_rotate = ng::inv(this->rotate);
	}
}

// set x and y and recompute origin.
void ng::Space2::set_p (const Vec2& p) {
	this->x = p.x;
	this->y = p.y;
	this->origin = ng::origin(x, y);
}

// set i and j and recompute scale and inv_scale.
void ng::Space2::set_dim (const Vec2& dim) {
	this->i = dim.i;
	this->j = dim.j;
	this->scale = ng::scale(i, j);
	this->inv_scale = ng::inv(this->scale);
}

// set a and recompute rotate and inv_rotate.
void ng::Space2::set_a (double a) {
	this->a = a;
	if (a == 0.0) {
		this->rotate = ng::rotate();
		this->inv_rotate = ng::rotate();
	} else {
		this->rotate = ng::rotate(a);
		this->inv_rotate = ng::inv(this->rotate);
	}
}

// get x and y as p.
Vec2 ng::Space2::p () const {
	Vec2 p(this->x,
	       this->y);
	return p;
}

// get i and j as dim.
Vec2 ng::Space2::dim () const {
	Vec2 dim(this->i,
	         this->j);
	return dim;
}

// get a. (Included for consistency. You don't have to use this)
double ng::Space2::a () const {
	return a;
}

// Remove this space from v. (Make v absolute from space).
// Multiply to remove a space, as you multiply to remove a basis.
Vec2 ng::Space2::operator* (const Vec2& v) const {
	return this->origin+(this->scale*(this->rotate*v));
}

Box2 ng::Space::operator* (const Box2& box) const {
	Vec2 p(this->origin+(this->scale*(this->rotate*box.p())));
	Vec2 dim(this->scale*box.dim());
	return ng::box(p, dim);
}

Rect2 ng::Space::operator* (const Rect2& rect) const {
	Vec2 p(this->origin+(this->scale*(this->rotate*rect.p())));
	Vec2 dim(this->scale*rect.dim());
	return ng::rect(p, dim);
}

double ng::Space2::operator* (double a) const {
	return a+this->a;
}

Space2 ng::Space::operator* (const Space2& space) const {
	Vec2 p(this->origin+(this->scale*(this->rotate*space.p())));
	Vec2 dim(this->scale*space.dim());
	double a(space.a+this->a);
	return ng::space(p, dim, a);
}

// Apply this space to v. (Make v relative to space).
// Divide to apply a space, as you divide (multiply by inverse) to apply a basis.
Vec2 ng::Space2::operator/ (const Vec2& v) const {
	return this->inv_rotate*(this->inv_scale*(v-this->origin));
}

Box2 ng::Space::operator/ (const Box2& box) const {
	Vec2 p(this->inv_rotate*(this->inv_scale*(box.p()-this->origin)));
	Vec2 dim(this->inv_scale*box.dim());
	return ng::box(p, dim);
}

Rect2 ng::Space::operator/ (const Rect2& rect) const {
	Vec2 p(this->inv_rotate*(this->inv_scale*(rect.p()-this->origin)));
	Vec2 dim(this->inv_scale*rect.dim());
	return ng::rect(p, dim);
}

double ng::Space2::operator/ (double a) const {
	return a-this->a;
}

Space2 ng::Space::operator/ (const Space2& space) const {
	Vec2 p(this->inv_rotate*(this->inv_scale*(space.p()-this->origin)));
	Vec2 dim(this->inv_scale*space.dim());
	double a(space.a-this->a);
	return ng::space(p, dim, a);
}

/*
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
*/


