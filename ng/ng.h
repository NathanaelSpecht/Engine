
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NG_H
#define NG_H

#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <cstdlib>

#include "SDL.h"

// Engie
#define NG_HERE __FILE__ << ":" << __LINE__

namespace ng {

// Use exceptions instead of returning an error code.
// Throw logic_error when parameters fail checks at the start of a function.
// Throw runtime_error when a problem occurs during function execution.
// For example:
/*
if (SDL_Init(...) != 0) {
	throw std::runtime_error(SDL_GetError());
}
...
catch (const std::exception& ex) {
	std::cout << NG_HERE << ": can't init: " << ex.what();
}
*/

// Every code that can be something or nothing, uses ng::None for nothing.
enum EnumNone {
	None = 0
};

// ng::Edge represents a fuzzy condition that could be true, false, or both.
// If you only need true and false, you should use bool instead.
// If you need three mutually exclusive states, you should use your own enum instead.
enum EnumTernary {
	False = 0,
	Edge = 1,
	True = 2
};

void init ();
void quit ();

// Forward declarations, to avoid "has not been declared" compilation errors.
class Time;
class Vec;
class Circle;
class Rect;
class Grid;
class Color;
class Image;
class Graphics;
class Mouse;
class Key;
class Event;
class Clip;
class Sound;
class Channel;
class Audio;

// String
// use <string> and <sstream> instead.

// File
// use <iostream> and <fstream> and <filesystem> instead.

// Time
class Time {
public:
	uint32_t now;
	uint32_t last;
	int64_t ticks;
	int delta;
	int tps;
	int count;
	int ms;
	
	void init ();
	void tick ();
};

// Physics
int contains (int x, int w, int p);
int overlaps (int x1, int w1, int x2, int w2);

// return true/edge/false if x + d crosses axis.
int intercepts (int axis, int x, int d);

// y-intercept along axis. assumes dx != 0.
int yint (int axis, int x, int y, int dx, int dy);

// x-intercept along axis. assumes dy != 0.
int xint (int axis, int x, int y, int dx, int dy);

// given x (-inf, inf) and m [1, inf), produces [0, m).
// unlike % modulo, does not have strange behavior for x < 0.
int wrap (int x, int m);

// Bhaskara I's sine approximation
// max absolute error is 0.00165, and max relative error is 1.8 percent.
// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
int bhaskara (int x, int r);

// quick integer sine.
// given degrees x [0, 359], and radius r (-inf, inf), produces sin(x) [-r, r].
int qsin (int x, int r);

// quick integer cosine.
// given degrees x [0, 359], and radius r (-inf, inf), produces cos(x) [-r, r].
int qcos (int x, int r);

// integer square root.
// int wrapper for float sqrt function in math.h
// assumes x >= 0.
int sqrt (int64_t x);

// x squared.
int64_t sq (int x);

// L1 distance, taxicab distance, or manhattan distance.
int distance_l1 (int x1, int y1, int x2, int y2);

// squared euclidean/pythagorean distance.
int64_t distance_sq (int x1, int y1, int x2, int y2);

// euclidean/pythagorean distance.
int distance (int x1, int y1, int x2, int y2);

class Vec {
public:
	int x;
	int y;
	int z; // z defaults to 0.
	int w; // magnitude defaults to 1.
	
	// vec represents all types of vector, so they can be interchanged.
	void init_2d (int x, int y);
	void init_2d (int x, int y, int w);
	void init_3d (int x, int y, int z);
	void init_3d (int x, int y, int z, int w);
};

class Circle {
public:
	int x;
	int y;
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

class Rect {
public:
	int x;
	int y;
	int w;
	int h;
	
