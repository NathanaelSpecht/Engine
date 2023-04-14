
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggraphics.h"

ng::Color::Color () {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}

ng::Color::~Color () {}

void ng::Color::set (int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

void ng::Color::set (int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

ng::Image::Image () {
	this->texture = NULL;
	this->w = 0.0;
	this->h = 0.0;
	this->color.set(255, 255, 255);
	this->flip = ng::None;
}

ng::Image::~Image () {
	if (this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
}

void ng::Image::load (Graphics* const g, const char* file, const Color* key) {
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
	this->w = static_cast<double>(surface->w);
	this->h = static_cast<double>(surface->h);
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

ng::Graphics::Graphics () {
	this->window = NULL;
	this->renderer = NULL;
	this->w = 0.0;
	this->h = 0.0;
	this->color.set(0, 0, 0);
}

ng::Graphics::~Graphics () {}

void ng::Graphics::open (const char* title, double w, double h) {
	this->w = w;
	this->h = h;
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		static_cast<int>(w), static_cast<int>(h), SDL_WINDOW_RESIZABLE);
	if (this->window == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::close () {
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

// Draw whole image to whole window.
void ng::Graphics::draw_image (Image* const image) {
	Rect2 src(image->w * 0.5, image->h * 0.5, image->w, image->h);
	Rect2 dest(this->w * 0.5, this->h * 0.5, this->w, this->h);
	this->draw_image(image, &src, &dest);
}

// Draw whole image to part of window.
void ng::Graphics::draw_image (Image* const image, const Rect2* dest) {
	Rect2 src(image->w * 0.5, image->h * 0.5, image->w, image->h);
	this->draw_image(image, &src, dest);
}

// Draw part of image to part of window.
void ng::Graphics::draw_image (Image* const image, const Rect2* src, const Rect2* dest) {
	SDL_Rect src_sdl, dest_sdl;
	src_sdl.x = static_cast<int>(src->p.x - (src->w * 0.5));
	src_sdl.y = static_cast<int>(src->p.y - (src->h * 0.5));
	src_sdl.w = static_cast<int>(src->w);
	src_sdl.h = static_cast<int>(src->h);
	dest_sdl.x = static_cast<int>(dest->p.x - (dest->w * 0.5));
	dest_sdl.y = static_cast<int>(dest->p.y - (dest->h * 0.5));
	dest_sdl.w = static_cast<int>(dest->w);
	dest_sdl.h = static_cast<int>(dest->h);
	
	if (image->flip == ng::None && src->a == 0.0 && dest->a == 0.0) {
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
		ng::degrees(src->a + dest->a), NULL, flip) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
	}
}

void ng::Graphics::draw_rect (const Rect2* dest, int draw) {
	SDL_Rect dest_sdl;
	dest_sdl.x = static_cast<int>(dest->p.x - (dest->w * 0.5));
	dest_sdl.y = static_cast<int>(dest->p.y - (dest->h * 0.5));
	dest_sdl.w = static_cast<int>(dest->w);
	dest_sdl.h = static_cast<int>(dest->h);
	
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

void ng::Graphics::draw_line (const Line2* line) {
	int x1, y1, x2, y2;
	x1 = static_cast<int>(line->p.x);
	y1 = static_cast<int>(line->p.y);
	x2 = static_cast<int>(line->p.x + line->v.x);
	y2 = static_cast<int>(line->p.y + line->v.y);

	if (SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::draw_point (const Vec2* vec) {
	int x, y;
	x = static_cast<int>(vec->x);
	y = static_cast<int>(vec->y);

	if (SDL_RenderDrawPoint(this->renderer, x, y) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}


