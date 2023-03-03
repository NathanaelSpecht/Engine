
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NG_H
#define NG_H

#include <stdexcept>
#include <new>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>

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
enum EnumNone { None = 0 };

// ng::Edge represents a fuzzy condition that could be true, false, or both.
// If you only need true and false, you should use a bool instead.
// If you need three mutually exclusive states, you should use your own enum instead.
enum EnumTernary { False = 0, Edge = 1, True = 2 };

void init ();
void quit ();

} // namespace ng

// String
// use <string> and <sstream> instead.

// File
// use <iostream> and <fstream> and <filesystem> instead.

// Time
typedef struct ngTime {
	uint32_t now;
	uint32_t last;
	int64_t ticks;
	int delta;
	int tps;
	int count;
	int ms;
} ngTime;

void ng_time_init (ngTime*);
void ng_time_tick (ngTime*);

// Graphics
typedef struct ngRect {
	int x;
	int y;
	int w;
	int h;
} ngRect;

typedef struct ngGrid {
	int columns;
	int rows;
	float tile_w;
	float tile_h;
} ngGrid;

typedef struct ngColor {
	int r;
	int g;
	int b;
	int a;
} ngColor;

// This is compatible with bool
enum ngEnumImageFlip {
	NG_FLIP_X = 1, // flip x coords (horizontal flip) (NOT flip over x axis)
	NG_FLIP_Y = 2 // flip y coords (vertical flip) (NOT flip over y axis)
}; // both = x | y

typedef struct ngImage {
	SDL_Texture* texture;
	ngRect rect;
	ngColor color;
	int flip;
	double angle;
} ngImage;

typedef struct ngGraphics {
	SDL_Window* window;
	SDL_Renderer* renderer;
	ngRect rect;
	ngColor color;
} ngGraphics;

void ng_rect_init (ngRect*, int x, int y, int w, int h);
void ng_rect_to_sdl (SDL_Rect*, const ngRect*);
int ng_rect_contains (const ngRect*, int x, int y);
int ng_rect_overlaps (const ngRect*, const ngRect*);

void ng_grid_init (ngGrid*, const ngRect*, int columns, int rows);

void ng_absolute_to_relative (ngRect*, const ngRect*, const ngGrid*);
void ng_relative_to_absolute (ngRect*, const ngRect*, const ngGrid*);
void ng_rect_portal (ngRect*, const ngRect* src, const ngRect* dest);
void ng_grid_portal (ngGrid*, const ngRect* src, const ngRect* dest);

void ng_color_init (ngColor*, int r, int g, int b);

void ng_image_init (ngGraphics*, ngImage*, const char* file, const ngColor* key);
void ng_image_quit (ngImage*);
void ng_image_color (ngImage*, const ngColor*);
void ng_image_alpha (ngImage*, const ngColor*);
void ng_image_flip (ngImage*, int flip);
void ng_image_angle (ngImage*, double angle);

void ng_graphics_init (ngGraphics*, const char* title, int w, int h);
void ng_graphics_quit (ngGraphics*);
void ng_graphics_color (ngGraphics*, const ngColor*);
void ng_graphics_alpha (ngGraphics*, const ngColor*);
void ng_graphics_clear (ngGraphics*);
void ng_graphics_draw (ngGraphics*);

void ng_draw_image (ngGraphics*, ngImage*, const ngRect*, const ngRect*);
enum ngEnumRectFill { NG_FRAME = 0, NG_FILL = 1 }; // compatible with bool
void ng_draw_rect (ngGraphics*, const ngRect*, bool fill);
void ng_draw_line (ngGraphics*, int x1, int y1, int x2, int y2);
void ng_draw_point (ngGraphics*, int x, int y);

/*
void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames,
	const char* str, int di);
void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames);
*/

// Event
void ng_window_event (ngGraphics*, SDL_Event*);

// These are compatible with bool
enum ngEnumButtonState {
	NG_RELEASE = 0,
	NG_PRESS = 1
};
typedef struct ngMouse {
	int left;
	int middle;
	int right;
	int x;
	int y;
	int dx;
	int dy;
	int scroll_x;
	int scroll_y;
} ngMouse;
void ng_mouse_init (ngMouse*);
void ng_mouse_press (ngMouse*, SDL_Event*);
void ng_mouse_release (ngMouse*, SDL_Event*);
void ng_mouse_move (ngMouse*, SDL_Event*);
void ng_mouse_scroll (ngMouse*, SDL_Event*);

typedef struct ngKey {
	int scancode; // SDL_Scancode
	int keycode; // SDL_Keycode
	int lshift;
	int rshift;
	int lctrl;
	int rctrl;
	int lalt;
	int ralt;
	int caps;
} ngKey;
void ng_key_init (ngKey*);
void ng_key_press (ngKey*, SDL_Event*);
void ng_key_release (ngKey*, SDL_Event*);

enum ngEnumEventMode {
	NG_QUIT = 1,
	NG_WINDOW = 2,
	NG_MOUSE_PRESS = 3,
	NG_MOUSE_RELEASE = 4,
	NG_MOUSE_MOVE = 5,
	NG_MOUSE_SCROLL = 6,
	NG_KEY_PRESS = 7,
	NG_KEY_RELEASE = 8,
	NG_TEXT_INPUT = 9
};
enum ngEnumTextNum { NG_EVENT_TEXT = 33 };
typedef struct ngEvent {
	int mode;
	ngMouse mouse;
	ngKey key;
	char text[NG_EVENT_TEXT]; // ARRAY! DO NOT FREE!
	// ^ utf-8 text. always ends in '\0' (max input is 32, +1 for nul)
	// ^ text input should play nice with international keyboards,
	// ^ even if it can't process their inputs.
	ngGraphics* g;
	SDL_Event event;
} ngEvent;
void ng_event_init (ngEvent*, ngGraphics*);
bool ng_event_next (ngEvent*);
void ng_text_input (ngEvent*, SDL_Event*);

