
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

// Memory
// Wrappers around malloc, realloc, and free - with NULL checking.
// When a memory error occurs, the program exits.
void* ng_new (size_t);
void* ng_resize (void*, size_t);
void* ng_free (void*); // always returns NULL

// These also print the file and line they are called from,
// then "memory error", before exit. The 'd' stands for debug.
void* ng_debug_new (size_t, const char*, int);
void* ng_debug_resize (void*, size_t, const char*, int);
#define ng_dnew(a); ng_debug_new(a,__FILE__,__LINE__);
#define ng_dresize(a,b); ng_debug_resize(a,b,__FILE__,__LINE__);

// These do the same checks and DO NOT EXIT.
// The 'x' stands for no e'x'it.
void* ng_xnew (size_t);
void* ng_xresize (void*, size_t);

// These do the checks, print the debug message, and DO NOT EXIT.
void* ng_debugx_new (size_t, const char*, int);
void* ng_debugx_resize (void*, size_t, const char*, int);
#define ng_dxnew(a); ng_debugx_new(a,__FILE__,__LINE__);
#define ng_dxresize(a,b); ng_debugx_resize(a,b,__FILE__,__LINE__);

// String
// Wrappers around clib's string functions - with boundary checking and
// memory re-allocation - to (hopefully) avoid undefined behavior.
int64_t ng_strlen (const char*);
int ng_strcmp (const char*, const char*);
char* ng_strcpy (char*, const char*);
char* ng_strcat (char*, const char*);
char* ng_strcatc (char*, char); // calls strcat(s,char[2])
char* ng_substr (char*, const char*, int64_t, int64_t);
int64_t ng_strdelim (const char*, const char*, int64_t);
int64_t ng_strndelim (const char*, const char*, int64_t);
// ^ first delim/non-delim char from start
// ^ calls strncpy(s,a+start,len)
char* ng_qstrcpy (char*, const char*, int64_t);
char* ng_qstrcat (char*, int64_t, const char*, int64_t);
char* ng_qstrcatc (char*, int64_t, char);
char* ng_qsubstr (char*, const char*, int64_t, int64_t, int64_t);
int64_t ng_qstrdelim (const char*, int64_t, const char*, int64_t);
int64_t ng_qstrndelim (const char*, int64_t, const char*, int64_t);
// ^ quick str functions. the 'q' stands for quick.
bool ng_strchr (const char*, char); // returns strchr(s,c)!=NULL
void ng_strupper (char*);
void ng_strlower (char*);
char* ng_atoh (char*, const char*, char);
// ^ pass an uppercase/lowercase letter to output uppercase/lowercase hex.
// ^ if the letter is X/x, also prepends "0x".
double ng_atof (const char*);
int64_t ng_atoi (const char*);
bool ng_atob (const char*);
char* ng_htoa (char*, const char*);
char* ng_ftoa (char*, const char*, double); // calls sprintf(s,fmt,d)
char* ng_itoa (char*, const char*, int64_t); // calls sprintf(s,fmt,i)
char* ng_btoa (char*, bool);
// more quick str functions
char* ng_qatoh (char*, const char*, int64_t, char c);
char* ng_qhtoa (char*, const char*, int64_t);

// File
// Wrappers around clib's file functions - with boundary checking and
// error checking - to (hopefully) avoid undefined behavior.
FILE* ng_fopen (const char*, const char*); // returns NULL on error
char* ng_fgets (char*, FILE*, int buf); // returns chars read before error/EOF
// Buf is the number of chars to read at a time.
// - Larger buffers allow faster reads, but skip data when an error occurs,
//   and require ftell and fseek to return to where it left off.
// - Reading 1 char at a time is slow, but will pick up right where it
//   left off after errors are dealt with.
int ng_fputs (const char*, FILE*);
FILE* ng_fclose (FILE*); // always returns NULL
int ng_rename (const char*, const char*);
int ng_delete (const char*);
bool ng_exist (const char*, char); // file exists and program/user has permission
// check for 'r'ead/'w'rite/'+'both access

// Folders are OS-dependent
// Linux: int mkdir (const char*, int mode); requires <sys/stat.h>
// Windows: int mkdir (const char*); requires <windows.h>
// ng_delete can remove empty folders
// TODO List files in a folder?

/*
bool ng_file_exists (const char* file);
void ng_file_delete (const char* file);
char* ng_file_read (const char* file);
void ng_file_write (const char* file, const char* s);
void ng_file_append (const char* file, const char* s);
*/

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
enum ngEnumRectFill { NG_FRAME = 0, NG_FILL = 1 }; // compatible with bool
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

