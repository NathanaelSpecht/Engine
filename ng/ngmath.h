
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGMATH_H
#define NGMATH_H

#include "ngcore.h"

namespace ng {

	// Sides x/y/z may be OR'd together to produce the xy/xz/yz planes.
	// The xyz space is included for completeness.
	// 0 or ng::None means "no sides".
	enum EnumSide {
		SideX = 1,
		SideY = 2,
		SideXY = 3,
		SideZ = 4,
		SideXZ = 5,
		SideYZ = 6,
		SideXYZ = 7
	};

	// For all quick math functions, the following applies:
	//
	// Cycles per instruction across a variety of x86 platforms:
	// Source: www.agner.org/optimize | 4. Instruction tables.
	//
	// Cycles per function approximated from a generalization of the above.
	// For most platforms released last decade (as-of 2022):
	// - if/while is approx. 1 cycle.
	// - int add/subtract is approx. 1 cycle.
	// - int multiply is approx. 3 cycles.
	// - function call/return is approx. 5 cycles.
	// - int32 divide is approx. 15-20 cycles.
	// - int64 divide is approx. 15-50 cycles.
	// - double add/subtract/multiply is approx. 5 cycles.
	// - double divide is approx. 15 cycles.
	// - double sqrt is approx. 20 cycles.
	// - double sin/cos is approx. 50-150 cycles.
	// - double arctan/tan is approx. 100-150 cycles.
	//
	// The "q" at the start of functions means "quick".
	
	
	// given x (-int32, int32) and m [1, int16), produces [0, m).
	// unlike std::mod(x, m), does NOT mirror positive and negative x.
	// adds a multiple of m (say, p) to x, such that x+p >= 0 for any x.
	// equivalent to std::mod(x+p, m).
	int wrap (int x, int m);
	
	double wrap (double x, double m);
	
	// Bhaskara I's sine approximation
	// given degrees x [0, 180], produces sin(x) [0, 1].
	// 35 cycles.
	double bhaskara (double x);
	
	// given degrees x [0, 360], produces sin(x) [-1, 1].
	// 35-40 cycles.
	double qsin (double x);
	
	// given degrees x [0, 360], produces cos(x) [-1, 1].
	// 35-40 cycles.
	double qcos (double x);
	
	// Given x in [x_min, x_max], produce y in [0, 1].
	float normalize (float x, float x_min, float x_max);
	
	// Given x in [0, 1], produce y in [y_min, y_max].
	float denormalize (float x, float y_min, float y_max);
	
	// Force x into the range [x_min, x_max].
	float clamp (float x, float x_min, float x_max);
	
	// Given amplitude [0, 1], produce decibels [-inf, 0].
	float amp_to_dB (float);
	
	// Given decibels [-inf, 0], produce amplitude [0, 1].
	float dB_to_amp (float);
	
	// Convert decibels to amplitude, mix, then convert back to decibels.
	float mix_dB (float, float);
	
	// Given linear volume x [0, 1], produce exponential volume y [0, 1].
	// Multiply decibels by y to apply volume x.
	float dB_volume (float);
	
	float dB_silence ();
	
	double radians (double degrees);
	
	double degrees (double radians);
	
	double units (double columns, double width);
	
	double columns (double units, double width);
	
	double determinant (double a, double b, double c, double d);
	
	double scale (double src_w, double dest_w);
	
	// Represents a point or vector in R2.
	class Vec2 {
	public:
		double x;
		double y;
		
		Vec2 ();
		Vec2 (double x, double y);
		Vec2 (const Vec2* v);
		~Vec2 ();
		
		void set (double x, double y);
		void rotate (double a);
		void rotate (double sina, double cosa);
		void normalize ();
		void normalize (double length);
		double length () const;
		double lengthsq () const;
	};
	
	// Represents a line segment in R2.
	class Line2 {
	public:
		Vec2 p; // p1 = p
		Vec2 v; // p2 = p + v
		
		Line2 ();
		Line2 (double px, double py, double vx, double vy);
		Line2 (const Vec2* p, const Vec2* v);
		Line2 (const Line2* line);
		~Line2 ();
		
		void set (double px, double py, double vx, double vy);
		void set (const Vec2* p, const Vec2* v);
		
		// If this intersects line, return true and set i to intersection point.
		// Else return false.
		bool intersect (const Line2* line, Vec2* const i) const;
	};
	
	// Represents a rectangle in R2.
	class Rect2 {
	public:
		Vec2 p;   // center
		double w; // width
		double h; // height
		double a; // rotation angle, in radians
		
