
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGMATH_H
#define NGMATH_H

#include "ngcore.h"

namespace ng {
	
	// if (x, y) + (dx, dy) intercepts py axis, find (px, py) and return true.
	// else return false.
	bool xint (int x, int y, int dx, int dy, int* const px, int py);
	bool xint (double x, double y, double dx, double dy, double* const px, double py);
	
	// if (x, y) + (dx, dy) intercepts px axis, find (px, py) and return true.
	// else return false.
	bool yint (int x, int y, int dx, int dy, int px, int* const py);
	bool yint (double x, double y, double dx, double dy, double px, double* const py);
	
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
	int distance_l1 (int x1, int y1, int x2, int y2);
	double distance_l1 (double x1, double y1, double x2, double y2);
	
	// squared euclidean/pythagorean distance.
	int64_t distance_sq (int x1, int y1, int x2, int y2);
	double distance_sq (double x1, double y1, double x2, double y2);
	
	// euclidean/pythagorean distance.
	int distance (int x1, int y1, int x2, int y2);
	double distance (double x1, double y1, double x2, double y2);
	
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
		
		bool contains (int x) const;
		bool contains (double x) const;
		bool overlaps (const Range*) const;
		bool overlaps (const Axis*) const;
		
		// true if the vector crosses either edge of this.
		bool intersects (int x, int dx) const;
		bool intersects (double x, double dx) const;
		
		// true if this crosses either edge of range.
		bool intersects (const Range*) const;
		bool intersects (const Axis*) const;
		
		void absolute_to_relative (const Range*);
		void absolute_to_relative (const Axis*);
		void relative_to_absolute (const Range*);
		void relative_to_absolute (const Axis*);
	};
	
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
		
		bool contains (int x) const;
		bool contains (double x) const;
		bool overlaps (const Range*) const;
		bool overlaps (const Axis*) const;
		
		// true if the vector crosses either edge of this.
		bool intersects (int x, int dx) const;
		bool intersects (double x, double dx) const;
		
		// true if this crosses either edge of range.
		bool intersects (const Range*) const;
		bool intersects (const Axis*) const;
		
		void absolute_to_relative (const Range*);
		void absolute_to_relative_n (const Axis*);
		void absolute_to_relative_u (const Axis*);
		void relative_to_absolute (const Range*);
		void relative_to_absolute_n (const Axis*);
		void relative_to_absolute_u (const Axis*);
	};
	
}

#endif


