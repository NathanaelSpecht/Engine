
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
		
		void init (Image*, const Space*);
		void init (Image*, const Rect*);
		void init_c (Image*, const Rect*, double c, double r);
		void init_i (Image*, const Rect*, double i, double j);
	};
	
	class Canvas {
	public:
		Graphics* graphics;
		Canvas* parent;
		bool root;
		Space space;
		
		void init (Graphics*);
		void init (Canvas*, const Space*);
		
		// Given event mouse point on root canvas, find mouse point on this canvas.
		void get_mouse (Vec* const);
		
		// Draw this rect on parent.
		// Clearing root canvas calls graphics clear().
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


