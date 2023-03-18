
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggraphics.h"
#include "ngmath.h"

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
		this->x = (int)((float)this->x * rel_grid->tile_w_inv);
		this->y = (int)((float)this->y * rel_grid->tile_h_inv);
		this->w = (int)((float)this->w * rel_grid->tile_w_inv);
		this->h = (int)((float)this->h * rel_grid->tile_h_inv);
	}
}

void ng::Rect::relative_to_absolute (const Rect* rel_rect, const Grid* rel_grid) {
	if (rel_grid != NULL) {
		this->x = (int)((float)this->x * rel_grid->tile_w);
		this->y = (int)((float)this->y * rel_grid->tile_h);
		this->w = (int)((float)this->w * rel_grid->tile_w);
		this->h = (int)((float)this->h * rel_grid->tile_h);
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
	float scale_x = (float)dest->w / (float)src->w;
	float scale_y = (float)dest->h / (float)src->h;
	this->x = (int)(scale_x * (float)this->x);
	this->y = (int)(scale_y * (float)this->y);
	this->w = (int)(scale_x * (float)this->w);
	this->h = (int)(scale_y * (float)this->h);
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

void ng::Grid::init (const Rect* r, int columns, int rows) {
	this->columns = columns;
	this->rows = rows;
	this->tile_w = (float)r->w / (float)columns;
	this->tile_h = (float)r->h / (float)rows;
	this->tile_w_inv = (float)columns / (float)r->w;
	this->tile_h_inv = (float)rows / (float)r->h;
}

void ng::Grid::portal (const Rect* src, const Rect* dest) {
	// convert relative coord spaces: src to dest
	// g.tile_w' / g.tile_w = dest.w / src.w
	// --> g.tile_w' = (dest.w / src.w) * g.tile_w
	float scale_x = (float)dest->w / (float)src->w;
	float scale_y = (float)dest->h / (float)src->h;
	this->tile_w = scale_x * this->tile_w;
	this->tile_h = scale_y * this->tile_h;
	this->tile_w_inv = 1.0f / this->tile_w;
	this->tile_h_inv = 1.0f / this->tile_h;
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
	if (SDL_SetTextureColorMod(this->texture, color->r, color->g, color->b) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.r = color->r;
	this->color.g = color->g;
	this->color.b = color->b;
}

void ng::Image::set_alpha (const Color* color) {
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
	if (SDL_SetRenderDrawColor(this->renderer,
	color->r, color->g, color->b, this->color.a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.r = color->r;
	this->color.g = color->g;
	this->color.b = color->b;
}

void ng::Graphics::set_alpha (const Color* color) {
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

void ng::Graphics::draw_image (Image* const image, const Rect* s, const Rect* d) {
	if (image == NULL || image->texture == NULL) {
		this->draw_rect(d, true);
	}
	SDL_Rect src;
	if (s != NULL) {
		s->get_SDL_Rect(&src);
	} else {
		image->rect.get_SDL_Rect(&src);
	}
	SDL_Rect dest;
	if (d != NULL) {
		d->get_SDL_Rect(&dest);
	} else {
		this->rect.get_SDL_Rect(&dest);
	}
	if (image->flip == ng::None && image->angle == 0.0) {
		if (SDL_RenderCopy(this->renderer, image->texture, &src, &dest) != 0) {
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
			} default: {
				flip = static_cast<SDL_RendererFlip>(
					static_cast<int>(SDL_FLIP_HORIZONTAL) |
					static_cast<int>(SDL_FLIP_VERTICAL));
			}
		}
		if (SDL_RenderCopyEx(this->renderer, image->texture, &src, &dest,
		image->angle, NULL, flip) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
	}
}

void ng::Graphics::draw_rect (const Rect* r, int draw) {
	SDL_Rect dest;
	if (r != NULL) {
		r->get_SDL_Rect(&dest);
	} else {
		this->rect.get_SDL_Rect(&dest);
	}
	switch (draw) {
		case ng::DrawFill: {
			if (SDL_RenderFillRect(this->renderer, &dest) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			break;
		} case ng::DrawFrame: {
			if (SDL_RenderDrawRect(this->renderer, &dest) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			break;
		} default: {
			throw std::logic_error("unsupported draw format");
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

void ng::Graphics::draw_tile (Tileset* const tileset, const Rect* src, const Rect* dest) {
	Rect tile = *src;
	tile.x += tileset->column_offset;
	tile.y += tileset->row_offset;
	tile.relative_to_absolute(&tileset->rect, &tileset->grid);
	this->draw_image(tileset->image, &tile, dest);
}

void ng::Graphics::draw_text (Tileset* const tileset, const char* str,
const Rect* rect, const Grid* grid) {
	Rect src, tile, dest;
	src.init(0, 0, 1, 1);
	tile.init(0, 0, 1, 1);
	
	int c;
	for (int i=0; str[i] != '\0'; i++) {
		if (str[i] == '\n') {
			tile.x = 0;
			tile.y += 1;
			if (tile.y >= grid->rows) {
				return;
			}
			continue;
		}
	
		c = static_cast<int>(str[i]);
		src.x = c % tileset->grid.columns;
		src.y = c / tileset->grid.columns;
		dest = tile;
		dest.relative_to_absolute(rect, grid);
		this->draw_tile(tileset, &src, &dest);
		
		tile.x += 1;
		if (tile.x >= grid->columns) {
			tile.x = 0;
			tile.y += 1;
			if (tile.y >= grid->rows) {
				return;
			}
		}
	}
}

/*
void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames,
const char* str, int di) {
	ngFrame cframe = *frame;
	int columns = g->images[frame->image].columns;
	int i, c;
	for (int y = 0; y < h_frames; y++) {
		for (int x = 0; x < w_frames; x++) {
			i = x + (y * w_frames);
			c = str[i];
			if (c == '\0') {
				return;
			}
			c += di;
			if (c < 0) {
				c = 0;
			}
			cframe.column = c % columns;
			cframe.row = c / columns;
			cframe.x = frame->x + (x * frame->w);
			cframe.y = frame->y + (y * frame->h);
			ng_graphics_render_frame(g, &cframe);
		}
	}
}

void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames) {
	int columns = g->images[frame->image].columns;
	int rows = g->images[frame->image].rows;
	if (columns < 3 || rows < 3) {
		return; // spritesheet must be at least 3x3
	}
	ngFrame tframe = *frame;
	for (int y = 0; y < h_frames; y++) {
		for (int x = 0; x < w_frames; x++) {
			if (y == 0) {
				tframe.row = 0;
			} else if (y < h_frames - 1) {
				tframe.row = 1;
			} else {
				tframe.row = 2;
			}
			if (x == 0) {
				tframe.column = 0;
			} else if (x < w_frames - 1) {
				tframe.column = 1;
			} else {
				tframe.column = 2;
			}
			tframe.x = frame->x + (x * frame->w);
			tframe.y = frame->y + (y * frame->h);
			ng_graphics_render_frame(g, &tframe);
		}
	}
}
*/

