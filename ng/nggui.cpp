
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggui.h"
#include "ngmath.h"

ng::Text::Text () {
	this->line = 0;
	this->i = 0;
}

ng::Text::~Text () {
	for (size_t line=0; line < this->buffer.size(); line++) {
		this->buffer[line].clear();
	}
}

void ng::Text::reset () {
	for (size_t line=0; line < this->buffer.size(); line++) {
		this->buffer[line].clear();
	}
	this->buffer.clear();
	this->line = 0;
	this->i = 0;
}

// If result will be in-bounds, set/move cursor and return true.
// Else can't set/move cursor, so return false.
bool ng::Text::set_cursor (int line, int i) {
	size_t sline, si;
	sline = static_cast<size_t>(line);
	si = static_cast<size_t>(i);
	if (line < 0 || sline > this->buffer.size() || i < 0 || si > this->buffer[sline].size()) {
		return false;
	}
	
	this->line = sline;
	this->i = si;
	
	return true;
}

// Move forward/backward at end/start of line to wrap to prev/next line.
bool ng::Text::move_next_line () {
	if (this->line >= this->buffer.size()) {
		return false;
	}
	
	this->line++;
	if (this->i > this->buffer[this->line].size()) {
		this->i = this->buffer[this->line].size();
	}
	
	return true;
}

bool ng::Text::move_prev_line () {
	if (this->line == 0) {
		return false;
	}
	
	this->line--;
	if (this->i > this->buffer[this->line].size()) {
		this->i = this->buffer[this->line].size();
	}
	
	return true;
}

bool ng::Text::move_next () {
	if (this->line >= this->buffer.size()) {
		return false;
	}
	
	if (this->i == this->buffer[this->line].size()) {
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
			this->i = this->buffer[this->line].size();
		}
	} else {
		this->i--;
	}
	
	return true;
}

// Add/remove a line of text at the end.
void ng::Text::push_line (const char* s) {
	std::string str(s);
	this->buffer.push_back(str);
}

