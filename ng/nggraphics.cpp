
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggraphics.h"
#include "ngmath.h"

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

void ng::Rect::init (int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void ng::Rect::scale (const Scale* s) {
	this->x = static_cast<int>(static_cast<float>(this->x) * s->x);
	this->y = static_cast<int>(static_cast<float>(this->y) * s->y);
	this->w = static_cast<int>(static_cast<float>(this->w) * s->x);
	this->h = static_cast<int>(static_cast<float>(this->h) * s->y);
}

void ng::Rect::scale_inv (const Scale* s) {
	this->x = static_cast<int>(static_cast<float>(this->x) * s->x_inv);
	this->y = static_cast<int>(static_cast<float>(this->y) * s->y_inv);
	this->w = static_cast<int>(static_cast<float>(this->w) * s->x_inv);
	this->h = static_cast<int>(static_cast<float>(this->h) * s->y_inv);
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

bool ng::Rect::contains (int x, int y) const {
	Range rx, ry;
	rx.init(this->x, this->x + this->w);
	ry.init(this->y, this->y + this->h);
	return (rx.contains(x) && ry.contains(y));
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
	t.init(this);
	t.scale(s);
	this->set_tile(&t);
}

void ng::Grid::scale_inv (const Scale* s) {
	Scale t;
	t.init(this);
	t.scale_inv(s);
	this->set_tile(&t);
}

void ng::Grid::absolute_to_relative (const Grid* rel_grid) {
	// g is same units as rel
	// want g in units of rel
	// scale by 1 / rel.w
	Scale s, rel;
	s.init(this);
	rel.init(rel_grid);
	s.absolute_to_relative(&rel);
	this->set_tile(&s);
}

void ng::Grid::relative_to_absolute (const Grid* rel_grid) {
	// g is in units of rel
	// want g in same units as rel
	// scale by rel.w
	Scale s, rel;
	s.init(this);
	rel.init(rel_grid);
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


