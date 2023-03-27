
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGMATH_H
#define NGMATH_H

#include "ngcore.h"

namespace ng {
	
	bool intersects (int x, int dx, int axis);
	bool intersects (double x, double dx, double axis);
	
	// given x (-inf, inf) and m [1, inf), produces [0, m).
	// unlike mod(x, m), does NOT mirror x over y-axis.
	// eg: for m=360, wrap(-359)=1, wrap(-1)=359, wrap(1)=1, wrap(359)=359.
	int wrap (int x, int m);
	double wrap (double x, double m);
	
	// Bhaskara I's sine approximation
	// max absolute error is 0.00165, and max relative error is 1.8 percent.
	// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
	// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
	int bhaskara (int x, int r);
	
	// given degrees x [0, 180], produces sin(x) [0, 1].
	double bhaskara (double x);
	
	// quick integer sine.
	// given degrees x [0, 360), and radius r (-inf, inf), produces sin(x) [-r, r].
	int qsin (int x, int r);
	
	// given degrees x [0, 360), produces sin(x) [-1, 1].
	double qsin (double x);
	
	// quick integer cosine.
	// given degrees x [0, 360), and radius r (-inf, inf), produces cos(x) [-r, r].
	int qcos (int x, int r);
	
	// given degrees x [0, 360), produces cos(x) [-1, 1].
	double qcos (double x);
	
	// integer square root.
	// int wrapper for float sqrt function in math.h
	// assumes x >= 0.
	int sqrt (int64_t x);
	
	// x squared.
	int64_t sq (int x);
	
	// L1 distance, taxicab distance, or manhattan distance.
	int distance_l1 (const Vec* p1, const Vec* p2);
	double distance_l1 (const Vec* p1, const Vec* p2);
	
	// squared euclidean/pythagorean distance.
	int distance_sq (const Vec* p1, const Vec* p2);
	double distance_sq (const Vec* p1, const Vec* p2);
	
	// euclidean/pythagorean distance.
	int distance (const Vec* p1, const Vec* p2);
	double distance (const Vec* p1, const Vec* p2);
	
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
	
	double scale (const Range* src, const Range* dest);
	double scale (const Range* src, const Axis* dest);
	double scale (const Axis* src, const Range* dest);
	double scale (const Axis* src, const Axis* dest);
	
	class Range {
	public:
		// a inclusive to b exclusive [a, b), b-a=length
		// after init, a <= b
		double a;
		double b;
		
		void init (int p, int q);
		void init (double p, double q);
		
		// a*=s, b*=s
		void scale (double s);
		
		void absolute_to_relative (const Axis*);
		void relative_to_absolute (const Axis*);
		
		bool contains (int x) const;
		bool contains (double x) const;
		bool overlaps (const Range*) const;
		
		// true if the vector crosses either edge of this.
		bool intersects (int x, int dx) const;
		bool intersects (double x, double dx) const;
		
		// true if this crosses either edge of range.
		bool intersects (const Range*) const;
	};
	
	// range containing a relative coordinate axis
	class Axis {
	public:
		// absolute a inclusive to b exclusive [a, b), b-a=n*u
		// relative number of units n, absolute size of unit u
		// after init, a <= b
		double a;
		double b;
		double n;
		double u;
		
		// n=b-a, u=1
		void init (int p, int q);
		void init (double p, double q);
		
		// u=(b-a)/n
		void init_n (double p, double q, double n);
		
		// n=(b-a)/u
		void init_u (double p, double q, double u);
		
		// 2 ways to scale axis such that (b-a)*s = (n*u)*s
		// scale n, keeping u constant. a*=s, b*=s, n*=s
		void scale_n (double s);
		
		// scale u, keeping n constant. a*=s, b*=s, u*=s
		void scale_u (double s);
		
		void absolute_to_relative_n (const Axis*);
		void absolute_to_relative_u (const Axis*);
		void relative_to_absolute_n (const Axis*);
		void relative_to_absolute_u (const Axis*);
	};
	
	// range with center and radius
	class Diameter {
	public:
		double p;
		double r;
		
