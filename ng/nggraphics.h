
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
		
		Color ();
		~Color ();
		
		void set (int r, int g, int b);
		void set (int r, int g, int b, int a);
	};
	
	class Image {
	public:
		SDL_Texture* texture;
		double w;
		double h;
		Color color;
		int flip;
		
		Image ();
		~Image ();
		
		void load (Graphics* const, const char* file, const Color* key);
		void set_color (const Color*);
		void set_alpha (const Color*);
		void set_flip (int flip);
	};
	
	class Graphics {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		double w;
		double h;
		Color color;
		
		Graphics ();
		~Graphics ();
		
		void open (const char* title, double w, double h);
		void close ();
		void set_color (const Color*);
		void set_alpha (const Color*);
		void clear ();
		void draw ();
		
		// Draw whole image to whole window.
		void draw_image (Image* const);
		
		// Draw whole image to part of window.
		void draw_image (Image* const, const Rect2*);
		
		// Draw part of image to part of window.
		void draw_image (Image* const, const Rect2*, const Rect2*);
		
		void draw_rect (const Rect2*, int draw);
		void draw_line (const Line2*);
		void draw_point (const Vec2*);
	};

}

#endif