// Audio
enum ngEnumSoundMode { NG_PLAYONCE, NG_LOOP, NG_COMPLETE };

typedef struct ngClip {
	SDL_AudioSpec spec;
	uint8_t* data;
	uint32_t samples;
} ngClip;

typedef struct ngSound {
	ngClip* clip;
	int sample;
	int mode;
} ngSound;

typedef struct ngChannel {
	ngSound* data;
	int sounds;
} ngChannel;

typedef struct ngAudio {
	SDL_AudioSpec spec;
	SDL_AudioDeviceID device;
	uint8_t* data;
	uint32_t samples;
	bool playing;
} ngAudio;

void ng_audio_init (ngAudio*);
void ng_audio_quit (ngAudio*);
void ng_clip_init (ngAudio*, ngClip*, const char* file);
void ng_clip_quit (ngClip*);
void ng_channel_init (ngChannel*);
void ng_channel_quit (ngChannel*);

void ng_audio_play (ngAudio*); // unpause audio device
void ng_audio_pause (ngAudio*); // pause audio device

void ng_channel_start_sound (ngChannel*, ngClip*, int mode); // add sound
void ng_channel_stop_sound (ngChannel*, int sound); // remove sound
void ng_channel_stop (ngChannel*); // remove all sounds
void ng_audio_stop (ngAudio*); // clear queued audio

// void ng_audio_update (ngAudio*); // mix all sounds and queue
void ng_audio_clear (ngAudio*); // fill queue with silence
int ng_audio_mix_sample (int a, int b); // add decibels
void ng_audio_mix_sound (ngAudio*, ngChannel*, int sound); // add clip data to queue
void ng_audio_mix_channel (ngAudio*, ngChannel*);
void ng_audio_queue (ngAudio*); // queue audio

// Physics
typedef struct ngVec {
	int x;
	int y;
	// magnitude. defaults to 1.
	// may represent length, radius, etc.
	int w;
} ngVec;

// vec represents all types of vector, so they can be interchanged.
void ng_vec2_init (ngVec*, int x, int y);
void ng_vec2w_init (ngVec*, int x, int y, int w);
void ng_circle_init (ngVec*, int x, int y, int r);

int ng_contains (int x, int w, int p);
int ng_overlaps (int x1, int w1, int x2, int w2);

// return true/edge/false if x + d crosses axis.
int ng_intercepts (int axis, int x, int d);

// y-intercept along axis. assumes dx != 0.
int ng_yint (int axis, int x, int y, int dx, int dy);

// x-intercept along axis. assumes dy != 0.
int ng_xint (int axis, int x, int y, int dx, int dy);

// move rect by vec, consuming vec in the process (vec -> 0). 2d.
void ng_rect_moveby (ngRect*, ngVec*);

// move rect to (x, y), and reduce vec to the remaining motion. 2d.
// assumes (x, y) is in the direction of vec.
void ng_rect_moveto (ngRect*, ngVec*, int x, int y);

// return true/edge/false if rect a collided with stationary rect b, and
// move rect a by the part of its vec v that gets it to collide, and
// reduce vec v to the remaining motion.
// edge means they will touch and not move any further.
// assumes rects are not overlapping.
int ng_rect_collide (ngRect* a, ngVec* v, const ngRect* b);

// given degrees x (-inf, inf), produces angle [0, 359].
int ng_wrap_degrees (int x);

// Bhaskara I's sine approximation
// max absolute error is 0.00165, and max relative error is 1.8 percent.
// error approaches 0 for x approaching 0, 30, 90, 150, and 180.
// given degrees x [0, 180], and radius r (-inf, inf), produces sin(x) [0, r].
int ng_bhaskara (int x, int r);

// quick integer sine.
// given degrees x [0, 359], and radius r (-inf, inf), produces sin(x) [-r, r].
int ng_qsin (int x, int r);

// quick integer cosine.
// given degrees x [0, 359], and radius r (-inf, inf), produces cos(x) [-r, r].
int ng_qcos (int x, int r);

// integer square root.
// int wrapper for float sqrt function in math.h
// assumes x >= 0.
int ng_sqrt (int64_t x);

// x squared.
int64_t ng_sq (int x);

// L1 distance, taxicab distance, or manhattan distance.
int ng_distance_l1 (int x1, int y1, int x2, int y2);

// squared euclidean/pythagorean distance.
int64_t ng_distance_sq (int x1, int y1, int x2, int y2);

// euclidean/pythagorean distance.
int ng_distance (int x1, int y1, int x2, int y2);

// return true/edge/false if circle contains (x, y).
int ng_circle_contains (const ngVec*, int x, int y);

// return true/edge/false if circles overlap/touch.
int ng_circle_overlaps (const ngVec*, const ngVec*);

// return true/edge/false if circle a collided with stationary circle b, and
// move circle a by the part of its vec v that gets it to collide, and
// reduce vec v to the remaining motion.
// edge means they will touch and not move any further.
// assumes circles are not overlapping.
int ng_circle_collide (ngVec* a, ngVec* v, const ngVec* b);

#endif


