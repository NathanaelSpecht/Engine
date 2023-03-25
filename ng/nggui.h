
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGUI_H
#define NGGUI_H

#include "ngcore.h"
#include "nggraphics.h"

namespace ng {

	enum EnumShape {
		ShapeRect = 0,
		ShapeEllipse = 1
	};

	enum EnumCanvasMode {
		CanvasRoot = 0, // root canvas. no translation, no scale.
		CanvasRect = 1, // translate relative to rect.
		CanvasGrid = 2, // translate relative to rect and scale to grid.
		CanvasScale = 3 // scale relative to rect.
	};
	
	class Hitbox {
	public:
		// center point
		int x;
		int y;
		// int z; // todo
		// radius from center along each axis
		int a;
		int b;
		// int c;
		int shape;
		
		// default shape is rect. change later if you want.
		void init (int x, int y, int a, int b);
		void init (const Rect*);
		void init (const Rect*, const Grid*, int column, int row);
		
		int major () const; // longest radius
		int minor () const; // shortest radius
		
		// get a graphics rect for drawing this hitbox.
		void get_rect (Rect* const) const;
		
		void scale (const Scale*);
		void scale_inv (const Scale*);
		
		// Generic Hitbox:
		// If shapes are the same, it will use the correct collider.
		// If shapes are different, it uses the collider for the larger shape.
		int get_shape (const Hitbox* h) const;
		
		// true if this contains (x, y).
		bool contains (int x, int y) const;
		
		// true if this overlaps h.
		bool overlaps (const Hitbox* h) const;
		
		// true if this will collide with h as a result of movement by v.
		bool collides (const Vec* v, const Hitbox* h) const;
		
		// collide this with h, and reduce v to remaining motion.
		// true if this collides with h.
		bool collide (Vec* const v, const Hitbox* h);
		
		// true if the point vector (this.x, this.y, v.x, v.y) intersects h.
		bool intersects (const Vec* v, const Hitbox* h) const;
		
		// intersect this with h (as defined above), and reduce v to remaining motion.
		// true if this intersects h.
		bool intersect (Vec* const v, const Hitbox* h);
		
		// Rect Hitbox:
		bool rect_contains (int x, int y) const;
		bool rect_overlaps (const Hitbox* h) const;
		bool rect_collides (const Vec* v, const Hitbox* h) const;
		bool rect_collide (Vec* const v, const Hitbox* h);
		bool rect_intersects (const Vec* v, const Hitbox* h) const;
		bool rect_intersect (Vec* const v, const Hitbox* h);
		
		// Ellipse Hitbox: (or Circle if a==b) TODO
		bool ellipse_contains (int x, int y) const;
		bool ellipse_overlaps (const Hitbox* h) const;
		bool ellipse_collides (const Vec* v, const Hitbox* h) const;
		bool ellipse_collide (Vec* const v, const Hitbox* h);
		bool ellipse_intersects (const Vec* v, const Hitbox* h) const;
		bool ellipse_intersect (Vec* const v, const Hitbox* h);
		
		// move this by v, and reduce v to 0.
		void moveby (Vec* const v);
		
		// move this to (x, y), and reduce v to remaining motion.
		void moveto (Vec* const v, int x, int y);
	};
	
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


