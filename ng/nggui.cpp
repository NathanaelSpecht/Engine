
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggui.h"
#include "ngmath.h"

void ng::Hitbox::init (int x, int y, int a, int b) {
	this->x = x;
	this->y = y;
	this->a = a;
	this->b = b;
	this->shape = ng::ShapeRect;
}

void ng::Hitbox::init (const Rect* rect) {
	this->a = rect->w / 2;
	this->b = rect->h / 2;
	this->x = rect->x + this->a;
	this->y = rect->y + this->b;
	this->shape = ng::ShapeRect;
}

void ng::Hitbox::init (const Rect* rect, const Grid* grid, int column, int row) {
	this->a = static_cast<int>(grid->tile_w);
	this->b = static_cast<int>(grid->tile_h);
	this->x = (rect->x + (column * this->a * 2)) + this->a;
	this->y = (rect->y + (row * this->b * 2)) + this->b;
	this->shape = ng::ShapeRect;
}

int ng::Hitbox::major () const {
	if (this->a >= this->b) {
		return this->a;
	} else {
		return this->b;
	}
}

int ng::Hitbox::minor () const {
	if (this->a >= this->b) {
		return this->b;
	} else {
		return this->a;
	}
}

// get a graphics rect for drawing this hitbox.
void ng::Hitbox::get_rect (Rect* const rect) const {
	rect->x = this->x - this->a;
	rect->y = this->y - this->b;
	rect->w = this->a * 2;
	rect->h = this->b * 2;
}

void ng::Hitbox::scale (const Scale* s) {
	this->x *= s->x;
	this->y *= s->y;
	this->a *= s->x;
	this->b *= s->y;
}

void ng::Hitbox::scale_inv (const Scale* s) {
	this->x *= s->x_inv;
	this->y *= s->y_inv;
	this->a *= s->x_inv;
	this->b *= s->y_inv;
}

// Generic Hitbox:
// If shapes are the same, it will use the correct collider.
// If shapes are different, it uses the collider for the larger shape.
int ng::Hitbox::get_shape (const Hitbox* h) const {
	int shape;
	if (this->shape == h->shape) {
		shape = this->shape;
	} else {
		int tsize, hsize;
		tsize = this->a * this->b * 4;
		hsize = h->a * h->b * 4;
		if (tsize >= hsize) {
			shape = this->shape;
		} else {
			shape = h->shape;
		}
	}
	return shape;
}

// true if this contains (x, y).
bool ng::Hitbox::contains (int x, int y) const {
	switch (this->shape) {
		case ng::ShapeEllipse: {
			return (this->ellipse_contains(x, y));
			break;
		} case ng::ShapeRect: default: {
			return (this->rect_contains(x, y));
		}
	}
}

// true if this overlaps h.
bool ng::Hitbox::overlaps (const Hitbox* h) const {
	int shape = this->get_shape(h);
	switch (shape) {
		case ng::ShapeEllipse: {
			return (this->ellipse_overlaps(h));
			break;
		} case ng::ShapeRect: default: {
			return (this->rect_overlaps(h));
		}
	}
}

// true if this will collide with h as a result of movement by v.
bool ng::Hitbox::collides (const Vec* v, const Hitbox* h) const {
	int shape = this->get_shape(h);
	switch (shape) {
		case ng::ShapeEllipse: {
			return (this->ellipse_collides(v, h));
			break;
		} case ng::ShapeRect: default: {
			return (this->rect_collides(v, h));
		}
	}
}

// collide this with h, and reduce v to remaining motion.
// true if this collides with h.
bool ng::Hitbox::collide (Vec* const v, const Hitbox* h) {
	int shape = this->get_shape(h);
	switch (shape) {
		case ng::ShapeEllipse: {
			return (this->ellipse_collide(v, h));
			break;
		} case ng::ShapeRect: default: {
			return (this->rect_collide(v, h));
		}
	}
}

// true if the point vector (this.x, this.y, v.x, v.y) intersects h.
bool ng::Hitbox::intersects (const Vec* v, const Hitbox* h) const {
	int shape = this->get_shape(h);
	switch (shape) {
		case ng::ShapeEllipse: {
			return (this->ellipse_intersects(v, h));
			break;
		} case ng::ShapeRect: default: {
			return (this->rect_intersects(v, h));
		}
	}
}

// intersect this with h (as defined above), and reduce v to remaining motion.
// true if this intersects h.
bool ng::Hitbox::intersect (Vec* const v, const Hitbox* h) {
	int shape = this->get_shape(h);
	switch (shape) {
		case ng::ShapeEllipse: {
			return (this->ellipse_intersect(v, h));
			break;
		} case ng::ShapeRect: default: {
			return (this->rect_intersect(v, h));
		}
	}
}

