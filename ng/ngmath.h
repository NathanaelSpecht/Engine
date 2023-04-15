
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
	
}

#endif


