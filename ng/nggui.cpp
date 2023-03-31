
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggui.h"
#include "ngmath.h"

void ng::Tileset::init (Image* image, const Space* space) {
	this->image = image;
	this->space = *space;
	this->offset.init2(0.0, 0.0);
}

void ng::Tileset::init (Image* image, const Rect* rect) {
	this->image = image;
	this->space.init2(rect);
	this->offset.init2(0.0, 0.0);
}

void ng::Tileset::init_c (Image* image, const Rect* rect, double c, double r) {
	this->image = image;
	this->space.init2_c(rect, c, r);
	this->offset.init2(0.0, 0.0);
}

void ng::Tileset::init_i (Image* image, const Rect* rect, double i, double j) {
	this->image = image;
	this->space.init2_i(rect, i, j);
	this->offset.init2(0.0, 0.0);
}

void ng::Canvas::init (Graphics* graphics) {
	this->graphics = graphics;
	this->parent = NULL;
	this->root = true;
	this->space.init2(&graphics->rect);
}

void ng::Canvas::init (Canvas* canvas, const Space* space) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->root = false;
	this->space = *space;
}

// Given event mouse point on root canvas, find mouse point on this canvas.
void ng::Canvas::get_mouse (Vec* const mouse) {
	if (this->root) {
		Vec s;
		s.init2(&this->graphics->rect, &this->space);
		mouse->scale2(s.x, s.y);
	} else {
		this->parent->get_mouse(mouse);
		mouse->absolute_to_relative2(&this->space);
	}
}

// Draw this->rect on parent.
// Clearing root canvas calls graphics clear().
void ng::Canvas::clear () {
	if (this->root) {
		this->graphics->clear();
	} else {
		this->parent->draw_rect(&this->space.rect, ng::DrawFill);
	}
}

// Usually does nothing.
// Drawing root canvas calls graphics draw().
void ng::Canvas::draw () {
	if (this->root) {
		this->graphics->draw();
	}
}

// Graphics primitives
void ng::Canvas::draw_image (Image* const image) {
	if (this->root) {
		this->graphics->draw_image(image, &image->rect, &this->space.rect);
	} else {
		this->parent->draw_image(image, &image->rect, &this->space.rect);
	}
}

void ng::Canvas::draw_image (Image* const image, const Rect* dest) {
	Rect d = *dest;
	d.relative_to_absolute2(&this->space);
	
	if (this->root) {
		this->graphics->draw_image(image, &image->rect, &d);
	} else {
		this->parent->draw_image(image, &image->rect, &d);
	}
}

void ng::Canvas::draw_image (Image* const image, const Rect* src, const Rect* dest) {
	Rect d = *dest;
	d.relative_to_absolute2(&this->space);
	
	if (this->root) {
		this->graphics->draw_image(image, src, &d);
	} else {
		this->parent->draw_image(image, src, &d);
	}
}

void ng::Canvas::draw_rect (const Rect* dest, int draw) {
	Rect d = *dest;
	d.relative_to_absolute2(&this->space);
	
	if (this->root) {
		this->graphics->draw_rect(&d, draw);
	} else {
		this->parent->draw_rect(&d, draw);
	}
}

void ng::Canvas::draw_line (double x1, double y1, double x2, double y2) {
	Vec v1, v2;
	v1.init2(x1, y1);
	v2.init2(x2, y2);
	v1.relative_to_absolute2(&this->space);
	v2.relative_to_absolute2(&this->space);
	
	if (this->root) {
		this->graphics->draw_line(v1.x, v1.y, v2.x, v2.y);
	} else {
		this->parent->draw_line(v1.x, v1.y, v2.x, v2.y);
	}
}

void ng::Canvas::draw_point (double x, double y) {
	Vec v;
	v.init2(x, y);
	v.relative_to_absolute2(&this->space);
	
	if (this->root) {
		this->graphics->draw_point(v.x, v.y);
	} else {
		this->parent->draw_point(v.x, v.y);
	}
}

// Advanced graphics
void ng::Canvas::draw_text (Tileset* const tileset, const char* str, const Space* dest) {
	if (this->root) {
		Rect s, tile, d;
		s.init2(0.0, 0.0, 1.0, 1.0);
		tile.init2(0.0, 0.0, 1.0, 1.0);
		
		int c, tc;
		tc = static_cast<int>(tileset->space.c);
		for (int i=0; str[i] != '\0'; i++) {
			if (str[i] == '\n') {
				tile.x = 0.0;
				tile.y += 1.0;
				if (tile.y >= dest->r) {
					return;
				}
				continue;
			}
			
			c = static_cast<int>(str[i]);
			s.x = static_cast<double>(c % tc);
			s.y = static_cast<double>(c / tc);
			d = tile;
			d.relative_to_absolute2(dest);
			this->draw_tile(tileset, &s, &d);
			
			tile.x += 1.0;
			if (tile.x >= dest->c) {
				tile.x = 0.0;
				tile.y += 1.0;
				if (tile.y >= dest->r) {
					return;
				}
			}
		}
		
	} else {
		Space d = *dest;
		d.relative_to_absolute2_i(&this->space);
		this->parent->draw_text(tileset, str, &d);
	}
}

void ng::Canvas::draw_tile (Tileset* const tileset, const Rect* src, const Rect* dest) {
	Rect d = *dest;
	d.relative_to_absolute2(&this->space);
	
	if (this->root) {
		Rect s = *src;
		s.x += tileset->offset.x;
		s.y += tileset->offset.y;
		s.relative_to_absolute2(&tileset->space);
		this->graphics->draw_image(tileset->image, &s, &d);
	} else {
		this->parent->draw_tile(tileset, src, &d);
	}
}

// Gui elements


