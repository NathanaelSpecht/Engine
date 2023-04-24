
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGGRAPHICS_H
#define NGGRAPHICS_H

#include "ngcore.h"
#include "ngvec.h"

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
	
	// Switch between window and graphics coordinates.
	// Window (0,0) is top-left corner, +x points right, and +y points down.
	// Graphics (0,0) is center, +x points right, and +y points up.
	// These are used internally by the graphics draw functions.
	double window_x (double x, double rx);
	double window_y (double y, double ry);
	double graphics_x (double x, double rx);
	double graphics_y (double y, double ry);
	
	Rect2 window_rect (const Box2& a, double rx, double ry);
	SDL_Rect sdl_rect (const Rect2& a);
	SDL_RendererFlip sdl_flip (int flip);
	
	// Draw a message box.
	// These functions may be called at any time, even before ng::init().
	// Blocks execution of main thread until user clicks a button or closes the window.
	void draw_errormsg (const std::string& title, const std::string& msg);
	void draw_warningmsg (const std::string& title, const std::string& msg);
	void draw_infomsg (const std::string& title, const std::string& msg);
	
	class Color {
	public:
		int r;
		int g;
		int b;
		int a;
		Color ();
		Color (int r, int g, int b);
		Color (int r, int g, int b, int a);
		Color (const Color& color);
		void set (int r, int g, int b);
		void set (int r, int g, int b, int a);
	};
	
	class Image {
	public:
		SDL_Texture* texture;
		double w;
		double h;
		Color color;
		
		Image ();
		~Image ();
		
		void load (Graphics* const graphics, const char* file, const Color& key);
		void set_color (const Color& color);
		void set_alpha (const Color& color);
	};
	
	class Graphics {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		double rx;
		double ry;
		Color color;
		
		Graphics ();
		
		void open (const char* title, double rx, double ry);
		void close ();
		void set_color (const Color& color);
		void set_alpha (const Color& color);
		void set_window_dim (const Vec2& dim);
		void set_dim (const Vec2& dim);
		Vec2 window_dim () const;
		Vec2 dim () const;
		
		void clear ();
		void draw ();
		
		// Draw a message box.
		// Blocks execution of main thread until user clicks a button or closes the window.
		void draw_errormsg (const std::string& title, const std::string& msg);
		void draw_warningmsg (const std::string& title, const std::string& msg);
		void draw_infomsg (const std::string& title, const std::string& msg);
		
		// Draw whole image to whole window.
		void draw_image (Image* const image);
		
		// Draw whole image to part of window.
		void draw_image (Image* const image, const Box2& dest);
		
		// Draw part of image to part of window.
		void draw_image (Image* const image, const Rect2& src, const Box2& dest);
		void draw_image (Image* const image, const Rect2& src, const Box2& dest,
			double angle, int flip);
		
		// Draw shape.
		void draw_box (const Box2& box, int draw);
		void draw_line (const Vec2& p1, const Vec2& p2);
		void draw_point (const Vec2& p);
	};

}

#endif


