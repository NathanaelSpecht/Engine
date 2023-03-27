
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "nggui.h"
#include "ngmath.h"

/*
void ng::Tileset::init (Image* image, const Rect* rect, int columns, int rows) {
	this->image = image;
	this->rect = *rect;
	this->grid.init(rect, columns, rows);
	this->column_offset = 0;
	this->row_offset = 0;
}
*/

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

/*
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
*/

void ng::Canvas::draw_text (Tileset* const tileset, const char* str,
const Rect* textbox, const Grid* textgrid) {
	switch (this->mode) {
		case ng::CanvasRoot: {
			//this->graphics->draw_text(tileset, str, textbox, textgrid);
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
			//this->graphics->draw_tile(tileset, src, dest);
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


