
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggui.h"
#include "ngmath.h"
#include <cstring>

ng::Text::Text () {
	this->line = 0;
	this->i = 0;
}

ng::Text::~Text () {
	for (size_t line=0; line < this->buffer.size(); line++) {
		if (this->buffer[line] != NULL) {
			std::free(this->buffer[line]);
		}
	}
}

void ng::Text::reset () {
	for (size_t line=0; line < this->buffer.size(); line++) {
		if (this->buffer[line] != NULL) {
			std::free(this->buffer[line]);
			this->buffer[line] = NULL;
		}
	}
	this->buffer.clear();
	this->line = 0;
	this->i = 0;
}

// If result will be in-bounds, set/move cursor and return true.
// Else can't set/move cursor, so return false.
bool ng::Text::set_cursor (int line, int i) {
	if (line < 0 || static_cast<size_t>(line) > this->buffer.size() ||
	i < 0 || static_cast<size_t>(i) > std::strlen(this->buffer[static_cast<size_t>(line)])) {
		return false;
	}
	
	this->line = static_cast<size_t>(line);
	this->i = static_cast<size_t>(i);
	
	return true;
}

// Move forward/backward at end/start of line to wrap to prev/next line.
bool ng::Text::move_next_line () {
	if (this->line >= this->buffer.size()) {
		return false;
	}
	
	this->line++;
	if (this->i > std::strlen(this->buffer[this->line])) {
		this->i = std::strlen(this->buffer[this->line]);
	}
	
	return true;
}

bool ng::Text::move_prev_line () {
	if (this->line == 0) {
		return false;
	}
	
	this->line--;
	if (this->i > std::strlen(this->buffer[this->line])) {
		this->i = std::strlen(this->buffer[this->line]);
	}
	
	return true;
}

bool ng::Text::move_next () {
	if (this->line >= this->buffer.size()) {
		return false;
	}
	
	if (this->i == std::strlen(this->buffer[this->line])) {
		this->i = 0;
		this->line++;
	} else {
		this->i++;
	}
	
	return true;
}

bool ng::Text::move_prev () {
	if (this->line == 0 && this->i == 0) {
		return false;
	}
	
	if (this->i == 0) {
		if (this->line > 0) {
			this->line--;
			this->i = std::strlen(this->buffer[this->line]);
		}
	} else {
		this->i--;
	}
	
	return true;
}

// Add/remove a line of text at the end.
void ng::Text::push_line (const char* s) {
	char* t;
	if (s == NULL) {
		t = NULL;
	} else {
		size_t len = std::strlen(s);
		t = static_cast<char*>(std::malloc((len + 1) * sizeof(char)));
		for (size_t i=0; i < len; i++) {
			t[i] = s[i];
		}
		t[len] = '\0';
	}
	
	this->buffer.push_back(t);
}

void ng::Text::pop_line () {
	if (this->buffer.size() > 0) {
		this->buffer.pop_back();
	}
}

// Perform text-entry operation, as-if by typing.
// Ascii char.
void ng::Text::enter (char c) {
	// TODO
}

// UTF-8 char.
void ng::Text::enter (const char* c) {
	// TODO
}

// Perform copy/paste operations on entire text.
// Cut and copy return a malloc-d c-string, and must be free-d.
// Cut also resets this text.
char* ng::Text::cut () {
	// TODO
	return NULL;
}

char* ng::Text::copy () {
	// TODO
	return NULL;
}

void ng::Text::paste (const char* s) {
	// TODO
}

// Get pointer to current line or NULL for end of text.
char* ng::Text::get_line () {
	if (this->line >= this->buffer.size()) {
		return NULL;
	}
	
	return this->buffer[this->line];
}

// Get next char or a pointer to next line, and advance cursor.
// Returns nul or NULL for end of text.
char ng::Text::next () {
	size_t line, i;
	line = this->line;
	i = this->i;
	if (line >= this->buffer.size()) {
		return '\0';
	} else if (i >= std::strlen(this->buffer[line])) {
		return '\n';
	}
	
	bool b = this->move_next();
	
	return this->buffer[line][i];
}

