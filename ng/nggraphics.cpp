
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggraphics.h"

// Switch between window and graphics coordinates.
// Window (0,0) is top-left corner, +x points right, and +y points down.
// Graphics (0,0) is center, +x points right, and +y points up.
// These are used internally by the graphics draw functions.
double ng::window_x (double x, double rx) {
	return x+rx;
}

double ng::window_y (double y, double ry) {
	return -(y-ry);
}

double ng::graphics_x (double x, double rx) {
	// window_x = graphics_x + rx
	// graphics_x = window_x - rx
	return x-rx;
}

double ng::graphics_y (double y, double ry) {
	// window_y = -(graphics_y - ry)
	// graphics_y = (-window_y) + ry
	return (-y)+ry
}

Rect2 ng::window_rect (const Box2& a, double rx, double ry) {
	Box2 b(ng::window_x(a.x,rx), ng::window_y(a.y,ry), a.rx, a.ry);
	Rect2 c(b);
	return c;
}

SDL_Rect ng::sdl_rect (const Rect2& a) {
	SDL_Rect b;
	b.x = static_cast<int>(c.x);
	b.y = static_cast<int>(c.y);
	b.w = static_cast<int>(c.w);
	b.h = static_cast<int>(c.h);
	return b;
}

SDL_RendererFlip ng::sdl_flip (int flip) {
	SDL_RendererFlip flip_sdl;
	switch (flip) {
		case ng::FlipX:
			flip_sdl = SDL_FLIP_HORIZONTAL;
			break;
		case ng::FlipY:
			flip_sdl = SDL_FLIP_VERTICAL;
			break;
		case ng::FlipXY:
			flip_sdl = static_cast<SDL_RendererFlip>(
				static_cast<int>(SDL_FLIP_HORIZONTAL) |
				static_cast<int>(SDL_FLIP_VERTICAL));
		case ng::None: default:
			flip_sdl = SDL_FLIP_NONE;
	}
	return flip_sdl;
}

ng::Color::Color () :
	r(0),
	g(0),
	b(0),
	a(255)
{}

ng::Color::Color (int r, int g, int b) :
	r(r),
	g(g),
	b(b),
	a(255)
{}

ng::Color::Color (int r, int g, int b, int a) :
	r(r),
	g(g),
	b(b),
	a(a)
{}

ng::Color::Color (const Color& color) :
	r(color.r),
	g(color.g),
	b(color.b),
	a(color.a)
{}

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

ng::Image::Image () :
	texture(NULL),
	w(0.0),
	h(0.0),
	color(255, 255, 255),
	flip(ng::None)
{}

ng::Image::~Image () {
	if (this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
}

void ng::Image::load (Graphics* const graphics, const char* file, const Color& key) {
	SDL_Surface* surface = NULL;
	surface = SDL_LoadBMP(file);
	if (surface == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 
	key.r, key.g, key.b)) != 0) {
		SDL_FreeSurface(surface);
		throw std::runtime_error(SDL_GetError());
	}
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTextureFromSurface(graphics->renderer, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		throw std::runtime_error(SDL_GetError());
	}
	
	this->texture = texture;
	this->w = static_cast<double>(surface->w);
	this->h = static_cast<double>(surface->h);
}

