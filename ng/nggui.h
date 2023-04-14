
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGUI_H
#define NGGUI_H

#include "ngcore.h"
#include "nggraphics.h"
#include <string>

namespace ng {

	enum EnumButtonTile {
		TilePress = 0,
		TileRelease = 1
	};
	
	// represents text as a set of lines.
	class Text {
	public:
		std::vector<std::string> buffer;
		size_t line;
		size_t i;
		
		Text ();
		~Text ();
		
		void reset ();
		
		// If result will be in-bounds, set/move cursor and return true.
		// Else can't set/move cursor, so return false.
		bool set_cursor (int line, int i);
		// Move forward/backward at end/start of line to wrap to prev/next line.
		bool move_next_line ();
		bool move_prev_line ();
		bool move_next ();
		bool move_prev ();
		
		// Add/remove a line of text at the end.
		void push_line (const char*);
		void pop_line ();
		
		// Perform text-entry operation, as-if by typing.
		// Ascii char.
		void enter (char);
		// UTF-8 char.
		void enter (const char*);
		
		// Perform copy/paste operations on entire text.
		// Cut and copy return a newed string which must be deleted
		// Cut also resets this text.
		std::string* cut ();
		std::string* copy ();
		void paste (const std::string*);
		
		// Get next char or a pointer to next line, and advance cursor.
		// Returns nul or NULL for end of text.
		char next ();
		const std::string* next_line ();
	};
	
	class Tileset {
	public:
		Image* image;
		Grid2 grid;
		Vec2 offset; // relative to grid
		
		Tileset ();
		~Tileset ();
		
		void set (Image* image);
		void set (Image* image, double c, double r);
		void set (Image* image, double x, double y, double c, double r);
		void set (Image* image, const Vec2* p, double c, double r);
		void set (Image* image, const Grid2* grid);
		
		void absolute (Rect2* const rect) const;
	};
	
	class Button {
	public:
		Text text;
		Grid2 text_grid;
		Color text_color;
		Rect2 rect;
		Color fill_color;
		Color frame_color;
		
		Button ();
		~Button ();
		
		void set (const char* str, double text_scale, double x, double y, double w, double h);
		void set (const char* str, double text_scale, const Color* text_color,
			double x, double y, double w, double h, const Color* fill, const Color* frame);
		bool contains (const Vec2* p) const;
	};
	
	class Label {
	public:
		Text text;
		Grid2 text_grid;
		Color text_color;
		Rect2 rect;
		
		Label ();
		~Label ();
		
		void set (const char* str, double lines, double x, double y, double w, double h);
		void set (const char* str, double lines, const Color* text_color,
			double x, double y, double w, double h);
		bool contains (const Vec2* p) const;
	};
	
	class Canvas {
	public:
		Graphics* graphics;
		Canvas* parent;
		Space2 space;
		double w; // w and h are relative to space.
		double h;
		// root draws to graphics. non-root draws to parent canvas.
		bool root;
		
		Canvas ();
		~Canvas ();
		
		void set (Graphics* graphics, double w, double h);
		void set (Graphics* graphics, double x, double y, double w, double h);
		void set (Graphics* graphics, const Space2* space, double w, double h);
		void set (Canvas* canvas, double x, double y, double w, double h);
		void set (Canvas* canvas, const Space2* space, double w, double h);
		
		// Get the bounding box for this canvas, relative to this space.
		void get_rect (Rect2* const) const;
		
		// Given event mouse point on graphics, find mouse point on this canvas.
		void get_mouse (Vec2* const) const;
		
		// Graphics primitives
		void draw_image (Image* const);
		void draw_image (Image* const, const Rect2*);
		void draw_image (Image* const, const Rect2*, const Rect2*);
		void draw_rect (const Rect2*, int draw);
		void draw_line (const Line2*);
		void draw_point (const Vec2*);
		
		// Advanced graphics
		void draw_text (Tileset* const, Text* const, const Grid2*);
		void draw_tile (Tileset* const, const Rect2*, const Rect2*);
		
		// Gui elements
		void draw_button (Tileset* const, Button* const);
		void draw_label (Tileset* const, Label* const);
	};
	
}

#endif