		void init (int p, int r);
		void init (double p, double r);
		
		// p*=s, r*=s
		void scale (double s);
		
		void absolute_to_relative (const Axis*);
		void relative_to_absolute (const Axis*);
		
		bool contains (int x) const;
		bool contains (double x) const;
		bool overlaps (const Diameter*) const;
		
		// true if the vector crosses either edge of this.
		bool intersects (int x, int dx) const;
		bool intersects (double x, double dx) const;
		
		// true if this crosses either edge of diameter.
		bool intersects (const Diameter*) const;
	};
	
	// vector in R2 and R3
	class Vec {
	public:
		double x;
		double y;
		//double z; //todo
		
		void init2 (int x, int y);
		void init2 (double x, double y);
		
		void scale2 (double s);
		void scale2 (double x, double y);
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
		
		// if p + v intercepts y axis in R2, find this and return true.
		// else return false.
		bool xint2 (const Vec* p, const Vec* v);
		
		// if p + v intercepts x axis in R2, find this and return true.
		// else return false.
		bool yint2 (const Vec* p, const Vec* v);
		
		// L1/taxicab/manhattan distance in R2.
		int len2_l1 () const;
		double len2_l1 () const;
		
		// squared distance in R2.
		int64_t len2_sq () const;
		double len2_sq () const;
		
		// distance in R2.
		int len2 () const;
		double len2 () const;
	};
	
	// rect in R2 and R3
	class Rect {
	public:
		Range x;
		Range y;
		//Range z; //todo
		
		void init2 (int x1, int y1, int x2, int y2);
		void init2 (double x1, double y1, double x2, double y2);
		void init2 (const Range* x, const Range* y);
		
		void scale2 (double s);
		void scale2 (double x, double y);
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
		
		bool contains2 (int x, int y) const;
		bool contains2 (double x, double y) const;
	};
	
	// rect containing a relative coordinate space in R2 and R3
	class Space {
	public:
		Axis x;
		Axis y;
		//Axis z; //todo
		
		void init2 (int x1, int y1, int x2, int y2);
		void init2 (double x1, double y1, double x2, double y2);
		void init2_n (const Rect*, double n);
		void init2_n (const Rect*, double nx, double ny);
		void init2_u (const Rect*, double u);
		void init2_u (const Rect*, double ux, double uy);
		void init2 (const Axis* x, const Axis* y);
		
		void scale2_n (double s);
		void scale2_n (double x, double y);
		void scale2_u (double s);
		void scale2_u (double x, double y);
		void absolute_to_relative2_n (const Space*);
		void absolute_to_relative2_u (const Space*);
		void relative_to_absolute2_n (const Space*);
		void relative_to_absolute2_u (const Space*);
	};
	
	// box with center and radius in R2 or R3
	class Box {
	public:
		Diameter x;
		Diameter y;
		//Diameter z; //todo
		
		void init2 (int x, int y, int a, int b);
		void init2 (double x, double y, double a, double b);
		void init2 (const Rect*);
		
		// get a rect for drawing this box.
		void get_rect2 (Rect* const) const;
		
		void scale2 (double s);
		void scale2 (double x, double y);
		
		// move this by v, and reduce v to 0.
		void moveby2 (Vec* const v);
		
		// move this to p, and reduce v to remaining motion.
		void moveto2 (Vec* const v, const Vec* p);
		
		bool contains2_rect (double x, double y) const;
		bool overlaps2_rect (const Box* b) const;
		
		// true if this will collide with b as a result of movement by v.
		bool collides2_rect (const Vec* v, const Box* b) const;
		
		// collide this with b, and reduce v to remaining motion.
		// true if this collides with b.
		bool collide2_rect (Vec* const v, const Box* b);
		
		// true if the point vector (this.x, this.y, v.x, v.y) intersects b.
		bool intersects2_rect (const Vec* v, const Box* b) const;
		
		// intersect this with b (as defined above), and reduce v to remaining motion.
		// true if this intersects b.
		bool intersect2_rect (Vec* const v, const Box* b);
	};
	
}

#endif


