
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

typedef struct fdGameState {
	int* screen_mode;
	ngRect* screen_rect;
	ngGrid* char_grid;
	ngGrid* tile_grid;
	ngGraphics* g;
	ngMouse* mouse;
	ngKey* key;
} fdGameState;

typedef struct fdTitleScreen {
	ngRect header_rect;
	ngRect button_rect;
	ngRect start_rect;
	ngRect quit_rect;
} fdTitleScreen;
void fd_titlescreen_init (fdTitleScreen*, fdGameState*);
void fd_titlescreen_event (fdTitleScreen*, fdGameState*);
void fd_titlescreen_draw (fdTitleScreen*, fdGameState*);

typedef struct fdFileScreen {
	ngRect header_rect;
	ngRect save_rect;
	ngRect save1_rect;
} fdFileScreen;
void fd_filescreen_init (fdFileScreen*, fdGameState*);
void fd_filescreen_event (fdFileScreen*, fdGameState*);
void fd_filescreen_draw (fdFileScreen*, fdGameState*);

typedef struct fdWorldScreen {
	ngRect header_rect;
	ngRect level_rect;
	ngRect level1_rect;
} fdWorldScreen;
void fd_worldscreen_init (fdWorldScreen*, fdGameState*);
void fd_worldscreen_event (fdWorldScreen*, fdGameState*);
void fd_worldscreen_draw (fdWorldScreen*, fdGameState*);

enum fdEnumHudMode { FD_HUDMENU = 1 };
typedef struct fdHudMenu {
	int mode;
	ngRect hud_rect;
	ngRect temperature_rect;
	ngRect heat_rect;
	ngRect fuel_rect;
} fdHudMenu;
void fd_hudmenu_init (fdHudMenu*, fdGameState*);
void fd_hudmenu_event (fdHudMenu*, fdGameState*);
void fd_hudmenu_draw (fdHudMenu*, fdGameState*);

enum fdEnumPauseMode { FD_PAUSEMENU = 1 };
typedef struct fdPauseMenu {
	int mode;
	ngRect header_rect;
	ngRect button_rect;
	ngRect resume_rect;
	ngRect quit_rect;
} fdPauseMenu;
void fd_pausemenu_init (fdPauseMenu*, fdGameState*);
void fd_pausemenu_event (fdPauseMenu*, fdGameState*);
void fd_pausemenu_draw (fdPauseMenu*, fdGameState*);

typedef struct fdLevelScreen {
	ngRect header_rect;
	fdHudMenu hud_menu;
	fdPauseMenu pause_menu;
} fdLevelScreen;
void fd_levelscreen_init (fdLevelScreen*, fdGameState*);
void fd_levelscreen_event (fdLevelScreen*, fdGameState*);
void fd_levelscreen_draw (fdLevelScreen*, fdGameState*);

enum fdEnumDebugMode { FD_DEBUGMENU = 1 };
typedef struct fdDebugMenu {
	int mode;
	ngRect version_rect;
	ngRect fps_rect;
} fdDebugMenu;
void fd_debugmenu_init (fdDebugMenu*, fdGameState*);
void fd_debugmenu_event (fdDebugMenu*, fdGameState*);
void fd_debugmenu_draw (fdDebugMenu*, fdGameState*);

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

