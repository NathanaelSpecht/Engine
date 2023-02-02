
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * Fire Days API
 */


#ifndef FIREDAYS_H
#define FIREDAYS_H

#include "ng.h"

enum fdEnumNone { FD_NONE = 0 };
enum fdEnumScreenMode {
	FD_TITLESCREEN = 1,
	FD_FILESCREEN = 2,
	FD_WORLDSCREEN = 3,
	FD_LEVELSCREEN = 4,
	FD_CREATIVESCREEN = 5
};

typedef struct fdTitleScreen {
	ngRect header_rect;
	ngFrame button_frame;
	ngRect start_rect;
	ngRect quit_rect;
} fdTitleScreen;

void fd_title_screen_init (fdTitleScreen*);
void fd_title_screen_draw (fdTitleScreen*, ngGraphics*, ngView*);

typedef struct fdFileScreen {
	ngRect header_rect;
	ngFrame save_frame;
	ngRect save1_rect;
} fdFileScreen;

void fd_file_screen_init (fdFileScreen*);
void fd_file_screen_draw (fdFileScreen*, ngGraphics*, ngView*);

typedef struct fdWorldScreen {
	ngRect header_rect;
	ngFrame level_frame;
	ngRect level1_rect;
} fdWorldScreen;

void fd_world_screen_init (fdWorldScreen*);
void fd_world_screen_draw (fdWorldScreen*, ngGraphics*, ngView*);

typedef struct fdLevelScreen {
	ngRect header_rect;
	ngFrame hud_frame; // overlay on virtual screen
	ngRect temperature_rect;
	ngRect heat_rect;
	ngRect fuel_rect;
} fdLevelScreen;

void fd_level_screen_init (fdLevelScreen*);
void fd_level_screen_draw (fdLevelScreen*, ngGraphics*, ngView*);

enum fdEnumDebugMode { FD_DEBUGSCREEN = 1 };

typedef struct fdDebugScreen {
	int mode;
	ngRect version_rect;
	ngRect fps_rect;
} fdDebugScreen;

void fd_debug_screen_init (fdDebugScreen*);
void fd_debug_screen_draw (fdDebugScreen*, ngGraphics*, ngView*);

// Level

/* TODO camera, player controls, and level data (fire, water, boxes, etc)
typedef struct fdLevel {
	ngView camera; // portal from level to window pixels
	// ^ fills the whole window
	// ^ allows user to follow characters in the level.
} fdLevel;
*/

// Animation
// TODO image bank, tile sheets, animations, etc

#endif

