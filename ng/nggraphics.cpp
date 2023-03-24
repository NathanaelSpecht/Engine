
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggraphics.h"
#include "ngmath.h"

void ng::Vec::init (int x, int y) {
	this->x = x;
	this->y = y;
}

void ng::Vec::scale (const Scale* s) {
	this->x = static_cast<int>(static_cast<float>(this->x) * s->x);
	this->y = static_cast<int>(static_cast<float>(this->y) * s->y);
}

void ng::Vec::scale_inv (const Scale* s) {
	this->x = static_cast<int>(static_cast<float>(this->x) * s->x_inv);
	this->y = static_cast<int>(static_cast<float>(this->y) * s->y_inv);
}

void ng::Vec::absolute_to_relative (const Rect* rel_rect) {
	this->x = this->x - rel_rect->x;
	this->y = this->y - rel_rect->y;
}

void ng::Vec::absolute_to_relative (const Grid* rel_grid) {
	Scale rel;
	rel.init(rel_grid);
	this->scale_inv(&rel);
}

void ng::Vec::absolute_to_relative (const Rect* rel_rect, const Grid* rel_grid) {
	this->absolute_to_relative(rel_rect);
	this->absolute_to_relative(rel_grid);
}

void ng::Vec::relative_to_absolute (const Rect* rel_rect) {
	this->x = this->x + rel_rect->x;
	this->y = this->y + rel_rect->y;
}

void ng::Vec::relative_to_absolute (const Grid* rel_grid) {
	Scale rel;
	rel.init(rel_grid);
	this->scale(&rel);
}

void ng::Vec::relative_to_absolute (const Rect* rel_rect, const Grid* rel_grid) {
	this->relative_to_absolute(rel_grid);
	this->relative_to_absolute(rel_rect);
}

void ng::Vec::portal (const Rect* src, const Rect* dest) {
	this->absolute_to_relative(src);
	Scale s;
	s.init(src, dest);
	this->scale(&s);
	this->relative_to_absolute(dest);
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
	// a collides with b when (a.x, a.y) is within a.r + b.r of (b.x, b.y).
	// -> when (a.x, a.y) intersects circle c (b.x, b.y, a.r + b.r).
	
	return ng::False;
}