void ng::Text::pop_line () {
	if (this->buffer.size() > 0) {
		this->buffer[this->buffer.size() - 1].clear();
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
// Cut and copy return a newed string which must be deleted
// Cut also resets this text.
std::string* ng::Text::cut () {
	// TODO
	std::string* str = new std::string();
	return str;
}

std::string* ng::Text::copy () {
	// TODO
	std::string* str = new std::string();
	return str;
}

void ng::Text::paste (const std::string* str) {
	// TODO
}

// Get next char or a pointer to next line, and advance cursor.
// Returns nul or NULL for end of text.
char ng::Text::next () {
	size_t line, i;
	line = this->line;
	i = this->i;
	if (line >= this->buffer.size()) {
		return '\0';
	} else if (i >= this->buffer[line].size()) {
		bool bb = this->move_next();
		return '\n';
	}
	
	bool b = this->move_next();
	
	return this->buffer[line][i];
}

const std::string* ng::Text::next_line () {
	size_t line;
	line = this->line;
	if (line >= this->buffer.size()) {
		return NULL;
	}
	
	bool b = this->move_next_line();
	this->i = 0;
	
	return &this->buffer[line];
}

ng::Tileset::Tileset () {
	this->image = NULL;
	this->grid.set(1.0, 1.0, 0.0, 0.0);
	this->offset.set(0.0, 0.0);
}

ng::Tileset::~Tileset () {}

void ng::Tileset::set (Image* image) {
	this->image = image;
	this->grid.set(1.0, 1.0, image->w, image->h);
	this->offset.set(0.0, 0.0);
}

void ng::Tileset::set (Image* image, double c, double r) {
	this->image = image;
	this->grid.set(ng::units(c, image->w), ng::units(r, image->h), c, r);
	this->offset.set(0.0, 0.0);
}

void ng::Tileset::set (Image* image, double x, double y, double c, double r) {
	this->image = image;
	this->grid.set(x, y, ng::units(c, image->w), ng::units(r, image->h), c, r);
	this->offset.set(0.0, 0.0);
}

void ng::Tileset::set (Image* image, const Vec2* p, double c, double r) {
	this->image = image;
	this->grid.set(p, ng::units(c, image->w), ng::units(r, image->h), c, r);
	this->offset.set(0.0, 0.0);
}

void ng::Tileset::set (Image* image, const Grid2* grid) {
	this->image = image;
	this->grid = *grid;
	this->offset.set(0.0, 0.0);
}

void ng::Tileset::absolute (Rect2* const rect) const {
	rect->p.x += this->offset.x;
	rect->p.y += this->offset.y;
	this->grid.absolute(rect);
}

ng::Button::Button () {}

ng::Button::~Button () {}

void ng::Button::set (const char* str, double text_scale, double x, double y, double w, double h) {
	this->text.reset();
	this->text.push_line(str);
	double i, j;
	i = h*text_scale*0.5;
	j = h*text_scale;
	this->text_grid.set(x - (w*0.5), y - (h*0.5),
		i, j, ng::columns(i, w), ng::columns(j, h));
	this->text_color.set(255, 255, 255);
	this->rect.set(x, y, w, h);
	this->fill_color.set(0, 0, 0);
	this->frame_color.set(255, 255, 255);
}

void ng::Button::set (const char* str, double text_scale, const Color* text_color,
double x, double y, double w, double h, const Color* fill, const Color* frame) {
	this->text.reset();
	this->text.push_line(str);
	double i, j;
	i = h*text_scale*0.5;
	j = h*text_scale;
	this->text_grid.set(x - (w*0.5), y - (h*0.5),
		i, j, ng::columns(i, w), ng::columns(j, h));
	this->text_color = *text_color;
	this->rect.set(x, y, w, h);
	this->fill_color = *fill;
	this->frame_color = *frame;
}

bool ng::Button::contains (const Vec2* p) const {
	return this->rect.contains(p);
}

ng::Label::Label () {}

ng::Label::~Label () {}

void ng::Label::set (const char* str, double lines, double x, double y, double w, double h) {
	this->text.reset();
	this->text.push_line(str);
	this->text_grid.set(x - (w*0.5), y - (h*0.5),
		ng::units(lines*2.0, w), ng::units(lines, h), lines*2.0, lines);
	this->text_color.set(255, 255, 255);
	this->rect.set(x, y, w, h);
}

void ng::Label::set (const char* str, double lines, const Color* text_color,
double x, double y, double w, double h) {
	this->text.reset();
	this->text.push_line(str);
	this->text_grid.set(x - (w*0.5), y - (h*0.5),
		ng::units(lines*2.0, w), ng::units(lines, h), lines*2.0, lines);
	this->text_color = *text_color;
	this->rect.set(x, y, w, h);
}

bool ng::Label::contains (const Vec2* p) const {
	return this->rect.contains(p);
}

ng::Canvas::Canvas () {
	this->graphics = NULL;
	this->parent = NULL;
	this->root = false;
}

ng::Canvas::~Canvas () {}

void ng::Canvas::set (Graphics* graphics, double w, double h) {
	this->graphics = graphics;
	this->parent = NULL;
	this->root = true;
	this->space.set(w * 0.5, h * 0.5, 1.0, 1.0);
	this->w = w;
	this->h = h;
}

void ng::Canvas::set (Graphics* graphics, double x, double y, double w, double h) {
	this->graphics = graphics;
	this->parent = NULL;
	this->root = true;
	this->space.set(x, y, 1.0, 1.0);
	this->w = w;
	this->h = h;
}

void ng::Canvas::set (Graphics* graphics, const Space2* space, double w, double h) {
	this->graphics = graphics;
	this->parent = NULL;
	this->root = true;
	this->space = *space;
	this->w = w;
	this->h = h;
}

void ng::Canvas::set (Canvas* canvas, double x, double y, double w, double h) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->root = false;
	this->space.set(x, y, 1.0, 1.0);
	this->w = w;
	this->h = h;
}

void ng::Canvas::set (Canvas* canvas, const Space2* space, double w, double h) {
	this->graphics = canvas->graphics;
	this->parent = canvas;
	this->root = false;
	this->space = *space;
	this->w = w;
	this->h = h;
}

// Get the bounding box for this canvas, relative to this space.
void ng::Canvas::get_rect (Rect2* const rect) const {
	rect->set(0.0, 0.0, this->w, this->h);
}

// Given event mouse point on root canvas, find mouse point on this canvas.
void ng::Canvas::get_mouse (Vec2* const mouse) const {
	if (!this->root) {
		this->parent->get_mouse(mouse);
	}
	this->space.relative(mouse);
}

// Graphics primitives
void ng::Canvas::draw_image (Image* const image) {
	Rect2 src(image->w * 0.5, image->h * 0.5, image->w, image->h);
	Rect2 dest(0.0, 0.0, this->w, this->h);
	this->draw_image(image, &src, &dest);
}

void ng::Canvas::draw_image (Image* const image, const Rect2* dest) {
	Rect2 src(image->w * 0.5, image->h * 0.5, image->w, image->h);
	this->draw_image(image, &src, dest);
}

void ng::Canvas::draw_image (Image* const image, const Rect2* src, const Rect2* dest) {
	Rect2 d = *dest;
	this->space.absolute(&d);
	
	if (this->root) {
		this->graphics->draw_image(image, src, &d);
	} else {
		this->parent->draw_image(image, src, &d);
	}
}

void ng::Canvas::draw_rect (const Rect2* dest, int draw) {
	Rect2 d = *dest;
	this->space.absolute(&d);
	
	if (this->root) {
		this->graphics->draw_rect(&d, draw);
	} else {
		this->parent->draw_rect(&d, draw);
	}
}

void ng::Canvas::draw_line (const Line2* line) {
	Line2 l = *line;
	this->space.absolute(&l);
	
	if (this->root) {
		this->graphics->draw_line(&l);
	} else {
		this->parent->draw_line(&l);
	}
}

void ng::Canvas::draw_point (const Vec2* p) {
	Vec2 v = *p;
	this->space.absolute(&v);
	
	if (this->root) {
		this->graphics->draw_point(&v);
	} else {
		this->parent->draw_point(&v);
	}
}

// Advanced graphics
void ng::Canvas::draw_text (Tileset* const tileset, Text* const text, const Grid2* dest) {
	Rect2 s, tile, d;
	s.set(0.5, 0.5, 1.0, 1.0);
	tile.set(0.5, 0.5, 1.0, 1.0);
	
	int text_line, text_i;
	text_line = text->line;
	text_i = text->i;
	char ch;
	
	double c;
	while ((ch = text->next()) != '\0') {
		if (ch == '\n') {
			tile.p.x = 0.5;
			tile.p.y += 1.0;
			if (tile.p.y >= dest->r) {
				return;
			}
			continue;
		}
		
		c = static_cast<double>(ch);
		s.p.x = fmod(c, tileset->grid.c) + 0.5;
		s.p.y = floor(c / tileset->grid.c) + 0.5;
		d = tile;
		dest->absolute(&d);
		this->draw_tile(tileset, &s, &d);
		
		tile.p.x += 1.0;
		if (tile.p.x >= dest->c) {
			tile.p.x = 0.5;
			tile.p.y += 1.0;
			if (tile.p.y >= dest->r) {
				return;
			}
		}
	}
	
	text->set_cursor(text_line, text_i);	
}

void ng::Canvas::draw_tile (Tileset* const tileset, const Rect2* src, const Rect2* dest) {
	Rect2 s = *src;
	tileset->absolute(&s);
	this->draw_image(tileset->image, &s, dest);
}

// Gui elements
void ng::Canvas::draw_button (Tileset* const tileset, Button* const button) {
	this->graphics->set_color(&button->fill_color);
	this->draw_rect(&button->rect, ng::DrawFill);
	this->graphics->set_color(&button->frame_color);
	this->draw_rect(&button->rect, ng::DrawFrame);
	tileset->image->set_color(&button->text_color);
	this->draw_text(tileset, &button->text, &button->text_grid);
}

void ng::Canvas::draw_label (Tileset* const tileset, Label* const label) {
	tileset->image->set_color(&label->text_color);
	this->draw_text(tileset, &label->text, &label->text_grid);
}