char* ng::Text::next_line () {
	size_t line;
	line = this->line;
	if (line >= this->buffer.size()) {
		return NULL;
	}
	
	bool b = this->move_next_line();
	this->i = 0;
	
	return this->buffer[line];
}

ng::Tileset::Tileset () {
	this->image = NULL;
}

ng::Tileset::~Tileset () {}

void ng::Tileset::set (Image* image, const Space* space) {
	this->image = image;
	this->space = *space;
	this->offset.set2(0.0, 0.0);
}

void ng::Tileset::set (Image* image, const Rect* rect) {
	this->image = image;
	this->space.set2(rect);
	this->offset.set2(0.0, 0.0);
}

void ng::Tileset::set_c (Image* image, const Rect* rect, double c, double r) {
	this->image = image;
	this->space.set2_c(rect, c, r);
	this->offset.set2(0.0, 0.0);
}

void ng::Tileset::set_i (Image* image, const Rect* rect, double i, double j) {
	this->image = image;
	this->space.set2_i(rect, i, j);
	this->offset.set2(0.0, 0.0);
}

ng::Canvas::Canvas () {
	this->graphics = NULL;
	this->parent = NULL;
	this->root = false;
	this->relative = false;
}

ng::Canvas::~Canvas () {}

void ng::Canvas::set (Graphics* graphics) {
	this->graphics = graphics;
	this->parent = NULL;
	this->space.set2(&graphics->rect);
	this->root = true;
	this->relative = false;
}

void ng::Canvas::set_c (Graphics* graphics, double c, double r) {
	this->graphics = graphics;
	this->parent = NULL;
	this->space.set2_c(&graphics->rect, c, r);
	this->root = true;
	this->relative = false;
}

void ng::Canvas::set_i (Graphics* graphics, double i, double j) {
	this->graphics = graphics;
	this->parent = NULL;
	this->space.set2_i(&graphics->rect, i, j);
	this->root = true;
	this->relative = false;
}

void ng::Canvas::set (Canvas* canvas, const Space* space) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->space = *space;
	this->root = false;
	this->relative = true;
}

void ng::Canvas::set (Canvas* canvas, double x, double y, double w, double h) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->space.set2(x, y, w, h);
	this->root = false;
	this->relative = true;
}

void ng::Canvas::set_c (Canvas* canvas, double x, double y, double w, double h, double c, double r) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->space.set2_c(x, y, w, h, c, r);
	this->root = false;
	this->relative = true;
}

void ng::Canvas::set_i (Canvas* canvas, double x, double y, double w, double h, double i, double j) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->space.set2_i(x, y, w, h, i, j);
	this->root = false;
	this->relative = true;
}

// scale from parent/graphics to this.
void ng::Canvas::scale_in (Vec* const vec) {
	if (this->relative) {
		vec->absolute_to_relative2(&this->space);
	} else {
		Vec s;
		if (this->root) {
			s.set2(&this->graphics->rect, &this->space);
		} else {
			s.set2(&this->parent->space, &this->space);
		}
		vec->scale2(s.x, s.y);
	}
}

void ng::Canvas::scale_in (Rect* const rect) {
	if (this->relative) {
		rect->absolute_to_relative2(&this->space);
	} else {
		Vec s;
		if (this->root) {
			s.set2(&this->graphics->rect, &this->space);
		} else {
			s.set2(&this->parent->space, &this->space);
		}
		rect->scale2(s.x, s.y);
	}
}

void ng::Canvas::scale_in (Space* const space) {
	if (this->relative) {
		space->absolute_to_relative2(&this->space);
	} else {
		Vec s;
		if (this->root) {
			s.set2(&this->graphics->rect, &this->space);
		} else {
			s.set2(&this->parent->space, &this->space);
		}
		space->scale2(s.x, s.y);
	}
}

// scale from this to parent/graphics.
void ng::Canvas::scale_out (Vec* const vec) {
	if (this->relative) {
		vec->relative_to_absolute2(&this->space);
	} else {
		Vec s;
		if (this->root) {
			s.set2(&this->space, &this->graphics->rect);
		} else {
			s.set2(&this->space, &this->parent->space);
		}
		vec->scale2(s.x, s.y);
	}
}

