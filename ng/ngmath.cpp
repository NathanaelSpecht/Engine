
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngmath.h"

int ng::contains (int x, int w, int p) {
	if (p < x || x + w < p) {
		return ng::False;
	} else if (p == x || x + w == p) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng::overlaps (int x1, int w1, int x2, int w2) {
	if ((x1 + w1 < x2) || (x2 + w2 < x1)) {
		return ng::False;
	} else if ((x1 + w1 == x2) || (x2 + w2 == x1)) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng::intercepts (int axis, int x, int d) {
	if ((x > axis && x + d < axis) || (x < axis && x + d > axis)) {
		return ng::True;
	} else if (x + d == axis) {
		return ng::Edge;
	} else {
		return ng::False;
	}
}

int ng::yint (int axis, int x, int y, int dx, int dy) {
	// y = mx + b
	// m = dy/dx
	// b = y-intercept = y - mx
	// cast to int64 to avoid overflow for large x or dy
	int64_t x1, y1, mx;
	int result;
	x1 = static_cast<int64_t>(x - axis);
	y1 = static_cast<int64_t>(y);
	mx = (static_cast<int64_t>(dy) * static_cast<int64_t>(x1)) /
		static_cast<int64_t>(dx);
	result = static_cast<int>(y1 - mx);
	return result;
}

int ng::xint (int axis, int x, int y, int dx, int dy) {
	// x = my + b
	// m = dx/dy
	// b = x-intercept = x - my
	// cast to int64 to avoid overflow for large y or dx
	int64_t x1, y1, my;
	int result;
	x1 = static_cast<int64_t>(x);
	y1 = static_cast<int64_t>(y - axis);
	my = (static_cast<int64_t>(dx) * static_cast<int64_t>(y1)) /
		static_cast<int64_t>(dy);
	result = static_cast<int>(x1 - my);
	return result;
}

int ng::wrap (int x, int m) {
	// given x (-inf, inf) and m [1, inf), produces [0, m).
	// unlike % modulo, does not have strange behavior for x < 0.
	// cast to int64 to avoid overflow
	int64_t x1, m1, y;
	int result;
	x1 = static_cast<int64_t>(x);
	m1 = static_cast<int64_t>(m);
	y = (x1 + (INT64_C(2147483648) * m1)) % m1;
	result = static_cast<int>(y);
	return result;
}

int ng::bhaskara (int x, int r) {
	// Bhaskara I's sine approximation
	// max absolute error is 0.00166, and max relative error is 1.9 percent.
	// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
	// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
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

int ng::qsin (int x, int r) {
	// quick integer sine.
	// given degrees x [0, 360), and radius r (-inf, inf), produces sin(x) [-r, r].
	if (x <= 180) {
		return ng::bhaskara(x, r);
	} else {
		return -ng::bhaskara(x - 180, r);
	}
}

int ng::qcos (int x, int r) {
	// quick integer cosine.
	// given degrees x [0, 360), and radius r (-inf, inf), produces cos(x) [-r, r].
	if (x <= 90) {
		return ng::bhaskara(x + 90, r);
	} else if (x < 270) {
		return -ng::bhaskara(x - 90, r);
	} else {
		return ng::bhaskara(x - 270, r);
	}
}

int ng::sqrt (int64_t x) {
	// integer square root.
	// int wrapper for float sqrt function in math.h
	// assumes x >= 0.
	double x1, y;
	int result;
	x1 = static_cast<double>(x);
	y = std::sqrt(x1);
	result = static_cast<int>(y);
	return result;
}

int64_t ng::sq (int x) {
	// x squared.
	int64_t x1, y;
	x1 = static_cast<int64_t>(x);
	y = x1 * x1;
	return y;
}

int ng::distance_l1 (int x1, int y1, int x2, int y2) {
	// L1 distance, taxicab distance, or manhattan distance.
	return std::abs(x2 - x1) + std::abs(y2 - y1);
}

int64_t ng::distance_sq (int x1, int y1, int x2, int y2) {
	// squared euclidean/pythagorean distance.
	return ng::sq(x2 - x1) + ng::sq(y2 - y1);
}

int ng::distance (int x1, int y1, int x2, int y2) {
	// euclidean/pythagorean distance.
	return ng::sqrt(ng::distance_sq(x1, y1, x2, y2));
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


