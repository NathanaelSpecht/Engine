
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGRAPHICS_H
#define NGGRAPHICS_H

#include "ngcore.h"
#include "ngmath.h"

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
	
	class Graphics {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		Rect rect;
		Color color;
		
		void init (const char* title, double w, double h);
		void quit ();
		void set_color (const Color*);
		void set_alpha (const Color*);
		void clear ();
		void draw ();
		
		// Draw whole image to whole window.
		void draw_image (Image* const);
		
		// Draw whole image to part of window.
		void draw_image (Image* const, const Rect*);
		
		// Draw part of image to part of window.
		void draw_image (Image* const, const Rect*, const Rect*);
		
		void draw_rect (const Rect*, int draw);
		void draw_line (double x1, double y1, double x2, double y2);
		void draw_point (double x, double y);
	};

}

#endif


