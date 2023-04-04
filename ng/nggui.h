
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGUI_H
#define NGGUI_H

#include "ngcore.h"
#include "nggraphics.h"

namespace ng {
	
	class Tileset {
	public:
		Image* image;
		Space space;
		Vec offset;
		
		Tileset ();
		~Tileset ();
		
		void set (Image*, const Space*);
		void set (Image*, const Rect*);
		void set_c (Image*, const Rect*, double c, double r);
		void set_i (Image*, const Rect*, double i, double j);
	};
	
	class Canvas {
	public:
		Graphics* graphics;
		Canvas* parent;
		Space space;
		// root draws to graphics. non-root draws to parent canvas.
		bool root;
		// relative draws relative_to_absolute(this space).
		// non-relative scales from this space to parent space/graphics rect.
		bool relative;
		
		Canvas ();
		~Canvas ();
		
		void set (Graphics*);
		void set_c (Graphics*, double c, double r);
		void set_i (Graphics*, double i, double j);
		void set (Canvas*, const Space*);
		void set (Canvas*, double x, double y, double w, double h);
		void set_c (Canvas*, double x, double y, double w, double h, double c, double r);
		void set_i (Canvas*, double x, double y, double w, double h, double i, double j);
		
		// scale from parent/graphics to this.
		void scale_in (Vec* const);
		void scale_in (Rect* const);
		void scale_in (Space* const);
		// scale from this to parent/graphics.
		void scale_out (Vec* const);
		void scale_out (Rect* const);
		void scale_out (Space* const);
		
		// Given event mouse point on root canvas, find mouse point on this canvas.
		void get_mouse (Vec* const);
		
		// Draw this space on parent.
		void clear ();
		
		// Usually does nothing.
		// Drawing root canvas calls graphics draw().
		void draw ();
		
		// Graphics primitives
		void draw_image (Image* const);
		void draw_image (Image* const, const Rect*);
		void draw_image (Image* const, const Rect*, const Rect*);
		void draw_rect (const Rect*, int draw);
		void draw_line (double x1, double y1, double x2, double y2);
		void draw_point (double x, double y);
		
		// Advanced graphics
		void draw_text (Tileset* const, const char*, const Space*);
		void draw_tile (Tileset* const, const Rect*, const Rect*);
		
		// Gui elements
	};
	
}

#endif


