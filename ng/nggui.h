
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGUI_H
#define NGGUI_H

#include "ngcore.h"
#include "nggraphics.h"

namespace ng {
	
	enum EnumCanvasMode {
		CanvasRoot = 0, // root canvas. no translation, no scale.
		CanvasRect = 1, // translate relative to rect.
		CanvasGrid = 2, // translate relative to rect and scale to grid.
		CanvasScale = 3 // scale relative to rect.
	};
	
	/*
	// Rect
		int contains (int x, int y) const;
		int overlaps (const Rect*) const;
		
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
	*/
	
	/*
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
	*/
	
	/*
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
		
		// get a graphics rect for drawing this hitbox.
		void get_rect (Rect* const) const;
		
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
	
	class Canvas {
	public:
		// These are set internally by member functions.
		// They may be viewed from outside the class.
		Graphics* graphics;
		Canvas* parent;
		int mode; // EnumCanvasMode
		
		// These are public.
		Rect rect;
		Grid grid;
		//Scale scale;
		
		void init_root (Graphics*); // root canvas
		void init (Canvas*, const Rect*); // rect canvas
		void init (Canvas*, const Rect*, const Grid*); // grid canvas
		void init_scale (Canvas*, const Rect*); // scale canvas
		//void set_grid (const Grid*);
		//void set_scale (const Scale*);
		//void remove_grid ();
		//void remove_scale ();
		
		// re-calculate scale between this rect and parent rect.
		//void rescale ();
		
		// Given event mouse point on root canvas, find mouse point on this canvas.
		void get_mouse (Vec* const);
		
		// Draw this rect on parent.
		// Clearing root canvas calls graphics clear().
		void clear ();
		void clear (int draw);
		
		// Usually does nothing.
		// Drawing root canvas calls graphics draw().
		void draw ();
		
		// Graphics primitives
		void draw_text (Tileset* const, const char*, const Rect*, const Grid*);
		void draw_tile (Tileset* const, const Rect*, const Rect*);
		void draw_image (Image* const);
		void draw_image (Image* const, const Rect*);
		void draw_image (Image* const, const Rect*, const Rect*);
		void draw_rect (const Rect*, int draw);
		void draw_line (int x1, int y1, int x2, int y2);
		void draw_point (int x, int y);
		
		// Gui elements
	};
	
}

#endif