	void init (int x, int y, int w, int h);
	void get_SDL_Rect (SDL_Rect* const) const;
	int contains (int x, int y) const;
	int overlaps (const Rect*) const;
	void absolute_to_relative (const Rect*, const Grid*);
	void relative_to_absolute (const Rect*, const Grid*);
	void portal (const Rect* src, const Rect* dest);
	
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
};

// Graphics
enum EnumFlip {
	FlipX = 1, // flip x coords (horizontal flip) (NOT flip over x axis)
	FlipY = 2 // flip y coords (vertical flip) (NOT flip over y axis)
}; // both = x | y

enum EnumDraw {
	DrawFrame = 0,
	DrawFill = 1
};

class Grid {
public:
	int columns;
	int rows;
	float tile_w;
	float tile_h;
	
	void init (const Rect*, int columns, int rows);
	void portal (const Rect* src, const Rect* dest);
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
	
	void init (const char* title, int w, int h);
	void quit ();
	void set_color (const Color*);
	void set_alpha (const Color*);
	void clear ();
	void draw ();
	
	void draw_image (Image* const, const Rect*, const Rect*);
	void draw_rect (const Rect*, int draw);
	void draw_line (int x1, int y1, int x2, int y2);
	void draw_point (int x, int y);
	
	/*
	void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame,
		int w_frames, int h_frames, const char* str, int di);
	void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame,
		int w_frames, int h_frames);
	*/

// Event
	void window_event (SDL_Event* const);
};

class Mouse {
public:
	bool left;
	bool middle;
	bool right;
	int x;
	int y;
	int dx;
	int dy;
	int scroll_x;
	int scroll_y;
	
	void init ();
	bool press (SDL_Event* const);
	bool release (SDL_Event* const);
	void move (SDL_Event* const);
	void scroll (SDL_Event* const);
};

class Key {
public:
	int scancode; // SDL_Scancode
	int keycode; // SDL_Keycode
	bool lshift;
	bool rshift;
	bool lctrl;
	bool rctrl;
	bool lalt;
	bool ralt;
	bool caps;
	
	void init ();
	void press (SDL_Event* const);
	void release (SDL_Event* const);
};

enum EnumEvent {
	Quit = 1,
	WindowEvent = 2,
	MousePress = 3,
	MouseRelease = 4,
	MouseMove = 5,
	MouseScroll = 6,
	KeyPress = 7,
	KeyRelease = 8,
	TextInput = 9
};

#define NG_EVENT_TEXT 33

class Event {
public:
	int mode;
	Mouse mouse;
	Key key;
	char text[NG_EVENT_TEXT]; // ARRAY! DO NOT FREE!
	// ^ utf-8 text. always ends in '\0' (max input is 32, +1 for nul)
	// ^ text input should play nice with international keyboards,
	// ^ even if it can't process their inputs.
	Graphics* g;
	SDL_Event event;
	
	void init (Graphics* const);
	bool next ();
	void consume ();
	bool exists ();
	void text_input (SDL_Event* const);
};

// Audio
enum EnumSound {
	SoundPlayOnce,
	SoundLoop,
	SoundComplete
};

class Clip {
public:
	SDL_AudioSpec spec;
	uint8_t* data;
	uint32_t samples;
	
	void init (Audio*, const char* file);
	void quit ();
};

class Sound {
public:
	Clip* clip;
	int sample;
	int mode;
	
	// start sound at the beginning of a clip
	void init (Clip*, int mode);
};

class Channel {
public:
	Sound* data;
	int sounds;
	
	void init ();
	void quit ();
	
	void start_sound (Clip*, int mode); // add sound
	void stop_sound (int sound); // remove sound
	void stop (); // remove all sounds
};

class Audio {
public:
	SDL_AudioSpec spec;
	SDL_AudioDeviceID device;
	uint8_t* data;
	uint32_t samples;
	bool playing;
	
	void init ();
	void quit ();
	void play (); // unpause audio device
	void pause (); // pause audio device
	void stop (); // clear queued audio
	
	// void ng_audio_update (ngAudio*); // mix all sounds and queue
	void clear (); // fill queue with silence
	int mix_sample (int a, int b) const; // add decibels
	void mix_sound (Channel*, int sound); // add clip data to queue
	void mix_channel (Channel*);
	void queue (); // queue audio
};

} // namespace ng

#endif


