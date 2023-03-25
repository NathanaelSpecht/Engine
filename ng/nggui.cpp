
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggui.h"
#include "ngmath.h"

/*
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
	// a collides with b when (a.x, a.y) is within a.r + b.r of (b.x, b.y).
	// -> when (a.x, a.y) intersects circle c (b.x, b.y, a.r + b.r).
	
	return ng::False;
}
*/

/*
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
*/

void ng::Canvas::init_root (Graphics* graphics) {
	this->graphics = graphics;
	this->parent = NULL;
	this->mode = ng::CanvasRoot;
	this->rect = graphics->rect;
	this->grid.init(&graphics->rect);
	//this->scale.init();
}

void ng::Canvas::init (Canvas* canvas, const Rect* rect) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->mode = ng::CanvasRect;
	this->rect = *rect;
	this->grid.init(rect);
	//this->scale.init();
}

void ng::Canvas::init (Canvas* canvas, const Rect* rect, const Grid* grid) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->mode = ng::CanvasGrid;
	this->rect = *rect;
	this->grid = *grid;
	//this->scale.init();
}

void ng::Canvas::init_scale (Canvas* canvas, const Rect* rect) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->mode = ng::CanvasScale;
	this->rect = *rect;
	this->grid.init(rect);
	//this->scale.init();
}

/*
void ng::Canvas::set_grid (const Grid* grid) {
	this->use_grid = true;
	this->grid = *grid;
}
*/

/*
void ng::Canvas::set_scale (const Scale* s) {
	this->use_scale = true;
	this->scale = *s;
}
*/

/*
void ng::Canvas::remove_grid () {
	this->use_grid = false;
}
*/

/*
void ng::Canvas::remove_scale () {
	this->use_scale = false;
}
*/

/*
// re-calculate scale between this rect and parent rect.
void ng::Canvas::rescale () {
	if (this->root) {
		this->use_scale = false;
	} else {
		this->use_scale = true;
		if (this->parent->root) {
			this->scale.init(&this->rect, &this->graphics->rect);
		} else {
			this->scale.init(&this->rect, &this->parent->rect);
		}
	}
}
*/

// Given event mouse point on root canvas, find mouse point on this canvas.
void ng::Canvas::get_mouse (Vec* const mouse) {
	switch (this->mode) {
		case ng::CanvasScale: {
			this->parent->get_mouse(mouse);
			if (this->parent->mode == ng::CanvasRoot) {
				mouse->portal(&this->graphics->rect, &this->rect);
			} else {
				mouse->portal(&this->parent->rect, &this->rect);
			}
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			this->parent->get_mouse(mouse);
			mouse->absolute_to_relative(&this->rect);
			if (this->mode == ng::CanvasGrid) {
				mouse->absolute_to_relative(&this->grid);
			}
			break;
			
		} default: {}
	}
}

// Draw this->rect on parent.
// Clearing root canvas calls graphics clear().
void ng::Canvas::clear () {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->clear();
			break;
			
		} case ng::CanvasScale: {
			this->parent->clear();
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			this->parent->draw_rect(&this->rect, ng::DrawFill);
			break;
			
		} default: {}
	}
}

void ng::Canvas::clear (int draw) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->clear();
			break;
			
		} case ng::CanvasScale: {
			this->parent->clear(draw);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			this->parent->draw_rect(&this->rect, draw);
			break;
			
		} default: {}
	}
}

// Usually does nothing.
// Drawing root canvas calls graphics draw().
void ng::Canvas::draw () {
	if (this->mode == ng::CanvasRoot) {
		this->graphics->draw();
	}
}

void ng::Canvas::draw_text (Tileset* const tileset, const char* str,
const Rect* textbox, const Grid* textgrid) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->draw_text(tileset, str, textbox, textgrid);
			break;
			
		} case ng::CanvasScale: {
			Rect tb = *textbox;
			Grid g = *textgrid;
			if (this->parent->mode == ng::CanvasRoot) {
				tb.portal(&this->rect, &this->graphics->rect);
				g.portal(&this->rect, &this->graphics->rect);
			} else {
				tb.portal(&this->rect, &this->parent->rect);
				g.portal(&this->rect, &this->parent->rect);
			}
			this->parent->draw_text(tileset, str, &tb, &g);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			Rect tb = *textbox;
			Grid g = *textgrid;
			if (this->mode == ng::CanvasGrid) {
				tb.relative_to_absolute(&this->grid);
				g.relative_to_absolute(&this->grid);
			}
			tb.relative_to_absolute(&this->rect);
			this->parent->draw_text(tileset, str, &tb, &g);
			break;
			
		} default: {}
	}
}

