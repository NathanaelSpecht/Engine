
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

void frame_mouse(ng::Rect* r, GameState* gs, ng::Rect* frame);
void frame_draw_rect(const ng::Rect* r, GameState* gs);
void frame_draw_rect(const ng::Rect* r, GameState* gs, ng::Rect* frame);

class TitleScreen {
public:
	ng::Rect header;
	ng::Canvas canvas;
	ng::Rect start_btn;
	ng::Rect quit_btn;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class FileScreen {
public:
	ng::Rect header;
	ng::Canvas canvas;
	ng::Rect save1;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class WorldScreen {
public:
	ng::Rect header;
	ng::Canvas canvas;
	ng::Rect level1;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class LevelScreen {
public:
	ng::Canvas canvas;
	
	void init (GameState* gs);
	void event (GameState* gs);
	void draw (GameState* gs);
};

class HudMenu {
public:
	bool events;
	bool draws;
	ng::Canvas canvas;
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
	ng::Canvas canvas;
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
	ng::Canvas canvas;
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
	
	ng::Canvas canvas;
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

