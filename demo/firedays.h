
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

class GameState;
class TitleScreen;
class FileScreen;
class WorldScreen;
class LevelScreen;
class HudMenu;
class PauseMenu;
class DebugMenu;

/*
// TODO add to ng:
class Canvas;

class Canvas {
public:
	Graphics* graphics;
	Canvas* parent;
	
	// Rect is edge of canvas.
	// May either be relative to parent (default), or a portal to parent.
	bool portal;
	Rect rect;
	
	// Grid applies to get_mouse(), and text, tile, image, and rect draw().
	bool use_grid;
	Grid grid;
	
	// Root canvas is graphics!
	// Root has neither parent nor grid. Uses graphics rect.
	void init (Graphics*);
	
	// Child canvas uses parent graphics, and might use grid.
	void init (Canvas*, const Rect*);
	void init (Canvas*, const Rect*, const Grid*);
	void init_portal (Canvas*, const Rect*);
	void init_portal (Canvas*, const Rect*, const Grid*);
	
	// Given event mouse point on root canvas, find mouse point on this canvas.
	// Returns false if mouse point is outside this canvas.
	bool get_mouse (Event*, Rect*);
	
	// Draw this->rect on parent.
	// Clearing root canvas calls graphics clear().
	void clear ();
	
	// Given shape on this canvas, draw on parent canvas.
	// Drawing to root canvas draws on graphics.
	void draw_text (const Tileset*, const char*, const Rect*, const Grid*);
	void draw_tile (const Tileset*, const Rect*, const Rect*);
	void draw_image (const Image*);
	void draw_image (const Image*, const Rect*);
	void draw_image (const Image*, const Rect*, const Rect*);
	void draw_rect (Rect*, int);
	void draw_line (int, int, int, int);
	void draw_point (int, int);
};
*/

void frame_mouse(ng::Rect* r, GameState* gs, ng::Rect* frame);
void frame_draw_rect(const ng::Rect* r, GameState* gs);
void frame_draw_rect(const ng::Rect* r, GameState* gs, ng::Rect* frame);

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
	bool events;
	bool draws;
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
	bool events;
	bool draws;
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
	bool events;
	bool draws;
	ng::Rect frame;
	ng::Rect version;
	ng::Rect fps;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class GameState {
public:
	ng::Event event;
	ng::Graphics graphics;
	ng::Audio audio;
	ng::Time time;
	
	ng::Rect rect;
	ng::Grid char_grid;
	ng::Grid tile_grid;
	ng::Color background_color;
	ng::Color draw_color;
	
	ng::Clip crazy_music;
	ng::Channel music_channel;
	ng::Channel sound_channel;
	
	int screen_mode;
	TitleScreen title_screen;
	FileScreen file_screen;
	WorldScreen world_screen;
	LevelScreen level_screen;
	HudMenu hud_menu;
	PauseMenu pause_menu;
	DebugMenu debug_menu;
	
	void init ();
	void loop ();
	void quit ();
	
	void goto_screen (int screen_mode);
};

} // namespace fd

// Level
// TODO level data (fire, water, boxes, etc)

// Animation
// TODO animations, etc

#endif

