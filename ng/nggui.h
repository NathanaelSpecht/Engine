
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


