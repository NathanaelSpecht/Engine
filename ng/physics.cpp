
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

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

void ng::Vec::init_2d (int x, int y) {
	this->x = x;
	this->y = y;
	this->z = 0;
	this->w = 1;
}

void ng::Vec::init_2d (int x, int y, int w) {
	this->x = x;
	this->y = y;
	this->z = 0;
	this->w = w;
}

void ng::Vec::init_3d (int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}

void ng::Vec::init_3d (int x, int y, int z, int w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void ng::Circle::init (int x, int y, int r) {
	this->x = x;
	this->y = y;
	this->r = r;
}

int ng::Circle::contains (int x, int y) const {
	// return true/edge/false if circle contains (x, y).
	int64_t r2, d2;
	r2 = ng::sq(this->r);
	d2 = ng::distance_sq(this->x, this->y, x, y);
	if (d2 > r2) {
		return ng::False;
	} else if (d2 == r2) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng::Circle::overlaps (const Circle* b) const {
	// return true/edge/false if circles overlap/touch.
	int64_t ar2, br2, d2;
	ar2 = ng::sq(this->r);
	br2 = ng::sq(b->r);
	d2 = ng::distance_sq(this->x, this->y, b->x, b->y);
	if (d2 > ar2 + br2) {
		return ng::False;
	} else if (d2 == ar2 + br2) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng::Circle::collide (Vec* const v, const Circle* b) {
	// return true/edge/false if circle a collided with stationary circle b, and
	// move circle a by the part of its vec v that gets it to collide, and
	// reduce vec v to the remaining motion.
	// edge means they will touch and not move any further.
	// assumes circles are not overlapping.
	// TODO
	return ng::False;
}

void ng::Rect::init (int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void ng::Rect::get_SDL_Rect (SDL_Rect* const r) const {
	r->x = this->x;
	r->y = this->y;
	r->w = this->w;
	r->h = this->h;
}

int ng::Rect::contains (int x, int y) const {
	int xc = ng::contains(this->x, this->w, x);
	int yc = ng::contains(this->y, this->h, y);
	if (!xc || !yc) {
		return ng::False;
	} else if (xc == ng::Edge || yc == ng::Edge) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

int ng::Rect::overlaps (const Rect* r2) const {
	int xo = ng::overlaps(this->x, this->w, r2->x, r2->w);
	int yo = ng::overlaps(this->y, this->h, r2->y, r2->h);
	if (!xo || !yo) {
		return ng::False;
	} else if (xo == ng::Edge || yo == ng::Edge) {
		return ng::Edge;
	} else {
		return ng::True;
	}
}

void ng::Rect::absolute_to_relative (const Rect* rel_rect, const Grid* rel_grid) {
	if (rel_rect != NULL) {
		this->x = this->x - rel_rect->x;
		this->y = this->y - rel_rect->y;
	}
	if (rel_grid != NULL) {
		this->x = (int)(this->x / rel_grid->tile_w);
		this->y = (int)(this->y / rel_grid->tile_h);
		this->w = (int)(this->w / rel_grid->tile_w);
		this->h = (int)(this->h / rel_grid->tile_h);
	}
}

void ng::Rect::relative_to_absolute (const Rect* rel_rect, const Grid* rel_grid) {
	if (rel_grid != NULL) {
		this->x = (int)(this->x * rel_grid->tile_w);
		this->y = (int)(this->y * rel_grid->tile_h);
		this->w = (int)(this->w * rel_grid->tile_w);
		this->h = (int)(this->h * rel_grid->tile_h);
	}
	if (rel_rect != NULL) {
		this->x = this->x + rel_rect->x;
		this->y = this->y + rel_rect->y;
	}
}

void ng::Rect::portal (const Rect* src, const Rect* dest) {
	this->absolute_to_relative(src, NULL);
	// convert relative coord spaces: src to dest
	// r.x' / r.x = dest.w / src.w --> r.x' = (dest.w / src.w) * r.x
	float scale_x = (float)dest->w / src->w;
	float scale_y = (float)dest->h / src->h;
	this->x = (int)(scale_x * this->x);
	this->y = (int)(scale_y * this->y);
	this->w = (int)(scale_x * this->w);
	this->h = (int)(scale_y * this->h);
	this->relative_to_absolute(dest, NULL);
}

void ng::Rect::moveby (Vec* const v) {
	// move rect by vec, consuming vec in the process (vec -> 0).
	this->x += v->x;
	this->y += v->y;
	v->x = 0;
	v->y = 0;
}

void ng::Rect::moveto (Vec* const v, int x, int y) {
	// move rect to (x, y), and reduce vec to the remaining motion.
	// assumes (x, y) is in the direction of vec.
	int dx = x - this->x;
	int dy = y - this->y;
	this->x += dx;
	this->y += dy;
	v->x -= dx;
	v->y -= dy;
}

int ng::Rect::collide (Vec* const v, const Rect* b) {
	// return true/edge/false if rect a collided with stationary rect b, and
	// move rect a by the part of its vec v that gets it to collide, and
	// reduce vec v to the remaining motion.
	// edge means they will touch and not move any further.
	// assumes rects are not overlapping.
	// where is a in relation to b?
	bool right = b->x + b->w < this->x;
	bool left = this->x + this->w < b->x;
	bool below = b->y + b->h < this->y;
	bool above = this->y + this->h < b->y;
	// a moving away from b.
	if ((right && v->x >= 0) || (left && v->x <= 0) ||
	(below && v->y >= 0) || (above && v->y <= 0)) {
		this->moveby(v);
		return ng::False;
	}
	// a moving vaguely towards b, from right/left/below/above.
	int x, y, result;
	if (right && ng::intercepts(b->w, this->x, v->x)) {
		x = b->w;
		y = ng::yint(x, this->x, this->y, v->x, v->y);
		result = ng::overlaps(b->y, b->h, y, this->h);
		if (result) {
			this->moveto(v, x, y);
			return result;
		}
	}
	if (left && ng::intercepts(b->x, this->x + this->w, v->x)) {
		x = b->x;
		y = ng::yint(x, this->x - this->w, this->y, v->x, v->y);
		result = ng::overlaps(b->y, b->h, y, this->h);
		if (result) {
			this->moveto(v, x, y);
			return result;
		}
	}
	if (below && ng::intercepts(b->h, this->y, v->y)) {
		y = b->h;
		x = ng::xint(y, this->x, this->y, v->x, v->y);
		result = ng::overlaps(b->x, b->w, x, this->w);
		if (result) {
			this->moveto(v, x, y);
			return result;
		}
	}
	if (above && ng::intercepts(b->y, this->y + this->h, v->y)) {
		y = b->y;
		x = ng::xint(y, this->x, this->y - this->h, v->x, v->y);
		result = ng::overlaps(b->x, b->w, x, this->w);
		if (result) {
			this->moveto(v, x, y);
			return result;
		}
	}
	// rects miss, no collision.
	this->moveby(v);
	return ng::False;
}


