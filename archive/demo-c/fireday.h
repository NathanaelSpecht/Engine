
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * Fire Day API
 */


#ifndef FIREDAY_H
#define FIREDAY_H

#include "ng.h"

// Core
enum fdEnumNone { FD_NONE = 0 };

typedef struct fdCore {
	ngTime time;
	ngGraphics graphics;
	//TODO audio & channels
	ngEvent event;
} fdCore;
void fd_core_init (fdCore*);
void fd_core_quit (fdCore*);

// Screen
enum fdEnumScreenMode {
	FD_TITLESCREEN = 1,
	FD_FILESCREEN = 2,
	FD_WORLDSCREEN = 3,
	FD_LEVELSCREEN = 4
};
typedef struct fdScreen {
	int mode;
	ngRect rect;
	ngGrid char_grid;
	ngGrid tile_grid;
	ngColor background_color;
	ngColor draw_color;
} fdScreen;
void fd_screen_init (fdScreen*);

//TODO image bank
//TODO clip bank

// Quality of Life
void fd_frame_mouse(ngRect* r, fdCore*, fdScreen*, ngRect* frame);
void fd_frame_draw_rect(const ngRect* r, fdCore*, fdScreen*, ngRect* frame);

// Title Screen
typedef struct fdTitleScreen {
	fdCore* core;
	fdScreen* screen;
	ngRect header;
	ngRect frame;
	ngRect start_btn;
	ngRect quit_btn;
} fdTitleScreen;
void fd_titlescreen_init (fdTitleScreen*, fdScreen*, fdCore*);
void fd_titlescreen_event (fdTitleScreen*);
void fd_titlescreen_draw (fdTitleScreen*);

// File Screen
typedef struct fdFileScreen {
	fdCore* core;
	fdScreen* screen;
	ngRect header;
	ngRect frame;
	ngRect save1;
} fdFileScreen;
void fd_filescreen_init (fdFileScreen*, fdScreen*, fdCore*);
void fd_filescreen_event (fdFileScreen*);
void fd_filescreen_draw (fdFileScreen*);

// World Screen
typedef struct fdWorldScreen {
	fdCore* core;
	fdScreen* screen;
	ngRect header;
	ngRect frame;
	ngRect level1;
} fdWorldScreen;
void fd_worldscreen_init (fdWorldScreen*, fdScreen*, fdCore*);
void fd_worldscreen_event (fdWorldScreen*);
void fd_worldscreen_draw (fdWorldScreen*);

// Hud Menu
enum fdEnumHudMode { FD_HUDMENU = 1 };
typedef struct fdHudMenu {
	fdCore* core;
	fdScreen* screen;
	int mode;
	ngRect frame;
	ngRect temp;
	ngRect heat;
	ngRect fuel;
} fdHudMenu;
void fd_hudmenu_init (fdHudMenu*, fdScreen*, fdCore*);
void fd_hudmenu_event (fdHudMenu*);
void fd_hudmenu_draw (fdHudMenu*);

// Pause Menu
enum fdEnumPauseMode { FD_PAUSEMENU = 1 };
typedef struct fdPauseMenu {
	fdCore* core;
	fdScreen* screen;
	int mode;
	ngRect header;
	ngRect frame;
	ngRect resume_btn;
	ngRect quit_btn;
} fdPauseMenu;
void fd_pausemenu_init (fdPauseMenu*, fdScreen*, fdCore*);
void fd_pausemenu_event (fdPauseMenu*);
void fd_pausemenu_draw (fdPauseMenu*);

// Level Screen
typedef struct fdLevelScreen {
	fdCore* core;
	fdScreen* screen;
	fdHudMenu hud_menu;
	fdPauseMenu pause_menu;
} fdLevelScreen;
void fd_levelscreen_init (fdLevelScreen*, fdScreen*, fdCore*);
void fd_levelscreen_event (fdLevelScreen*);
void fd_levelscreen_draw (fdLevelScreen*);

// Debug Menu
enum fdEnumDebugMode { FD_DEBUGMENU = 1 };
typedef struct fdDebugMenu {
	fdCore* core;
	fdScreen* screen;
	int mode;
	ngRect frame;
	ngRect version;
	ngRect fps;
} fdDebugMenu;
void fd_debugmenu_init (fdDebugMenu*, fdScreen*, fdCore*);
void fd_debugmenu_event (fdDebugMenu*);
void fd_debugmenu_draw (fdDebugMenu*);

// Level
/* TODO camera, player controls, and level data (fire, water, boxes, etc)
typedef struct fdLevel {
	ngView camera; // portal from level to window pixels
	// ^ fills the whole window
	// ^ allows user to follow characters in the level.
} fdLevel;
*/

// Animation
// TODO tile sheets, animations, etc

#endif

