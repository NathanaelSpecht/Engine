
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NG_H
#define NG_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL.h"

// Core
#define ng_here(); printf("%s:%d\n",__FILE__,__LINE__);

// These are compatible with bool
enum ngEnumNone { NG_NONE = 0 };
enum ngEnumError { NG_ERROR = 0, NG_SUCCESS = 1 };
enum ngEnumTernary { NG_FALSE = 0, NG_EDGE = 1, NG_TRUE = 2 };

// File
bool ng_file_exists (const char* file);
void ng_file_delete (const char* file);
char* ng_file_read (const char* file);
void ng_file_write (const char* file, const char* s);
void ng_file_append (const char* file, const char* s);

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
int ng_rect_contains (ngRect*, int x, int y);
int ng_rect_overlaps (ngRect*, ngRect*);

void ng_grid_init (ngGrid*, const ngRect*, int columns, int rows);

void ng_absolute_to_relative (ngRect*, const ngRect*, const ngGrid*);
void ng_relative_to_absolute (ngRect*, const ngRect*, const ngGrid*);
void ng_rect_portal (ngRect*, const ngRect* src, const ngRect* dest);
void ng_grid_portal (ngGrid*, const ngRect* src, const ngRect* dest);

void ng_color_init (ngColor*, int r, int g, int b);

int ng_image_init (ngGraphics*, ngImage*, const char* file, const ngColor* key);
void ng_image_quit (ngImage*);
int ng_image_color (ngImage*, const ngColor*);
int ng_image_alpha (ngImage*, const ngColor*);
void ng_image_flip (ngImage*, int flip);
void ng_image_angle (ngImage*, double angle);

int ng_graphics_init (ngGraphics*, const char* title, int w, int h);
void ng_graphics_quit (ngGraphics*);
int ng_graphics_color (ngGraphics*, const ngColor*);
int ng_graphics_alpha (ngGraphics*, const ngColor*);
int ng_graphics_clear (ngGraphics*);
void ng_graphics_draw (ngGraphics*);

int ng_draw_image (ngGraphics*, ngImage*, const ngRect*, const ngRect*);
int ng_draw_rect (ngGraphics*, const ngRect*, bool fill);
int ng_draw_line (ngGraphics*, int x1, int y1, int x2, int y2);
int ng_draw_point (ngGraphics*, int x, int y);

/*
void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames,
	const char* str, int di);
void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames);
*/

// Event
void ng_window_event (ngGraphics*, SDL_Event*);

// These are compatible with bool
enum ngEnumButtonState {
	NG_RELEASED = 0,
	NG_PRESSED = 1
};
enum ngEnumMouseEvent {
	NG_MOUSE_PRESS = 1,
	NG_MOUSE_RELEASE = 2,
	NG_MOUSE_MOVE = 3,
	NG_MOUSE_SCROLL = 4
};
typedef struct ngMouse {
	int event;
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

// This is compatible with bool
enum ngEnumKeyEvent {
	NG_KEY_PRESS = 1,
	NG_KEY_RELEASE = 2,
	NG_TEXT_INPUT = 3
};
enum ngEnumKeyNum { NG_KEYTEXT = 33 };
typedef struct ngKey {
	int event;
	int scancode; // SDL_Scancode
	int keycode; // SDL_Keycode
	int lshift;
	int rshift;
	int lctrl;
	int rctrl;
	int lalt;
	int ralt;
	int caps;
	char text[NG_KEYTEXT]; // null-terminated utf-8 text
	// ^ text input should play nice with international keyboards,
	// ^ even if it can't process their inputs.
} ngKey;
void ng_key_init (ngKey*);
void ng_key_press (ngKey*, SDL_Event*);
void ng_key_release (ngKey*, SDL_Event*);
void ng_text_input (ngKey*, SDL_Event*);

enum ngEnumEventMode { NG_QUIT = 1, NG_WINDOW = 2, NG_MOUSE = 3, NG_KEY = 4 };
typedef struct ngEvent {
	int mode;
	ngMouse mouse;
	ngKey key;
	ngGraphics* g;
	SDL_Event event;
} ngEvent;
void ng_event_init (ngEvent*, ngGraphics*);
bool ng_event_next (ngEvent*);

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

int ng_audio_init (ngAudio*);
void ng_audio_quit (ngAudio*);
int ng_clip_init (ngAudio*, ngClip*, const char* file);
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
int ng_audio_queue (ngAudio*); // queue audio

#endif

