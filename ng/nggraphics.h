
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGRAPHICS_H
#define NGGRAPHICS_H

#include "ngcore.h"

namespace ng {

	enum EnumFlipMode {
		FlipX = 1, // flip x coords (horizontal flip) (NOT flip over x axis)
		FlipY = 2, // flip y coords (vertical flip) (NOT flip over y axis)
		FlipXY = 3 // flip both (rotate 180 degrees)
	};

	enum EnumDrawMode {
		DrawFrame = 0,
		DrawFill = 1
	};
	
	// Vec may represent a vector or point.
	class Vec {
	public:
		int x;
		int y;
		// int z; // todo
		
		void init (int x, int y);
		void scale (const Scale*);
		void scale_inv (const Scale*);
		void absolute_to_relative (const Rect*);
		void absolute_to_relative (const Grid*);
		void absolute_to_relative (const Rect*, const Grid*);
		void relative_to_absolute (const Rect*);
		void relative_to_absolute (const Grid*);
		void relative_to_absolute (const Rect*, const Grid*);
		void portal (const Rect* src, const Rect* dest);
	};
	
	/*
	// TODO
	// Replace Circle with Hitbox.
	// Remove Rect collision functions -> move to Hitbox.
	
	class Hitbox {
	public:
		int shape; // EnumShape {Square, Circle}
		// center point
		int x;
		int y;
		// int z; // todo
		// axis/radius from center. a==b means Square/Circle. a!=b means Rect/Ellipse.
		int a;
		int b;
		// int c;
		
		void init (int shape, int x, int y, int r); // Sets symmetry to Radius
		void init (int shape, int x, int y, int a, int b); // Sets symmetry to Axis
		
		void scale (const Scale*);
		void scale_inv (const Scale*);
		
		// true if this contains (x, y).
		bool contains (int x, int y) const;
		
		// true if this overlaps h.
		bool overlaps (const Hitbox* h) const;
		
		// true if this will collide with h as a result of movement by v.
		// assumes this is same shape as h.
		bool collides (const Vec* v, const Hitbox* h) const;
		
		// collide this with h, and reduce v to remaining motion.
		// assumes this collides with, and is the same shape as, h.
		void collide (Vec* const v, const Hitbox* h);
		
		// true if the ray (this.x, this.y, in the direction of v) intersects h.
		bool intersects (const Vec* v, const Hitbox* h) const;
		
		// intersect this with h (as defined above), and reduce v to remaining motion.
		// assumes this intersects h.
		void intersect (Vec* const v, const Hitbox* h);
		
		// move this by v, and reduce v to 0.
		void moveby (Vec* const v);
		
		// move this to (x, y), and reduce v to remaining motion.
		void moveto (Vec* const v, int x, int y);
	};
	*/
	
	class Circle {
	public:
		int x;
		int y;
		// int z; // todo
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
		// int z; // todo
		int w;
		int h;
		// int d;
		
		void init (int x, int y, int w, int h);
		void scale (const Scale*);
		void scale_inv (const Scale*);
		int contains (int x, int y) const;
		int overlaps (const Rect*) const;
		void absolute_to_relative (const Rect*);
		void absolute_to_relative (const Grid*);
		void absolute_to_relative (const Rect*, const Grid*);
		void relative_to_absolute (const Rect*);
		void relative_to_absolute (const Grid*);
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
	
	class Scale {
	public:
		float x;
		float y;
		// float z; // todo
		float x_inv; // 1 / x
		float y_inv; // 1 / y
		// float z_inv; // 1 / z
		
		// No scale.
		void init ();
		
		// Compute x_inv and y_inv scales from x and y.
		void init (float x, float y);
		
		void init (float x, float y, float x_inv, float y_inv);
		void init (const Grid*);
		
		// Compute scale of grid tiles from columns.
		void init (const Rect* r, int columns, int rows);
		
		// Compute scale between two rects.
		void init (const Rect* src, const Rect* dest);
		
		void inverse ();
		void scale (const Scale*);
		void scale_inv (const Scale*);
		void relative_to_absolute (const Scale*);
		void absolute_to_relative (const Scale*);
		void portal (const Rect* src, const Rect* dest);
	};
	
	class Grid {
	public:
		int columns;
		int rows;
		// Note: there is no standard term for "depth column".
		// Terms often used are: aisle, layer, page, sheet, and slice.
		// int layers; // todo
		float tile_w;
		float tile_h;
		// float tile_d;
		// float multiply is 10x speed of divide, so multiply by inverse instead of dividing.
		float tile_w_inv; // 1 / tile_w
		float tile_h_inv; // 1 / tile_h
		// float tile_d_inv; // 1 / tile_d
		
		void set_tile (const Scale*);
		void init (const Rect*);
		void init (const Rect*, int columns, int rows);
		
		void scale (const Scale*);
		void scale_inv (const Scale*);
		void absolute_to_relative (const Grid*);
		void relative_to_absolute (const Grid*);
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
		
		void draw_text (Tileset* const, const char*, const Rect*, const Grid*);
		void draw_tile (Tileset* const, const Rect*, const Rect*);
		
		// Draw whole image to whole window.
		void draw_image (Image* const);
		
		// Draw whole image to part of window.
		void draw_image (Image* const, const Rect*);
		
		// Draw part of image to part of window.
		void draw_image (Image* const, const Rect*, const Rect*);
		
		void draw_rect (const Rect*, int draw);
		void draw_line (int x1, int y1, int x2, int y2);
		void draw_point (int x, int y);
	};

}

#endif


