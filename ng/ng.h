
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

enum ngEnumReturnCode { NG_SUCCESS = 0, NG_ERROR = -1 };

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
typedef struct ngFrame {
	int x;
	int y;
	int w;
	int h;
	int columns;
	int rows;
	float tile_w;
	float tile_h;
} ngFrame;

typedef struct ngView {
	ngFrame in;
	ngFrame out;
} ngView;

typedef struct ngImage {
	SDL_Texture* texture;
	int w;
	int h;
	bool grid;
	int columns;
	int rows;
	int tile_w;
	int tile_h;
	int r;
	int g;
	int b;
	int a;
} ngImage;

typedef struct ngGraphics {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int w;
	int h;
	int r;
	int g;
	int b;
	int a;
} ngGraphics;

void ng_frame_init (ngFrame*, int x, int y, int w, int h);
void ng_frame_grid (ngFrame*, int columns, int rows);
// ^ change columns and recompute tile w, keeping w the same

// resize functions keep x the same
// scale functions change x to keep center the same
void ng_frame_resize_absolute (ngFrame*, int w, int h);
void ng_frame_scale_absolute (ngFrame*, int w, int h);
// ^ change w and recompute tile w, keeping columns the same
void ng_frame_resize_percent (ngFrame*, float sw, float sh);
void ng_frame_scale_percent (ngFrame*, float sw, float sh);
// ^ change w by percent and recompute tile w, keeping columns the same
void ng_frame_resize_grid (ngFrame*, int columns, int rows);
void ng_frame_scale_grid (ngFrame*, int columns, int rows);
// ^ change columns and recompute w, keeping tile w the same

void ng_frame_in (const ngFrame*, SDL_Rect*);
// ^ change rect from absolute to relative, using grid if needed
void ng_frame_out (const ngFrame*, SDL_Rect*);
// ^ change rect from relative (using grid if needed) to absolute
// to shift a point in or out, use a rect with w=0 and h=0
// to shift a line in or out, use 2 points

void ng_view_init (ngView*, ngFrame* in, ngFrame* out);
void ng_view_in (const ngView*, SDL_Rect*);
// ^ change rect from inside coord space to outside coord space, both absolute
void ng_view_out (const ngView*, SDL_Rect*);
// ^ change rect from outside coord space to inside coord space, both absolute

int ng_image_init (ngGraphics*, ngImage*, const char* file, int columns, int rows,
	int key_r, int key_g, int key_b);
void ng_image_quit (ngImage*);
void ng_image_grid (ngImage*, int columns, int rows);
int ng_image_color (ngImage*, int r, int g, int b);
int ng_image_alpha (ngImage*, int a);

int ng_graphics_init (ngGraphics*, const char* title, int w, int h);
void ng_graphics_quit (ngGraphics*);
int ng_graphics_color (ngGraphics*, int r, int g, int b);
int ng_graphics_alpha (ngGraphics*, int a);
int ng_graphics_clear (ngGraphics*);
void ng_graphics_draw (ngGraphics*);

int ng_draw_image (ngGraphics*, ngImage*, const SDL_Rect*, const SDL_Rect*,
	int flip, double angle);
// ^ sdl flip, angle in degrees
int ng_draw_rect (ngGraphics*, const SDL_Rect*, bool fill);
int ng_draw_line (ngGraphics*, int x1, int y1, int x2, int y2);
int ng_draw_point (ngGraphics*, int x, int y);

/*
void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames,
	const char* str, int di);
void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames);
*/

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

