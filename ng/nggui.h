
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
	
	/*
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
	*/
	
	class Tileset {
	public:
		Image* image;
		Mat3 tile_space
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
		Label label;
		Box2 box;
		Color fill_color;
		Color frame_color;
		
		Button ();
		~Button ();
		
		void set (const std::string& text, const Mat3& text_space);
		void set (const std::string& text, const Mat3& text_space,
			const Color* text_color, const Color* fill_color, const Color* frame_color);
		bool contains (const Vec2* p) const;
	};
	
	class Label {
	public:
		std::string text;
		Mat3 text_space
		Color text_color;
		Box2 text_box;
		
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
		bool root; // root draws to graphics. non-root draws to parent canvas.
		Box2 box;
		Mat3 space;
		
		Canvas ();
		
		void set (Graphics* graphics, const Mat3& space); // root
		void set (Canvas* canvas, const Mat3& space); // non-root
		
		// Given event mouse point on graphics, find mouse point on this canvas.
		void get_mouse (Vec2* const) const;
		
		// Draw canvas box.
		void draw (int draw);
		
		// Graphics primitives
		void draw_image (Image* const image);
		void draw_image (Image* const image, const Box2& dest);
		void draw_image (Image* const image, const Rect2& src, const Box2& dest);
		void draw_image (Image* const image, const Rect2& src, const Box2& dest,
			double angle, int flip);
		void draw_box (const Box2& dest, int draw);
		void draw_line (const Vec2& p1, const Vec2& p2);
		void draw_point (const Vec2& p);
		
		// Advanced graphics
		void draw_text (Tileset* const, const std::string& text, const Mat3& dest_space);
		void draw_tile (Tileset* const, const Rect2& src, const Box2& dest);
		
		// Gui elements
		void draw_button (Tileset* const, Button* const);
		void draw_label (Tileset* const, Label* const);
	};
	
}

#endif