		Rect2 ();
		Rect2 (double x, double y, double w, double h);
		Rect2 (double x, double y, double w, double h, double a);
		Rect2 (const Vec2* p, double w, double h);
		Rect2 (const Vec2* p, double w, double h, double a);
		Rect2 (const Rect2* rect);
		~Rect2 ();
		
		void set (double x, double y, double w, double h);
		void set (double x, double y, double w, double h, double a);
		void set (const Vec2* p, double w, double h);
		void set (const Vec2* p, double w, double h, double a);
		bool contains (double x, double y) const;
		bool contains (const Vec2* p) const;
	};
	
	// Represents a coordinate basis in R2.
	class Basis2 {
	public:
		Vec2 u;
		Vec2 v;
		
		Basis2 ();
		Basis2 (double i, double j);
		Basis2 (double ux, double uy, double vx, double vy);
		Basis2 (const Vec2* u, const Vec2* v);
		Basis2 (const Basis2* basis);
		~Basis2 ();
		
		void set (double i, double j);
		void set (double ux, double uy, double vx, double vy);
		void set (const Vec2* u, const Vec2* v);
		void rescale (double i, double j);
		void rotate (double a);
		void rotate (double sina, double cosa);
		void inverse ();
		void inverse (const Basis2* basis);
	};
	
	// Represents a coordinate space in R2.
	class Space2 {
	public:
		Vec2 p;   // center
		Basis2 basis; // change of basis matrices
		Basis2 inverse;
		double i; // 1 unit along this x and y axis = i and j units in parent basis
		double j;
		double a; // rotation angle from parent space to this space, in radians
		
		Space2 ();
		Space2 (double x, double y);
		Space2 (double x, double y, double a);
		Space2 (double x, double y, double i, double j);
		Space2 (double x, double y, double i, double j, double a);
		Space2 (const Vec2* p);
		Space2 (const Vec2* p, double a);
		Space2 (const Vec2* p, double i, double j);
		Space2 (const Vec2* p, double i, double j, double a);
		Space2 (const Space2* space);
		~Space2 ();
		
		void set (double x, double y);
		void set (double x, double y, double a);
		void set (double x, double y, double i, double j);
		void set (double x, double y, double i, double j, double a);
		void set (const Vec2* p);
		void set (const Vec2* p, double a);
		void set (const Vec2* p, double i, double j);
		void set (const Vec2* p, double i, double j, double a);
		
		// Change from this to parent space.
		void absolute (Vec2* const vec) const;
		void absolute (Line2* const line) const;
		void absolute (Rect2* const rect) const;
		void absolute (Basis2* const basis) const;
		void absolute (Space2* const space) const;
		
		// Change from parent to this space.
		void relative (Vec2* const vec) const;
		void relative (Line2* const line) const;
		void relative (Rect2* const rect) const;
		void relative (Basis2* const basis) const;
		void relative (Space2* const space) const;
	};
	
	// Represents a finite grid in R2.
	class Grid2 {
	public:
		Vec2 p; // top-left corner
		double i;
		double j;
		double c; // columns
		double r; // rows
		
		Grid2 ();
		Grid2 (double i, double j, double c, double r);
		Grid2 (double x, double y, double i, double j, double c, double r);
		Grid2 (const Vec2* p, double i, double j, double c, double r);
		Grid2 (const Grid2* grid);
		~Grid2 ();
		
		void set (double i, double j, double c, double r);
		void set (double x, double y, double i, double j, double c, double r);
		void set (const Vec2* p, double i, double j, double c, double r);
		
		void absolute (Vec2* const vec) const;
		void absolute (Rect2* const rect) const;
		
		void relative (Vec2* const vec) const;
		void relative (Rect2* const rect) const;
	};
	
	
	// vector in R2 or R3
	class Vec {
	public:
		double x;
		double y;
		//double z; //todo
		
		Vec ();
		~Vec ();
		
		void set2 (double x, double y);
		
		// Set this to the vector from p1 to p2.
		void set2 (const Vec* p1, const Vec* p2);
		
		// Set this to the scale between relative to src and relative to dest.
		// For example, a virtual camera with one side in game, and other side on screen:
		// - To draw to screen, src in game world and dest on screen.
		// - To get mouse point, src on screen and dest in game world.
		void set2 (const Space* src, const Space* dest);
		void set2 (const Space* src, const Rect* dest);
		void set2 (const Rect* src, const Space* dest);
		void set2 (const Rect* src, const Rect* dest);
		
		// this - v
		void sub2 (const Vec* v);
		// flip this over side. (see EnumSide)
		void flip2 (int side);
		// this * s
		void scale2 (double s);
		void scale2 (double x, double y);
		
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
		
