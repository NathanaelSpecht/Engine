
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_vec_init (ngVec* v, int x, int y) {
	v->x = x;
	v->y = y;
}

int ng_contains (int x, int w, int p) {
	if (p < x || x + w < p) {
		return NG_FALSE;
	} else if (p == x || x + w == p) {
		return NG_EDGE;
	} else {
		return NG_TRUE;
	}
}

int ng_overlaps (int x1, int w1, int x2, int w2) {
	if ((x1 + w1 < x2) || (x2 + w2 < x1)) {
		return NG_FALSE;
	} else if ((x1 + w1 == x2) || (x2 + w2 == x1)) {
		return NG_EDGE;
	} else {
		return NG_TRUE;
	}
}

int ng_intercepts (int axis, int x, int d) {
	if ((x > axis && x + d < axis) || (x < axis && x + d > axis)) {
		return NG_TRUE;
	} else if (x + d == axis) {
		return NG_EDGE;
	} else {
		return NG_FALSE;
	}
}

int ng_yintercept (int axis, int x, int y, int dx, int dy) {
	// y = mx + b
	// m = dy/dx
	// b = y-intercept = y - mx
	int x1 = x - axis;
	return y - ((dy * x1) / dx);
}

int ng_xintercept (int axis, int x, int y, int dx, int dy) {
	// x = my + b
	// m = dx/dy
	// b = x-intercept = x - my
	int y1 = y - axis;
	return x - ((dx * y1) / dy);
}

int ng_rect_collides (const ngRect* a, const ngVec* av, const ngRect* b, const ngVec* bv) {
	// return true/edge/false if rects will collide.
	// edge means they will touch and not move any further.
	// assumes rects are not overlapping.
	// obtain b relative to a.
	ngRect o, r; // a -> origin rect o, b -> relative rect r
	ng_rect_init(&o, 0, 0, a->w, a->h);
	ng_rect_init(&r, b->x - a->x, b->y - a->y, b->w, b->h);
	ngVec z, v; // av -> zero vector z, bv -> relative vector v
	ng_vec_init(&z, 0, 0);
	ng_vec_init(&v, bv->x - av->x, bv->y - av->y);
	// where is b in relation to a?
	bool right = o.w < r.x;
	bool left = r.x + r.w < o.x;
	bool below = o.h < r.y;
	bool above = r.y + r.h < o.y;
	// b moving away from a
	if ((right && v.x >= 0) || (left && v.x <= 0) ||
	(below && v.y >= 0) || (above && v.y <= 0)) {
		return NG_FALSE;
	}
	// b moving vaguely towards a, from:
	if (right && below) { // check for 2 side intercepts.
		// if 1 pair of sides miss, other pair might hit, so check both.
		// TODO
	} else if (right && above) {
		// TODO
	} else if (left && below) {
		// TODO
	} else if (left && above) {
		// TODO
	} else if (right) { // check for 1 side intercept.
		// if this pair of sides miss, cannot hit other sides.
		// TODO
	} else if (left) {
		// TODO
	} else if (below) {
		// TODO
	} else if (above) {
		// TODO
	}
	// side pair(s) miss, no collision.
	return NG_FALSE;
}

void ng_rect_collide (ngRect* a, ngVec* av, ngRect* b, ngVec* bv) {
	// move each rect by the part of its vec that gets it to collide, and
	// reduce each vec by the remaining motion.
	// assumes rects are not overlapping and will collide/touch.
	// collision will occur. don't over-engineer for a miss that won't happen.
	// TODO
}