void ng::Canvas::draw_tile (Tileset* const tileset, const Rect* src, const Rect* dest) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->draw_tile(tileset, src, dest);
			break;
			
		} case ng::CanvasScale: {
			Rect d = *dest;
			if (this->parent->mode == ng::CanvasRoot) {
				d.portal(&this->rect, &this->graphics->rect);
			} else {
				d.portal(&this->rect, &this->parent->rect);
			}
			this->parent->draw_tile(tileset, src, &d);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			Rect d = *dest;
			if (this->mode == ng::CanvasGrid) {
				d.relative_to_absolute(&this->grid);
			}
			d.relative_to_absolute(&this->rect);
			this->parent->draw_tile(tileset, src, &d);
			break;
			
		} default: {}
	}
}

void ng::Canvas::draw_image (Image* const image) {
	if (this->mode == ng::CanvasRoot) {
		this->graphics->draw_image(image);
	} else {
		this->draw_image(image, &image->rect, &this->rect);
	}
}

void ng::Canvas::draw_image (Image* const image, const Rect* dest) {
	if (this->mode == ng::CanvasRoot) {
		this->graphics->draw_image(image, dest);
	} else {
		this->draw_image(image, &image->rect, dest);
	}
}

void ng::Canvas::draw_image (Image* const image, const Rect* src, const Rect* dest) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->draw_image(image, src, dest);
			break;
			
		} case ng::CanvasScale: {
			Rect d = *dest;
			if (this->parent->mode == ng::CanvasRoot) {
				d.portal(&this->rect, &this->graphics->rect);
			} else {
				d.portal(&this->rect, &this->parent->rect);
			}
			this->parent->draw_image(image, src, &d);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			Rect d = *dest;
			if (this->mode == ng::CanvasGrid) {
				d.relative_to_absolute(&this->grid);
			}
			d.relative_to_absolute(&this->rect);
			this->parent->draw_image(image, src, &d);
			break;
			
		} default: {}
	}
}

void ng::Canvas::draw_rect (const Rect* dest, int draw) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->draw_rect(dest, draw);
			break;
			
		} case ng::CanvasScale: {
			Rect d = *dest;
			if (this->parent->mode == ng::CanvasRoot) {
				d.portal(&this->rect, &this->graphics->rect);
			} else {
				d.portal(&this->rect, &this->parent->rect);
			}
			this->parent->draw_rect(&d, draw);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			Rect d = *dest;
			if (this->mode == ng::CanvasGrid) {
				d.relative_to_absolute(&this->grid);
			}
			d.relative_to_absolute(&this->rect);
			this->parent->draw_rect(&d, draw);
			break;
			
		} default: {}
	}
}

void ng::Canvas::draw_line (int x1, int y1, int x2, int y2) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->draw_line(x1, y1, x2, y2);
			break;
			
		} case ng::CanvasScale: {
			Vec v1, v2;
			v1.init(x1, y1);
			v2.init(x2, y2);
			if (this->parent->mode == ng::CanvasRoot) {
				v1.portal(&this->rect, &this->graphics->rect);
				v2.portal(&this->rect, &this->graphics->rect);
			} else {
				v1.portal(&this->rect, &this->parent->rect);
				v2.portal(&this->rect, &this->parent->rect);
			}
			this->parent->draw_line(v1.x, v1.y, v2.x, v2.y);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			Vec v1, v2;
			v1.init(x1, y1);
			v2.init(x2, y2);
			if (this->mode == ng::CanvasGrid) {
				v1.relative_to_absolute(&this->grid);
				v2.relative_to_absolute(&this->grid);
			}
			v1.relative_to_absolute(&this->rect);
			v2.relative_to_absolute(&this->rect);
			this->parent->draw_line(v1.x, v1.y, v2.x, v2.y);
			break;
			
		} default: {}
	}
}

void ng::Canvas::draw_point (int x, int y) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			this->graphics->draw_point(x, y);
			break;
			
		} case ng::CanvasScale: {
			Vec v;
			v.init(x, y);
			if (this->parent->mode == ng::CanvasRoot) {
				v.portal(&this->rect, &this->graphics->rect);
			} else {
				v.portal(&this->rect, &this->parent->rect);
			}
			this->parent->draw_point(v.x, v.y);
			break;
			
		} case ng::CanvasRect: case ng::CanvasGrid: {
			Vec v;
			v.init(x, y);
			if (this->mode == ng::CanvasGrid) {
				v.relative_to_absolute(&this->grid);
			}
			v.relative_to_absolute(&this->rect);
			this->parent->draw_point(v.x, v.y);
			break;
			
		} default: {}
	}
}


