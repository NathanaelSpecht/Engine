
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * Fire Days API
 */


#ifndef FIREDAYS_H
#define FIREDAYS_H

#include "ng.h"

// Screen

enum fdEnumNone { FD_NONE = 0 };
enum fdEnumScreenMode { FD_TITLE = 1, FD_FILE = 2, FD_WORLD = 3, FD_LEVEL = 4,
	FD_CREATIVE = 5 };

typedef struct fdTitleScreen {
	ngRect header_rect;
	ngFrame button_frame;
	ngRect start_rect;
	ngRect quit_rect;
} fdTitleScreen;

/* TODO level completion, save/load progress
typedef struct fdFileScreen {
	ngRect header_rect;
	ngFrame save_frame;
	ngRect save1_rect;
} fdFileScreen;
*/

/* TODO level select
typedef struct fdWorldScreen {
	ngRect header_rect;
	ngFrame level_frame;
	ngRect level1_rect;
} fdWorldScreen;
*/

typedef struct fdLevelScreen {
	ngRect header_rect;
	ngFrame hud_frame; // overlay on virtual screen
	ngRect temperature_rect;
	ngRect heat_rect;
	ngRect fuel_rect;
} fdLevelScreen;

/* TODO level creator
typedef struct fdCreativeScreen {
	ngRect header_rect;
	ngFrame item_frame;
	ngRect fire_rect;
	ngRect water_rect;
	ngRect box_rect;
	ngRect flag_rect;
} fdCreativeScreen;
*/

/* TODO debug overlay
enum fdEnumDebugMode { FD_DEBUG = 1 };

typedef struct fdDebugScreen {
	int mode;
	ngRect version_rect;
	ngRect fps_rect;
} fdDebugScreen;
*/

typedef struct fdScreen {
	ngView view; // portal from virtual screen to window pixels
	// ^ fills the whole window
	// ^ allows user to resize window while screen positions stay the same.
	int mode;
	fdTitleScreen title;
	//fdFileScreen file;
	//fdWorldScreen world;
	fdLevelScreen level;
	//fdCreativeScreen creative;
	//fdDebugScreen debug;
} fdScreen;

void fd_screen_init (fdScreen*, ngGraphics*);
void fd_screen_draw (fdScreen*, ngGraphics*);

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