void ng::Rect::init (int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void ng::Rect::scale (const Scale* s) {
	this->x = static_cast<int>(static_cast<float>(this->x) * s->x);
	this->y = static_cast<int>(static_cast<float>(this->x) * s->y);
	this->w = static_cast<int>(static_cast<float>(this->x) * s->x);
	this->h = static_cast<int>(static_cast<float>(this->x) * s->y);
}

void ng::Rect::scale_inv (const Scale* s) {
	this->x = static_cast<int>(static_cast<float>(this->x) * s->x_inv);
	this->y = static_cast<int>(static_cast<float>(this->x) * s->y_inv);
	this->w = static_cast<int>(static_cast<float>(this->x) * s->x_inv);
	this->h = static_cast<int>(static_cast<float>(this->x) * s->y_inv);
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

void ng::Rect::absolute_to_relative (const Rect* rel_rect) {
	this->x = this->x - rel_rect->x;
	this->y = this->y - rel_rect->y;
}

void ng::Rect::absolute_to_relative (const Grid* rel_grid) {
	Scale rel;
	rel.init(rel_grid);
	this->scale_inv(&rel);
}

void ng::Rect::absolute_to_relative (const Rect* rel_rect, const Grid* rel_grid) {
	this->absolute_to_relative(rel_rect);
	this->absolute_to_relative(rel_grid);
}

void ng::Rect::relative_to_absolute (const Rect* rel_rect) {
	this->x = this->x + rel_rect->x;
	this->y = this->y + rel_rect->y;
}

void ng::Rect::relative_to_absolute (const Grid* rel_grid) {
	Scale rel;
	rel.init(rel_grid);
	this->scale(&rel);
}

void ng::Rect::relative_to_absolute (const Rect* rel_rect, const Grid* rel_grid) {
	this->relative_to_absolute(rel_grid);
	this->relative_to_absolute(rel_rect);
}

void ng::Rect::portal (const Rect* src, const Rect* dest) {
	this->absolute_to_relative(src);
	Scale s;
	s.init(src, dest);
	this->scale(&s);
	this->relative_to_absolute(dest);
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

// No scale.
void ng::Scale::init () {
	this->x = 1.0f;
	this->y = 1.0f;
	this->x_inv = 1.0f;
	this->y_inv = 1.0f;
}

// Compute x_inv and y_inv scales from x and y.
void ng::Scale::init (float x, float y) {
	this->x = x;
	this->y = y;
	this->x_inv = 1.0f / x;
	this->y_inv = 1.0f / y;
}

void ng::Scale::init (float x, float y, float x_inv, float y_inv) {
	this->x = x;
	this->y = y;
	this->x_inv = x_inv;
	this->y_inv = y_inv;
}

void ng::Scale::init (const Grid* grid) {
	this->x = grid->tile_w;
	this->y = grid->tile_h;
	this->x_inv = grid->tile_w_inv;
	this->y_inv = grid->tile_h_inv;
}

// Compute scale of grid tiles from columns.
void ng::Scale::init (const Rect* r, int columns, int rows) {
	this->x = static_cast<float>(r->w) / static_cast<float>(columns);
	this->y = static_cast<float>(r->h) / static_cast<float>(rows);
	this->x_inv = 1.0f / this->x;
	this->y_inv = 1.0f / this->y;
}

// Compute scale between two rects.
void ng::Scale::init (const Rect* src, const Rect* dest) {
	this->x = static_cast<float>(dest->w) / static_cast<float>(src->w);
	this->y = static_cast<float>(dest->h) / static_cast<float>(src->h);
	this->x_inv = 1.0f / this->x;
	this->y_inv = 1.0f / this->y;
}

void ng::Scale::inverse () {
	this->x = 1.0f / this->x;
	this->y = 1.0f / this->y;
	this->x_inv = 1.0f / this->x_inv;
	this->y_inv = 1.0f / this->y_inv;
}

void ng::Scale::scale (const Scale* s) {
	this->x *= s->x;
	this->y *= s->y;
	this->x_inv *= s->x_inv;
	this->y_inv *= s->y_inv;
}

void ng::Scale::scale_inv (const Scale* s) {
	this->x *= s->x_inv;
	this->y *= s->y_inv;
	this->x_inv *= s->x;
	this->y_inv *= s->y;
}

void ng::Scale::absolute_to_relative (const Scale* s) {
	this->scale_inv(s);
}

void ng::Scale::relative_to_absolute (const Scale* s) {
	this->scale(s);
}

void ng::Scale::portal (const Rect* src, const Rect* dest) {
	Scale s;
	s.init(src, dest);
	this->scale(&s);
}

void ng::Grid::set_tile (const Scale* s) {
	this->tile_w = s->x;
	this->tile_h = s->y;
	this->tile_w_inv = s->x_inv;
	this->tile_h_inv = s->y_inv;
}

void ng::Grid::init (const Rect* r) {
	this->columns = r->w;
	this->rows = r->h;
	Scale s;
	s.init();
	this->set_tile(&s);
}

void ng::Grid::init (const Rect* r, int columns, int rows) {
	this->columns = columns;
	this->rows = rows;
	Scale s;
	s.init(r, columns, rows);
	this->set_tile(&s);
}

void ng::Grid::scale (const Scale* s) {
	Scale t;
	t.init(this->tile_w, this->tile_h, this->tile_w_inv, this->tile_h_inv);
	t.scale(s);
	this->set_tile(&t);
}

void ng::Grid::scale_inv (const Scale* s) {
	Scale t;
	t.init(this->tile_w, this->tile_h, this->tile_w_inv, this->tile_h_inv);
	t.scale_inv(s);
	this->set_tile(&t);
}

void ng::Grid::absolute_to_relative (const Grid* rel_grid) {
	// g is same units as rel
	// want g in units of rel
	// scale by 1 / rel.w
	Scale s, rel;
	s.init(this->tile_w, this->tile_h, this->tile_w_inv, this->tile_h_inv);
	rel.init(rel_grid->tile_w, rel_grid->tile_h, rel_grid->tile_w_inv, rel_grid->tile_h_inv);
	s.absolute_to_relative(&rel);
	this->set_tile(&s);
}

void ng::Grid::relative_to_absolute (const Grid* rel_grid) {
	// g is in units of rel
	// want g in same units as rel
	// scale by rel.w
	Scale s, rel;
	s.init(this->tile_w, this->tile_h, this->tile_w_inv, this->tile_h_inv);
	rel.init(rel_grid->tile_w, rel_grid->tile_h, rel_grid->tile_w_inv, rel_grid->tile_h_inv);
	s.relative_to_absolute(&rel);
	this->set_tile(&s);
}

void ng::Grid::portal (const Rect* src, const Rect* dest) {
	// scale g by dest / src
	Scale s;
	s.init(src, dest);
	this->scale(&s);
}

void ng::Color::init (int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

void ng::Color::init (int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void ng::Image::init (Graphics* const g, const char* file, const Color* key) {
	this->texture = NULL;
	this->rect.init(0, 0, 0, 0);
	this->color.init(255, 255, 255);
	this->flip = ng::None;
	this->angle = 0.0;
	
	SDL_Surface* surface = NULL;
	surface = SDL_LoadBMP(file);
	if (surface == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 
	key->r, key->g, key->b)) != 0) {
		SDL_FreeSurface(surface);
		throw std::runtime_error(SDL_GetError());
	}
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTextureFromSurface(g->renderer, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		throw std::runtime_error(SDL_GetError());
	}
	
	this->texture = texture;
	this->rect.w = surface->w;
	this->rect.h = surface->h;
}

void ng::Image::quit () {
	if (this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
}

void ng::Image::set_color (const Color* color) {
	if (this->color.r == color->r && this->color.g == color->g && this->color.b == color->b) {
		return;
	}
	// This is a different color.
	if (SDL_SetTextureColorMod(this->texture, color->r, color->g, color->b) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.r = color->r;
	this->color.g = color->g;
	this->color.b = color->b;
}

void ng::Image::set_alpha (const Color* color) {
	if (this->color.a == color->a) {
		return;
	}
	// This is a different alpha.
	if (SDL_SetTextureAlphaMod(this->texture, color->a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.a = color->a;
}

void ng::Image::set_flip (int flip) {
	this->flip = flip;
}

void ng::Image::set_angle (double angle) {
	this->angle = angle;
}

void ng::Tileset::init (Image* image, const Rect* rect, int columns, int rows) {
	this->image = image;
	this->rect = *rect;
	this->grid.init(rect, columns, rows);
	this->column_offset = 0;
	this->row_offset = 0;
}

void ng::Canvas::init (Graphics* graphics) {
	this->graphics = graphics;
	this->parent = NULL;
	this->use_grid = false;
	this->use_scale = false;
	this->root = true;
	this->rect = graphics->rect;
	this->grid.init(&graphics->rect);
	this->scale.init();
}

void ng::Canvas::init (Canvas* canvas, const Rect* rect) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->use_grid = false;
	this->use_scale = false;
	this->root = false;
	this->rect = *rect;
	this->grid.init(rect);
	this->scale.init();
}

void ng::Canvas::set_grid (const Grid* grid) {
	this->use_grid = true;
	this->grid = *grid;
}

void ng::Canvas::set_scale (const Scale* s) {
	this->use_scale = true;
	this->scale = *s;
}

void ng::Canvas::remove_grid () {
	this->use_grid = false;
}

void ng::Canvas::remove_scale () {
	this->use_scale = false;
}

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

// Given event mouse point on root canvas, find mouse point on this canvas.
void ng::Canvas::get_mouse (const Vec* mouse, Vec* const p) {
	if (this->root) {
		*p = *mouse;
	} else {
		this->parent->get_mouse(mouse, p);
		if (this->use_scale) {
			if (this->parent->root) {
				p->portal(&this->graphics->rect, &this->rect);
			} else {
				p->portal(&this->parent->rect, &this->rect);
			}
		}
		p->absolute_to_relative(&this->rect);
		if (this->use_grid) {
			p->absolute_to_relative(&this->grid);
		}
	}
}

// Draw this->rect on parent.
// Clearing root canvas calls graphics clear().
void ng::Canvas::clear (int draw) {
	if (this->root) {
		this->graphics->clear();
	} else {
		this->parent->draw_rect(&this->rect, draw);
	}
}

// Given shape on this canvas, draw on parent canvas.
// Drawing to root canvas draws on graphics.
void ng::Canvas::draw_text (Tileset* const tileset, const char* str,
const Rect* textbox, const Grid* textgrid) {
	if (this->root) {
		this->graphics->draw_text(tileset, str, textbox, textgrid);
	} else {
		Rect tb = *textbox;
		Grid g = *textgrid;
		if (this->use_grid) {
			tb.relative_to_absolute(&this->grid);
			g.relative_to_absolute(&this->grid);
		}
		tb.relative_to_absolute(&this->rect);
		if (this->use_scale) {
			if (this->parent->root) {
				tb.portal(&this->rect, &this->graphics->rect);
				g.portal(&this->rect, &this->graphics->rect);
			} else {
				tb.portal(&this->rect, &this->parent->rect);
				g.portal(&this->rect, &this->parent->rect);
			}
		}
		this->parent->draw_text(tileset, str, &tb, &g);
	}
}

void ng::Canvas::draw_tile (Tileset* const tileset, const Rect* src, const Rect* dest) {
	if (this->root) {
		this->graphics->draw_tile(tileset, src, dest);
	} else {
		Rect d = *dest;
		if (this->use_grid) {
			d.relative_to_absolute(&this->grid);
		}
		d.relative_to_absolute(&this->rect);
		if (this->use_scale) {
			if (this->parent->root) {
				d.portal(&this->rect, &this->graphics->rect);
			} else {
				d.portal(&this->rect, &this->parent->rect);
			}
		}
		this->parent->draw_tile(tileset, src, &d);
	}
}

void ng::Canvas::draw_image (Image* const image) {
	if (this->root) {
		this->draw_image(image, &image->rect, &this->graphics->rect);
	} else {
		this->draw_image(image, &image->rect, &this->rect);
	}
}

void ng::Canvas::draw_image (Image* const image, const Rect* dest) {
	this->draw_image(image, &image->rect, dest);
}

void ng::Canvas::draw_image (Image* const image, const Rect* src, const Rect* dest) {
	if (this->root) {
		this->graphics->draw_image(image, src, dest);
	} else {
		Rect d = *dest;
		if (this->use_grid) {
			d.relative_to_absolute(&this->grid);
		}
		d.relative_to_absolute(&this->rect);
		if (this->use_scale) {
			if (this->parent->root) {
				d.portal(&this->rect, &this->graphics->rect);
			} else {
				d.portal(&this->rect, &this->parent->rect);
			}
		}
		this->parent->draw_image(image, src, &d);
	}
}

void ng::Canvas::draw_rect (const Rect* dest, int draw) {
	if (this->root) {
		this->graphics->draw_rect(dest, draw);
	} else {
		Rect d = *dest;
		if (this->use_grid) {
			d.relative_to_absolute(&this->grid);
		}
		d.relative_to_absolute(&this->rect);
		if (this->use_scale) {
			if (this->parent->root) {
				d.portal(&this->rect, &this->graphics->rect);
			} else {
				d.portal(&this->rect, &this->parent->rect);
			}
		}
		this->parent->draw_rect(&d, draw);
	}
}

void ng::Canvas::draw_line (int x1, int y1, int x2, int y2) {
	if (this->root) {
		this->graphics->draw_line(x1, y1, x2, y2);
	} else {
		Vec v1, v2;
		v1.init(x1, y1);
		v2.init(x2, y2);
		if (this->use_grid) {
			v1.relative_to_absolute(&this->grid);
			v2.relative_to_absolute(&this->grid);
		}
		v1.relative_to_absolute(&this->rect);
		v2.relative_to_absolute(&this->rect);
		if (this->use_scale) {
			if (this->parent->root) {
				v1.portal(&this->rect, &this->graphics->rect);
				v2.portal(&this->rect, &this->graphics->rect);
			} else {
				v1.portal(&this->rect, &this->parent->rect);
				v2.portal(&this->rect, &this->parent->rect);
			}
		}
		this->parent->draw_line(v1.x, v1.y, v2.x, v2.y);
	}
}

void ng::Canvas::draw_point (int x, int y) {
	if (this->root) {
		this->graphics->draw_point(x, y);
	} else {
		Vec v;
		v.init(x, y);
		if (this->use_grid) {
			v.relative_to_absolute(&this->grid);
		}
		v.relative_to_absolute(&this->rect);
		if (this->use_scale) {
			if (this->parent->root) {
				v.portal(&this->rect, &this->graphics->rect);
			} else {
				v.portal(&this->rect, &this->parent->rect);
			}
		}
		this->parent->draw_point(v.x, v.y);
	}
}

void ng::Graphics::init (const char* title, int w, int h) {
	this->window = NULL;
	this->renderer = NULL;
	this->rect.init(0, 0, w, h);
	this->color.init(0, 0, 0);
	
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
	if (this->window == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::quit () {
	if (this->renderer != NULL) {
		SDL_DestroyRenderer(this->renderer);
		this->renderer = NULL;
	}
	if (this->window != NULL) {
		SDL_DestroyWindow(this->window);
		this->window = NULL;
	}
}

void ng::Graphics::set_color (const Color* color) {
	if (this->color.r == color->r && this->color.g == color->g && this->color.b == color->b) {
		return;
	}
	// This is a different color.
	if (SDL_SetRenderDrawColor(this->renderer,
	color->r, color->g, color->b, this->color.a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.r = color->r;
	this->color.g = color->g;
	this->color.b = color->b;
}

void ng::Graphics::set_alpha (const Color* color) {
	if (this->color.a == color->a) {
		return;
	}
	// This is a different alpha.
	SDL_BlendMode blendmode;
	if (color->a == 255) {
		blendmode = SDL_BLENDMODE_NONE;
	} else {
		blendmode = SDL_BLENDMODE_BLEND;
	}
	if (SDL_SetRenderDrawBlendMode(this->renderer, blendmode) != 0 ||
	SDL_SetRenderDrawColor(this->renderer,
	this->color.r, this->color.g, this->color.b, color->a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.a = color->a;
}

void ng::Graphics::clear () {
	if (SDL_RenderClear(this->renderer) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::draw () {
	SDL_RenderPresent(this->renderer);
}

void ng::Graphics::draw_text (Tileset* const tileset, const char* str,
const Rect* textbox, const Grid* textgrid) {
	Rect src, tile, dest;
	src.init(0, 0, 1, 1);
	tile.init(0, 0, 1, 1);
	
	int c;
	for (int i=0; str[i] != '\0'; i++) {
		if (str[i] == '\n') {
			tile.x = 0;
			tile.y += 1;
			if (tile.y >= textgrid->rows) {
				return;
			}
			continue;
		}
	
		c = static_cast<int>(str[i]);
		src.x = c % tileset->grid.columns;
		src.y = c / tileset->grid.columns;
		dest = tile;
		dest.relative_to_absolute(textbox, textgrid);
		this->draw_tile(tileset, &src, &dest);
		
		tile.x += 1;
		if (tile.x >= textgrid->columns) {
			tile.x = 0;
			tile.y += 1;
			if (tile.y >= textgrid->rows) {
				return;
			}
		}
	}
}

void ng::Graphics::draw_tile (Tileset* const tileset, const Rect* src, const Rect* dest) {
	Rect tile = *src;
	tile.x += tileset->column_offset;
	tile.y += tileset->row_offset;
	tile.relative_to_absolute(&tileset->rect, &tileset->grid);
	this->draw_image(tileset->image, &tile, dest);
}

// Draw whole image to whole window.
void ng::Graphics::draw_image (Image* const image) {
	this->draw_image(image, &image->rect, &this->rect);
}

// Draw whole image to part of window.
void ng::Graphics::draw_image (Image* const image, const Rect* dest) {
	this->draw_image(image, &image->rect, dest);
}

// Draw part of image to part of window.
void ng::Graphics::draw_image (Image* const image, const Rect* src, const Rect* dest) {
	SDL_Rect src_sdl = {src->x, src->y, src->w, src->h};
	SDL_Rect dest_sdl = {dest->x, dest->y, dest->w, dest->h};
	if (image->flip == ng::None && image->angle == 0.0) {
		if (SDL_RenderCopy(this->renderer, image->texture, &src_sdl, &dest_sdl) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
	} else {
		SDL_RendererFlip flip;
		switch (image->flip) {
			case ng::None: {
				flip = SDL_FLIP_NONE;
				break;
			} case ng::FlipX: {
				flip = SDL_FLIP_HORIZONTAL;
				break;
			} case ng::FlipY: {
				flip = SDL_FLIP_VERTICAL;
				break;
			} case ng::FlipXY: {
				flip = static_cast<SDL_RendererFlip>(
					static_cast<int>(SDL_FLIP_HORIZONTAL) |
					static_cast<int>(SDL_FLIP_VERTICAL));
			} default: {
				throw std::logic_error("unsupported flip mode");
			}
		}
		if (SDL_RenderCopyEx(this->renderer, image->texture, &src_sdl, &dest_sdl,
		image->angle, NULL, flip) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
	}
}

void ng::Graphics::draw_rect (const Rect* dest, int draw) {
	SDL_Rect dest_sdl = {dest->x, dest->y, dest->w, dest->h};
	switch (draw) {
		case ng::DrawFill: {
			if (SDL_RenderFillRect(this->renderer, &dest_sdl) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			break;
		} case ng::DrawFrame: {
			if (SDL_RenderDrawRect(this->renderer, &dest_sdl) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			break;
		} default: {
			throw std::logic_error("unsupported draw mode");
		}
	}
}

void ng::Graphics::draw_line (int x1, int y1, int x2, int y2) {
	if (SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::draw_point (int x, int y) {
	if (SDL_RenderDrawPoint(this->renderer, x, y) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}


