
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGMATH_H
#define NGMATH_H

#include "ngcore.h"

namespace ng {
	
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
	
	// vector in R2 or R3
	class Vec {
	public:
		double x;
		double y;
		//double z; //todo
		
		void init2 (double x, double y);
		void scale2 (double s);
		void scale2 (double x, double y);
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
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
		void scale2 (double s);
		void scale2 (double x, double y);
		void absolute_to_relative2 (const Space*);
		void relative_to_absolute2 (const Space*);
		bool contains2 (double x, double y) const;
		bool overlaps2 (const Rect*) const;
	};
	
	// relative coordinate space parallel to R2 or R3
	class Space {
	public:
		// w=c*i, h=r*j, d=l*k
		Rect rect;
		// n columns/rows/layers along x/y/z axis
		double c;
		double r;
		//double l; //todo
		// u units i/j/k along x/y/z axis
		double i;
		double j;
		//double k; //todo
		
		void init2_n (const Rect*, double c, double r);
		void init2_u (const Rect*, double i, double j);
		void scale2_n (double s);
		void scale2_n (double x, double y);
		void scale2_u (double s);
		void scale2_u (double x, double y);
		void absolute_to_relative2_n (const Space*);
		void absolute_to_relative2_u (const Space*);
		void relative_to_absolute2_n (const Space*);
		void relative_to_absolute2_u (const Space*);
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
		void move2 (const Vec*);
		
		// if this collides with rect, returns true and vec to collision.
		// else, returns false.
		bool collides2 (const Rect*, Vec* const);
		
		// inelastic collision
		void collide2 (const Rect*);
		
		// inelastic collision with momentum transfer
		void collide2 (Mass* const);
	};
	
}

#endif


