
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * Fire Days API
 */


#ifndef FIREDAYS_H
#define FIREDAYS_H

#include "ng.h"

// Fire Days
namespace fd {

// Every code that can be something or nothing uses fd::None for nothing.
enum EnumNone {
	None = 0
};

enum EnumScreen {
	ScreenTitle = 1,
	ScreenFile = 2,
	ScreenWorld = 3,
	ScreenLevel = 4
};

enum EnumMenuHud {
	MenuHud = 1
};

enum EnumMenuPause {
	MenuPause = 1
};

enum EnumMenuDebug {
	MenuDebug = 1
};

class GameState;
class TitleScreen;
class FileScreen;
class WorldScreen;
class LevelScreen;
class HudMenu;
class PauseMenu;
class DebugMenu;

void frame_mouse(ng::Rect* r, GameState* gs, ng::Rect* frame);
void frame_draw_rect(const ng::Rect* r, GameState* gs, ng::Rect* frame);

class GameState {
public:
	ng::Time time;
	ng::Graphics graphics;
	//TODO audio & channels
	ng::Event event;
	
	ng::Rect rect;
	ng::Grid char_grid;
	ng::Grid tile_grid;
	ng::Color background_color;
	ng::Color draw_color;
	
	int screen_mode;
	TitleScreen title_screen;
	FileScreen file_screen;
	WorldScreen world_screen;
	LevelScreen level_screen;
	
	int hud_mode;
	HudMenu hud_menu;
	
	int pause_mode;
	PauseMenu pause_menu;
	
	int debug_mode;
	DebugMenu debug_menu;
	
	void init ();
	void loop ();
	void quit ();
};

class TitleScreen {
public:
	ng::Rect header;
	ng::Rect frame;
	ng::Rect start_btn;
	ng::Rect quit_btn;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class FileScreen {
public:
	ng::Rect header;
	ng::Rect frame;
	ng::Rect save1;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class WorldScreen {
public:
	ng::Rect header;
	ng::Rect frame;
	ng::Rect level1;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class LevelScreen {
public:
	ng::Rect frame;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class HudMenu {
public:
	ng::Rect frame;
	ng::Rect temp;
	ng::Rect heat;
	ng::Rect fuel;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class PauseMenu {
public:
	ng::Rect header;
	ng::Rect frame;
	ng::Rect resume_btn;
	ng::Rect quit_btn;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class DebugMenu {
public:
	ng::Rect frame;
	ng::Rect version;
	ng::Rect fps;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

} // namespace fd

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