		// distance from this to p.
		// L1 distance, taxicab distance, or manhattan distance.
		double distance2_l1 (const Vec* p) const;
		// squared euclidean/pythagorean distance.
		double distance2_sq (const Vec* p) const;
		// euclidean/pythagorean distance.
		double distance2 (const Vec* p) const;
		
		// if p+v intersects this axis, then return true and this is intercept.
		// else return false.
		// x-intercept along this y.
		bool xint2 (const Vec* p, const Vec* v);
		// y-intercept along this x.
		bool yint2 (const Vec* p, const Vec* v);
	};
	
	// rectangular area in R2 or volume in R3
	class Rect {
	public:
		double x;
		double y;
		//double z; //todo
		double w;
		double h;
		//double d; //todo
		
		Rect ();
		~Rect ();
		
		void set2 (double x, double y, double w, double h);
		void moveby2 (const Vec*);
		void scale2 (double s);
		void scale2 (double x, double y);
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
		bool contains2 (double x, double y) const;
		bool overlaps2 (const Rect*) const;
		
		// if p+v intersects the edge of this, returns true, and
		// sets vint to the part of v which produces an intersection, and
		// sets side to the intersecting side (see EnumSide).
		// else, returns false, and sets vint to v.
		bool intersect2 (const Vec* p, const Vec* v, Vec* const vint, int* const side) const;
	};
	
	// relative coordinate space parallel to R2 or R3
	class Space {
	public:
		// w=c*i, h=r*j, d=l*k
		Rect rect;
		// columns c/r/l along x/y/z axis
		double c;
		double r;
		//double l; //todo
		// units i/j/k along x/y/z axis
		double i;
		double j;
		//double k; //todo
		// true for constant c/r/l. false for constant i/j/k
		bool const_c;
		
		Space ();
		~Space ();
		
		void set2 (double x, double y, double w, double h);
		void set2 (const Rect*);
		void set2_c (double x, double y, double w, double h, double c, double r);
		void set2_c (const Rect*, double c, double r);
		void set2_i (double x, double y, double w, double h, double i, double j);
		void set2_i (const Rect*, double i, double j);
		void resize2 (double w, double h);
		void scale2 (double s);
		void scale2 (double x, double y);
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
	};
	
	// mass in R2 or R3
	class Mass {
	public:
		Rect rect;
		Vec vec;
		double m;
		
		Mass ();
		~Mass ();
		
		void set2 (double x, double y, double w, double h, double m);
		void set2 (const Rect*, double m);
		void set2 (const Rect*, const Vec*, double m);
		
		void move2 ();
		
		// intersect this rect+vec with r. (see Rect::intersect)
		bool intersect2 (const Rect* r, Vec* const vint, int* const side);
		
		// An inelastic collision without momentum transfer results in a zero vector.
		// Thus, there is no function for this case. Just set vec to (0, 0).
		
		// Quick elastic collision without momentum transfer.
		// qbounce ignores all other possible collisions!
		// For large enough vectors, qbounce can cause this mass to clip through other masses.
		// The code inside qbounce is slightly slower than bounce, but more importantly
		// code which calls qbounce need not check for more intersections along remaining path.
		// Thus, on average qbounce ends up being much faster, and requires less overhead.
		// vint and side are the same parameters returned by intersect.
		void qbounce2 (const Vec* vint, int side);
		
		// Elastic collision without momentum transfer.
		// bounce allows for more collisions along the remaining path of this mass.
		// Code which calls bounce should:
		// - Save this->vec at the first intersection, because bounce will change it
		//   to the remaining path.
		// - Traverse the remaining path, checking for intersections,
		//   doing collisions/bounces, and flipping saved vec after each collision.
		// - After all collisions, call moveby(this->vec), and set this->vec to
		//   the saved vec so this mass continues moving next frame.
		// If that's too much, just call qbounce and live with the janky physics.
		// vint and side are the same parameters returned by intersect.
		void bounce2 (const Vec* vint, int side);
		
		// Inelastic collision with momentum transfer.
		// For when two moving masses collide and stick together, without deformation.
		// For example: you're moving, an object is moving, and you pick it up.
		// 2 versions: one like qbounce and the other like bounce.
		void qcollide2_inelastic (Mass* const);
		void collide2_inelastic (Mass* const);
		
		// Elastic collision with momentum transfer and bounce.
		// For when two moving masses collide and bounce, transfering energy perfectly
		// without deformation.
		// For example: an object hits another object and they ricochet off each other.
		// 2 versions: one like qbounce and the other like bounce.
		void qcollide2_elastic (Mass* const);
		void collide2_elastic (Mass* const);
	};
	
}

#endif