void ng::Canvas::scale_out (Rect* const rect) {
	if (this->relative) {
		rect->relative_to_absolute2(&this->space);
	} else {
		Vec s;
		if (this->root) {
			s.set2(&this->space, &this->graphics->rect);
		} else {
			s.set2(&this->space, &this->parent->space);
		}
		rect->scale2(s.x, s.y);
	}
}

void ng::Canvas::scale_out (Space* const space) {
	if (this->relative) {
		space->relative_to_absolute2(&this->space);
	} else {
		Vec s;
		if (this->root) {
			s.set2(&this->space, &this->graphics->rect);
		} else {
			s.set2(&this->space, &this->parent->space);
		}
		space->scale2(s.x, s.y);
	}
}

// Given event mouse point on root canvas, find mouse point on this canvas.
void ng::Canvas::get_mouse (Vec* const mouse) {
	if (!this->root) {
		this->parent->get_mouse(mouse);
	}
	this->scale_in(mouse);
}

// Draw this->space on parent.
void ng::Canvas::clear () {
	if (this->relative && this->root) {
		this->graphics->draw_rect(&this->space.rect, ng::DrawFill);
	} else if (this->relative && !this->root) {
		this->parent->draw_rect(&this->space.rect, ng::DrawFill);
	} else if (!this->relative && this->root) {
		this->graphics->clear();
	} else {
		this->parent->clear();
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
	this->draw_image(image, &image->rect, &this->space.rect);
}

void ng::Canvas::draw_image (Image* const image, const Rect* dest) {
	this->draw_image(image, &image->rect, dest);
}

void ng::Canvas::draw_image (Image* const image, const Rect* src, const Rect* dest) {
	Rect d = *dest;
	this->scale_out(&d);
	
	if (this->root) {
		this->graphics->draw_image(image, src, &d);
	} else {
		this->parent->draw_image(image, src, &d);
	}
}

void ng::Canvas::draw_rect (const Rect* dest, int draw) {
	Rect d = *dest;
	this->scale_out(&d);
	
	if (this->root) {
		this->graphics->draw_rect(&d, draw);
	} else {
		this->parent->draw_rect(&d, draw);
	}
}

void ng::Canvas::draw_line (double x1, double y1, double x2, double y2) {
	Vec v1, v2;
	v1.set2(x1, y1);
	v2.set2(x2, y2);
	this->scale_out(&v1);
	this->scale_out(&v2);
	
	if (this->root) {
		this->graphics->draw_line(v1.x, v1.y, v2.x, v2.y);
	} else {
		this->parent->draw_line(v1.x, v1.y, v2.x, v2.y);
	}
}

void ng::Canvas::draw_point (double x, double y) {
	Vec v;
	v.set2(x, y);
	this->scale_out(&v);
	
	if (this->root) {
		this->graphics->draw_point(v.x, v.y);
	} else {
		this->parent->draw_point(v.x, v.y);
	}
}

// Advanced graphics
void ng::Canvas::draw_text (Tileset* const tileset, Text* const text, const Space* dest) {
	if (this->root) {
		Rect s, tile, d;
		s.set2(0.0, 0.0, 1.0, 1.0);
		tile.set2(0.0, 0.0, 1.0, 1.0);
		
		int text_line, text_i;
		text_line = text->line;
		text_i = text->i;
		char ch;
		
		int c, tc;
		tc = static_cast<int>(tileset->space.c);
		while ((ch = text->next()) != '\0') {
			if (ch == '\n') {
				tile.x = 0.0;
				tile.y += 1.0;
				if (tile.y >= dest->r) {
					return;
				}
				continue;
			}
			
			c = static_cast<int>(ch);
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
		
		text->set_cursor(text_line, text_i);
		
	} else {
		Space d = *dest;
		this->scale_out(&d);
		this->parent->draw_text(tileset, text, &d);
	}
}

void ng::Canvas::draw_tile (Tileset* const tileset, const Rect* src, const Rect* dest) {
	Rect d = *dest;
	this->scale_out(&d);
	
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


