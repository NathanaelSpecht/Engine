
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
	
	// vector in R2 or R3
	class Vec {
	public:
		double x;
		double y;
		//double z; //todo
		
		void init2 (double x, double y);
		
		// Set this to the vector from p1 to p2.
		void init2 (const Vec* p1, const Vec* p2);
		
		// Set this to the scale between relative to src and relative to dest.
		// For example, a virtual camera with one side in game, and other side on screen:
		// - To draw to screen, src in game world and dest on screen.
		// - To get mouse point, src on screen and dest in game world.
		void init2 (const Space* src, const Space* dest);
		void init2 (const Space* src, const Rect* dest);
		void init2 (const Rect* src, const Space* dest);
		void init2 (const Rect* src, const Rect* dest);
		
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
		
		void init2 (double x, double y, double w, double h);
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
		
		void init2 (double x, double y, double w, double h);
		void init2 (const Rect*);
		void init2_c (double x, double y, double w, double h, double c, double r);
		void init2_c (const Rect*, double c, double r);
		void init2_i (double x, double y, double w, double h, double i, double j);
		void init2_i (const Rect*, double i, double j);
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
		
		void init2 (const Rect*, double m);
		void init2 (const Rect*, const Vec*, double m);
		
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


