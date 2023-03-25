
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGMATH_H
#define NGMATH_H

#include "ngcore.h"

namespace ng {
	
	// if (x, y) + (dx, dy) intercepts py axis, find (px, py) and return true.
	// else return false.
	bool xint (int x, int y, int dx, int dy, int* const px, int py);
	
	// if (x, y) + (dx, dy) intercepts px axis, find (px, py) and return true.
	// else return false.
	bool yint (int x, int y, int dx, int dy, int px, int* const py);
	
	// given x (-inf, inf) and m [1, inf), produces [0, m).
	// unlike % modulo, does not have strange behavior for x < 0.
	int wrap (int x, int m);
	
	// Bhaskara I's sine approximation
	// max absolute error is 0.00165, and max relative error is 1.8 percent.
	// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
	// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
	int bhaskara (int x, int r);
	
	// quick integer sine.
	// given degrees x [0, 359], and radius r (-inf, inf), produces sin(x) [-r, r].
	int qsin (int x, int r);
	
	// quick integer cosine.
	// given degrees x [0, 359], and radius r (-inf, inf), produces cos(x) [-r, r].
	int qcos (int x, int r);
	
	// integer square root.
	// int wrapper for float sqrt function in math.h
	// assumes x >= 0.
	int sqrt (int64_t x);
	
	// x squared.
	int64_t sq (int x);
	
	// L1 distance, taxicab distance, or manhattan distance.
	int distance_l1 (int x1, int y1, int x2, int y2);
	
	// squared euclidean/pythagorean distance.
	int64_t distance_sq (int x1, int y1, int x2, int y2);
	
	// euclidean/pythagorean distance.
	int distance (int x1, int y1, int x2, int y2);
	
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
	
	class Range {
	public:
		// after init, a <= b
		int a;
		int b;
		
		void init (int p, int q);
		bool contains (int x) const;
		bool overlaps (const Range*) const;
		
		// true if the vector crosses either edge of this.
		bool intersects (int x, int dx) const;
		
		// true if this crosses either edge of range.
		bool intersects (const Range*) const;
	};
	
}

#endif