void ng::Image::set_color (const Color& color) {
	if (this->color.r == color.r && this->color.g == color.g && this->color.b == color.b) {
		return;
	}
	// This is a different color.
	if (SDL_SetTextureColorMod(this->texture, color.r, color.g, color.b) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.r = color.r;
	this->color.g = color.g;
	this->color.b = color.b;
}

void ng::Image::set_alpha (const Color& color) {
	if (this->color.a == color.a) {
		return;
	}
	// This is a different alpha.
	if (SDL_SetTextureAlphaMod(this->texture, color.a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.a = color.a;
}

/*
void ng::Image::set_flip (int flip) {
	this->flip = flip;
}
*/

ng::Graphics::Graphics () :
	window(NULL),
	renderer(NULL),
	rx(0.0),
	ry(0.0),
	color(0, 0, 0)
{}

void ng::Graphics::open (const char* title, double rx, double ry) {
	this->rx = rx;
	this->ry = ry;
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		static_cast<int>(rx*2.0), static_cast<int>(ry*2.0), SDL_WINDOW_RESIZABLE);
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

void ng::Graphics::set_color (const Color& color) {
	if (this->color.r == color.r && this->color.g == color.g && this->color.b == color.b) {
		return;
	}
	// This is a different color.
	if (SDL_SetRenderDrawColor(this->renderer,
	color.r, color.g, color.b, this->color.a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.r = color.r;
	this->color.g = color.g;
	this->color.b = color.b;
}

void ng::Graphics::set_alpha (const Color& color) {
	if (this->color.a == color.a) {
		return;
	}
	// This is a different alpha.
	SDL_BlendMode blendmode;
	if (color.a == 255) {
		blendmode = SDL_BLENDMODE_NONE;
	} else {
		blendmode = SDL_BLENDMODE_BLEND;
	}
	if (SDL_SetRenderDrawBlendMode(this->renderer, blendmode) != 0 ||
	SDL_SetRenderDrawColor(this->renderer,
	this->color.r, this->color.g, this->color.b, color.a) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
	this->color.a = color.a;
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
	Rect2 src(0.0, 0.0, image->w, image->h);
	Box2 dest(0.0, 0.0, this->rx, this->ry);
	this->draw_image(image, src, dest);
}

// Draw whole image to part of window.
void ng::Graphics::draw_image (Image* const image, const Box2& dest) {
	Rect2 src(0.0, 0.0, image->w, image->h);
	this->draw_image(image, src, dest);
}

// Draw part of image to part of window.
void ng::Graphics::draw_image (Image* const image, const Rect2& src, const Box2& dest) {
	SDL_Rect src_sdl = ng::sdl_rect(src);
	SDL_Rect dest_sdl = ng::sdl_rect(ng::window_rect(dest));
	
	if (SDL_RenderCopy(this->renderer, image->texture, &src_sdl, &dest_sdl) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::draw_image (Image* const image, const Rect2& src, const Box2& dest,
double angle, int flip) {
	SDL_Rect src_sdl = ng::sdl_rect(src);
	SDL_Rect dest_sdl = ng::sdl_rect(ng::window_rect(dest));
	
	if (SDL_RenderCopyEx(this->renderer, image->texture, &src_sdl, &dest_sdl,
	ng::degrees(angle), NULL, ng::sdl_flip(flip)) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

// Draw shape.
void ng::Graphics::draw_box (const Box2& dest, int draw) {
	SDL_Rect dest_sdl = ng::sdl_rect(ng::window_rect(dest));
	
	switch (draw) {
		case ng::DrawFill: {
			if (SDL_RenderFillRect(this->renderer, &dest_sdl) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			break;
		} case ng::DrawFrame: default: {
			if (SDL_RenderDrawRect(this->renderer, &dest_sdl) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
		}
	}
}

void ng::Graphics::draw_line (const Vec2& p1, const Vec2& p2) {
	int x1, y1, x2, y2;
	x1 = static_cast<int>(ng::window_x(p1.x, this->rx));
	y1 = static_cast<int>(ng::window_y(p1.y, this->ry));
	x2 = static_cast<int>(ng::window_x(p2.x, this->rx));
	y2 = static_cast<int>(ng::window_y(p2.y, this->ry));

	if (SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::Graphics::draw_point (const Vec2& p) {
	int x, y;
	x = static_cast<int>(ng::window_x(p.x, this->rx));
	y = static_cast<int>(ng::window_y(p.y, this->ry));

	if (SDL_RenderDrawPoint(this->renderer, x, y) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}


