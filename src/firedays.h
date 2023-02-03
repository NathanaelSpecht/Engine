
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
	FD_LEVELSCREEN = 4
};

typedef struct fdTitleScreen {
	ngRect header_rect;
	ngRect button_rect;
	ngRect start_rect;
	ngRect quit_rect;
} fdTitleScreen;
void fd_title_screen_init (fdTitleScreen*);
void fd_title_screen_draw (fdTitleScreen*, ngGraphics*);

typedef struct fdFileScreen {
	ngRect header_rect;
	ngRect save_rect;
	ngRect save1_rect;
} fdFileScreen;
void fd_file_screen_init (fdFileScreen*);
void fd_file_screen_draw (fdFileScreen*, ngGraphics*);

typedef struct fdWorldScreen {
	ngRect header_rect;
	ngRect level_rect;
	ngRect level1_rect;
} fdWorldScreen;
void fd_world_screen_init (fdWorldScreen*);
void fd_world_screen_draw (fdWorldScreen*, ngGraphics*);

enum fdEnumHudMode { FD_HUDMENU = 1 };
typedef struct fdHudMenu {
	int mode;
	ngRect hud_rect;
	ngRect temperature_rect;
	ngRect heat_rect;
	ngRect fuel_rect;
} fdHudMenu;
void fd_hud_menu_init (fdHudMenu*);
void fd_hud_menu_draw (fdHudMenu*, ngGraphics*);

enum fdEnumPauseMode { FD_PAUSEMENU = 1 };
typedef struct fdPauseMenu {
	int mode;
	ngRect header_rect;
	ngRect button_rect;
	ngRect resume_rect;
	ngRect quit_rect;
} fdPauseMenu;
void fd_pause_menu_init (fdPauseMenu*);
void fd_pause_menu_draw (fdPauseMenu*, ngGraphics*);

typedef struct fdLevelScreen {
	ngRect header_rect;
	fdHudMenu hud_menu;
	fdPauseMenu pause_menu;
} fdLevelScreen;
void fd_level_screen_init (fdLevelScreen*);
void fd_level_screen_draw (fdLevelScreen*, ngGraphics*);

enum fdEnumDebugMode { FD_DEBUGMENU = 1 };
typedef struct fdDebugMenu {
	int mode;
	ngRect version_rect;
	ngRect fps_rect;
} fdDebugMenu;
void fd_debug_menu_init (fdDebugMenu*);
void fd_debug_menu_draw (fdDebugMenu*, ngGraphics*);

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

