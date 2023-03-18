
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGRAPHICS_H
#define NGGRAPHICS_H

#include "ngcore.h"

namespace ng {

enum EnumFlip {
	FlipX = 1, // flip x coords (horizontal flip) (NOT flip over x axis)
	FlipY = 2, // flip y coords (vertical flip) (NOT flip over y axis)
	FlipXY = 3 // flip both (rotate 180 degrees)
};

enum EnumDraw {
	DrawFrame = 0,
	DrawFill = 1
};

class Vec {
public:
	int x;
	int y;
	int z; // z defaults to 0.
	int w; // magnitude defaults to 1.
	
	// vec represents all types of vector, so they can be interchanged.
	void init_2d (int x, int y);
	void init_2d (int x, int y, int w);
	void init_3d (int x, int y, int z);
	void init_3d (int x, int y, int z, int w);
};

class Circle {
public:
	int x;
	int y;
	int r;
	
	void init (int x, int y, int r);
	
	// return true/edge/false if circle contains (x, y).
	int contains (int x, int y) const;
	
	// return true/edge/false if circles overlap/touch.
	int overlaps (const Circle*) const;
	
	// return true/edge/false if circle a collided with stationary circle b, and
	// move circle a by the part of its vec v that gets it to collide, and
	// reduce vec v to the remaining motion.
	// edge means they will touch and not move any further.
	// assumes circles are not overlapping.
	int collide (Vec* const v, const Circle* b);
};

class Rect {
public:
	int x;
	int y;
	int w;
	int h;
	
	void init (int x, int y, int w, int h);
	void get_SDL_Rect (SDL_Rect* const) const;
	int contains (int x, int y) const;
	int overlaps (const Rect*) const;
	void absolute_to_relative (const Rect*, const Grid*);
	void relative_to_absolute (const Rect*, const Grid*);
	void portal (const Rect* src, const Rect* dest);
	
	// move rect by vec, consuming vec in the process (vec -> 0). 2d.
	void moveby (Vec* const);
	
	// move rect to (x, y), and reduce vec to the remaining motion. 2d.
	// assumes (x, y) is in the direction of vec.
	void moveto (Vec* const, int x, int y);
	
	// return true/edge/false if rect a collided with stationary rect b, and
	// move rect a by the part of its vec v that gets it to collide, and
	// reduce vec v to the remaining motion.
	// edge means they will touch and not move any further.
	// assumes rects are not overlapping.
	int collide (Vec* const v, const Rect* b);
};

class Grid {
public:
	int columns;
	int rows;
	float tile_w;
	float tile_h;
	
	// float multiply is 10x speed of divide, so multiply by inverse instead of dividing.
	float tile_w_inv; // 1 / tile_w
	float tile_h_inv; // 1 / tile_h
	
	void init (const Rect*, int columns, int rows);
	void portal (const Rect* src, const Rect* dest);
};

class Color {
public:
	int r;
	int g;
	int b;
	int a;
	
	void init (int r, int g, int b);
	void init (int r, int g, int b, int a);
};

class Image {
public:
	SDL_Texture* texture;
	Rect rect;
	Color color;
	int flip;
	double angle;
	
	void init (Graphics* const, const char* file, const Color* key);
	void quit ();
	void set_color (const Color*);
	void set_alpha (const Color*);
	void set_flip (int flip);
	void set_angle (double angle);
};

class Tileset {
public:
	Image* image;
	Rect rect;
	Grid grid;
	int column_offset;
	int row_offset;
	
	void init (Image*, const Rect*, int columns, int rows);
};

class Graphics {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Rect rect;
	Color color;
	
	void init (const char* title, int w, int h);
	void quit ();
	void set_color (const Color*);
	void set_alpha (const Color*);
	void clear ();
	void draw ();
	
	void draw_image (Image* const, const Rect*, const Rect*);
	void draw_rect (const Rect*, int draw);
	void draw_line (int x1, int y1, int x2, int y2);
	void draw_point (int x, int y);
	
	void draw_tile (Tileset* const, const Rect*, const Rect*);
	void draw_text (Tileset* const, const char*, const Rect*, const Grid*);
	
	/*
	void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame,
		int w_frames, int h_frames, const char* str, int di);
	void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame,
		int w_frames, int h_frames);
	*/
};

}

#endif


