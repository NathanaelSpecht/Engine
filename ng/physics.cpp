
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_vec2_init (ngVec* v, int x, int y) {
	v->x = x;
	v->y = y;
	v->w = 1;
}

void ng_vec2w_init (ngVec* v, int x, int y, int w) {
	v->x = x;
	v->y = y;
	v->w = w;
}

void ng_circle_init (ngVec* c, int x, int y, int r) {
	c->x = x;
	c->y = y;
	c->w = r;
}

int ng_contains (int x, int w, int p) {
	if (p < x || x + w < p) {
		return ng::False;
	} else if (p == x || x + w == p) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng_overlaps (int x1, int w1, int x2, int w2) {
	if ((x1 + w1 < x2) || (x2 + w2 < x1)) {
		return ng::False;
	} else if ((x1 + w1 == x2) || (x2 + w2 == x1)) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng_intercepts (int axis, int x, int d) {
	if ((x > axis && x + d < axis) || (x < axis && x + d > axis)) {
		return ng::True;
	} else if (x + d == axis) {
		return ng::Edge;
	} else {
		return ng::False;
	}
}

int ng_yint (int axis, int x, int y, int dx, int dy) {
	// y = mx + b
	// m = dy/dx
	// b = y-intercept = y - mx
	// use int64 for x1 * dy > int32, to avoid overflow.
	int64_t x1, mx;
	x1 = x - axis;
	mx = ((int64_t)dy * x1) / (int64_t)dx;
	return (int)(y - mx);
}

int ng_xint (int axis, int x, int y, int dx, int dy) {
	// x = my + b
	// m = dx/dy
	// b = x-intercept = x - my
	// use int64 for y1 * dx > int32, to avoid overflow.
	int64_t y1, my;
	y1 = y - axis;
	my = ((int64_t)dx * y1) / (int64_t)dy;
	return (int)(x - my);
}

void ng_rect_moveby (ngRect* r, ngVec* v) {
	// move rect by vec, consuming vec in the process (vec -> 0).
	r->x += v->x;
	r->y += v->y;
	v->x = 0;
	v->y = 0;
}

void ng_rect_moveto (ngRect* r, ngVec* v, int x, int y) {
	// move rect to (x, y), and reduce vec to the remaining motion.
	// assumes (x, y) is in the direction of vec.
	int dx = x - r->x;
	int dy = y - r->y;
	r->x += dx;
	r->y += dy;
	v->x -= dx;
	v->y -= dy;
}

int ng_rect_collide (ngRect* a, ngVec* v, const ngRect* b) {
	// return true/edge/false if rect a collided with stationary rect b, and
	// move rect a by the part of its vec v that gets it to collide, and
	// reduce vec v to the remaining motion.
	// edge means they will touch and not move any further.
	// assumes rects are not overlapping.
	// where is a in relation to b?
	bool right = b->x + b->w < a->x;
	bool left = a->x + a->w < b->x;
	bool below = b->y + b->h < a->y;
	bool above = a->y + a->h < b->y;
	// a moving away from b.
	if ((right && v->x >= 0) || (left && v->x <= 0) ||
	(below && v->y >= 0) || (above && v->y <= 0)) {
		ng_rect_moveby(a, v);
		return ng::False;
	}
	// a moving vaguely towards b, from right/left/below/above.
	int result;
	int x, y;
	if (right && ng_intercepts(b->w, a->x, v->x)) {
		y = ng_yint(x = b->w, a->x, a->y, v->x, v->y);
		result = ng_overlaps(b->y, b->h, y, a->h);
		if (result) {
			ng_rect_moveto(a, v, x, y);
			return result;
		}
	}
	if (left && ng_intercepts(b->x, a->x + a->w, v->x)) {
		y = ng_yint(x = b->x, a->x - a->w, a->y, v->x, v->y);
		result = ng_overlaps(b->y, b->h, y, a->h);
		if (result) {
			ng_rect_moveto(a, v, x, y);
			return result;
		}
	}
	if (below && ng_intercepts(b->h, a->y, v->y)) {
		x = ng_xint(y = b->h, a->x, a->y, v->x, v->y);
		result = ng_overlaps(b->x, b->w, x, a->w);
		if (result) {
			ng_rect_moveto(a, v, x, y);
			return result;
		}
	}
	if (above && ng_intercepts(b->y, a->y + a->h, v->y)) {
		x = ng_xint(y = b->y, a->x, a->y - a->h, v->x, v->y);
		result = ng_overlaps(b->x, b->w, x, a->w);
		if (result) {
			ng_rect_moveto(a, v, x, y);
			return result;
		}
	}
	// rects miss, no collision.
	ng_rect_moveby(a, v);
	return ng::False;
}

int ng_wrap_degrees (int x) {
	// given degrees x (-inf, inf), produces angle [0, 359].
	// x + m must be >= 0, so no problems occur during modulo, and
	// m must be a multiple of 360.
	// 0 <= x + m <= max_int32, so
	// max range of x is: -m <= x <= m, while m <= max_int32 / 2.
	int m, y;
	m = 1073741760; // largest multiple of 360 <= max_int32 / 2
	y = (x + m) % 360;
	return y;
}

int ng_bhaskara (int x, int r) {
	// Bhaskara I's sine approximation
	// max absolute error is 0.00165, and max relative error is 1.8 percent.
	// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
	// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
	int p, y;
	p = x * (180 - x);
	y = (4 * p * r) / (40500 - p);
	return y;
}

int ng_qsin (int x, int r) {
	// quick integer sine.
	// given degrees x [0, 359], and radius r (-inf, inf), produces sin(x) [-r, r].
	if (x <= 180) {
		return ng_bhaskara(x, r);
	} else {
		return -ng_bhaskara(x - 180, r);
	}
}

int ng_qcos (int x, int r) {
	// quick integer cosine.
	// given degrees x [0, 359], and radius r (-inf, inf), produces cos(x) [-r, r].
	if (x <= 90) {
		return ng_bhaskara(x + 90, r);
	} else if (x < 270) {
		return -ng_bhaskara(x - 90, r);
	} else {
		return ng_bhaskara(x - 270, r);
	}
}

int ng_sqrt (int64_t x) {
	// integer square root.
	// int wrapper for float sqrt function in math.h
	// assumes x >= 0.
	return (int)sqrt((double)x);
}

int64_t ng_sq (int x) {
	// x squared.
	int64_t lx = x;
	return lx * lx;
}

int ng_distance_l1 (int x1, int y1, int x2, int y2) {
	// L1 distance, taxicab distance, or manhattan distance.
	return abs(x2 - x1) + abs(y2 - y1);
}

int64_t ng_distance_sq (int x1, int y1, int x2, int y2) {
	// squared euclidean/pythagorean distance.
	return ng_sq(x2 - x1) + ng_sq(y2 - y1);
}

int ng_distance (int x1, int y1, int x2, int y2) {
	// euclidean/pythagorean distance.
	return ng_sqrt(ng_distance_sq(x1, y1, x2, y2));
}

int ng_circle_contains (const ngVec* c, int x, int y) {
	// return true/edge/false if circle contains (x, y).
	int64_t r2, d2;
	r2 = ng_sq(c->w);
	d2 = ng_distance_sq(c->x, c->y, x, y);
	if (d2 > r2) {
		return ng::False;
	} else if (d2 == r2) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng_circle_overlaps (const ngVec* a, const ngVec* b) {
	// return true/edge/false if circles overlap/touch.
	int64_t ar2, br2, d2;
	ar2 = ng_sq(a->w);
	br2 = ng_sq(b->w);
	d2 = ng_distance_sq(a->x, a->y, b->x, b->y);
	if (d2 > ar2 + br2) {
		return ng::False;
	} else if (d2 == ar2 + br2) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng_circle_collide (ngVec* a, ngVec* v, const ngVec* b) {
	// return true/edge/false if circle a collided with stationary circle b, and
	// move circle a by the part of its vec v that gets it to collide, and
	// reduce vec v to the remaining motion.
	// edge means they will touch and not move any further.
	// assumes circles are not overlapping.
	// TODO
	return ng::False;
}