bool ng::Hitbox::rect_contains (int x, int y) const {
	if (x < this->x - this->a || x > this->x + this->a ||
	y < this->y - this->b || y > this->y + this->b) {
		return false;
	} else {
		return true;
	}
}

bool ng::Hitbox::rect_overlaps (const Hitbox* h) const {
	Hitbox k = *h;
	k.a += this->a;
	k.b += this->b;
	return k.rect_contains(this->x, this->y);
}

bool ng::Hitbox::rect_collides (const Vec* v, const Hitbox* h) const {
	Hitbox k = *h;
	k.a += this->a;
	k.b += this->b;
	return (this->rect_intersects(v, &k));
}

bool ng::Hitbox::rect_collide (Vec* const v, const Hitbox* h) {
	Hitbox k = *h;
	k.a += this->a;
	k.b += this->b;
	return (this->rect_intersect(v, &k));
}

bool ng::Hitbox::rect_intersects (const Vec* v, const Hitbox* h) const {
	// point vector intersects box if:
	// - point vector overlaps box (x and y range overlap), and
	// - point vector crosses any edge (x or y range intersect).
	Range rx, ry, hx, hy;
	rx.init(this->x, this->x + v->x);
	ry.init(this->y, this->y + v->y);
	hx.init(h->x - h->a, h->x + h->a);
	hy.init(h->y - h->b, h->y + h->b);
	return ((rx.overlaps(&hx) && ry.overlaps(&hy)) &&
		(rx.intersects(&hx) || ry.intersects(&hy)));
}

bool ng::Hitbox::rect_intersect (Vec* const v, const Hitbox* h) {
	int x, y;
	x = this->x;
	y = this->y;

	Range hx, hy;
	hx.init(h->x - h->a, h->x + h->a);
	hy.init(h->y - h->b, h->y + h->b);
	
	bool i = false; // intersection
	Vec p, p1, p2, p3, p4;
	
	// Find closest intersection point.
	p1.y = h->y - h->b;
	if (ng::xint(x, y, v->x, v->y, &p1.x, p1.y) && hx.contains(p1.x) &&
	(!i || ng::distance_sq(x, y, p1.x, p1.y) < ng::distance_sq(x, y, p.x, p.y))) {
		i = true;
		p = p1;
	}
	p2.y = h->y + h->b;
	if (ng::xint(x, y, v->x, v->y, &p2.x, p2.y) && hx.contains(p2.x) &&
	(!i || ng::distance_sq(x, y, p2.x, p2.y) < ng::distance_sq(x, y, p.x, p.y))) {
		i = true;
		p = p2;
	}
	p3.x = h->x - h->a;
	if (ng::yint(x, y, v->x, v->y, p3.x, &p3.y) && hy.contains(p3.y) &&
	(!i || ng::distance_sq(x, y, p3.x, p3.y) < ng::distance_sq(x, y, p.x, p.y))) {
		i = true;
		p = p3;
	}
	p4.x = h->x + h->a;
	if (ng::yint(x, y, v->x, v->y, p4.x, &p4.y) && hy.contains(p4.y) &&
	(!i || ng::distance_sq(x, y, p4.x, p4.x) < ng::distance_sq(x, y, p.x, p.y))) {
		i = true;
		p = p4;
	}
	
	if (i) { // intersection
		this->moveto(v, p.x, p.y);
	} else { // no intersection
		this->moveby(v);
	}
	return i;
}

bool ng::Hitbox::ellipse_contains (int x, int y) const {
	//TODO
	return false;
}

bool ng::Hitbox::ellipse_overlaps (const Hitbox* h) const {
	Hitbox k = *h;
	k.a += this->a;
	k.b += this->b;
	return k.ellipse_contains(this->x, this->y);
}

bool ng::Hitbox::ellipse_collides (const Vec* v, const Hitbox* h) const {
	Hitbox k = *h;
	k.a += this->a;
	k.b += this->b;
	return (this->ellipse_intersects(v, &k));
}

bool ng::Hitbox::ellipse_collide (Vec* const v, const Hitbox* h) {
	Hitbox k = *h;
	k.a += this->a;
	k.b += this->b;
	return (this->ellipse_intersect(v, &k));
}

bool ng::Hitbox::ellipse_intersects (const Vec* v, const Hitbox* h) const {
	//TODO
	return false;
}

bool ng::Hitbox::ellipse_intersect (Vec* const v, const Hitbox* h) {
	//TODO
	this->moveby(v);
	return false;
}

// move this by v, and reduce v to 0.
void ng::Hitbox::moveby (Vec* const v) {
	this->x += v->x;
	this->y += v->y;
	v->x = 0;
	v->y = 0;
}

// move this to (x, y), and reduce v to remaining motion.
void ng::Hitbox::moveto (Vec* const v, int x, int y) {
	int dx, dy;
	dx = x - this->x;
	dy = y - this->y;
	this->x = x;
	this->y = y;
	v->x -= dx;
	v->y -= dy;
}

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


