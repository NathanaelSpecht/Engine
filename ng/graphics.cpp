
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng::Grid::init (const Rect* r, int columns, int rows) {
	this->columns = columns;
	this->rows = rows;
	this->tile_w = (float)r->w / columns;
	this->tile_h = (float)r->h / rows;
}

void ng::Grid::portal (const Rect* src, const Rect* dest) {
	// convert relative coord spaces: src to dest
	// g.tile_w' / g.tile_w = dest.w / src.w
	// --> g.tile_w' = (dest.w / src.w) * g.tile_w
	float scale_x = (float)dest->w / src->w;
	float scale_y = (float)dest->h / src->h;
	this->tile_w = scale_x * this->tile_w;
	this->tile_h = scale_y * this->tile_h;
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
