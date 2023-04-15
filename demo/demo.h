
/* Copyright (C) 2022 - 2023 Nathanael Specht
 * Demo API
 */


#ifndef DEMO_H
#define DEMO_H

#include "ng.h"

// Fire Days
namespace demo {

	// Every code that can be something or nothing uses fd::None for nothing.
	enum EnumNone {
		None = 0
	};
	
	enum EnumScreenMode {
		TitleMode = 1,
		LevelMode = 2
	};
	
	enum EnumMenuEvent {
		MenuYes = 1,
		MenuNo = 2
	};
	
	class Menu;
	class Screen;
	class Core;
	
	class Menu {
	public:
		ng::Canvas canvas;
		ng::Rect2 header;
		ng::Button yes_button;
		ng::Button no_button;
		bool events;
		bool draws;
		
		Menu ();
		~Menu ();
		
		void set_title (Core* core, const char* yes_text, const char* no_text);
		void set_pause (Core* core, const char* yes_text, const char* no_text);
		int event (Core* core);
		void draw (Core* core);
	};
	
	class Screen {
	public:
		int mode;
		ng::Canvas canvas;
		ng::Color canvas_fillcolor;
		ng::Color canvas_framecolor;
		ng::Vec2 mouse;
		
		demo::Menu title;
		demo::Menu pause;
		
		Screen ();
		~Screen ();
		
		void reset (Core* core);
		void set_mode (int mode);
		void event (Core* core);
		void draw (Core* core);
	};
	
	class Core {
	public:
		ng::Event event;
		ng::Graphics graphics;
		ng::Audio audio;
		ng::Time time;
		
		ng::Tileset font;
		ng::Image font_img;
		
		ng::Clip crazy_music;
		ng::Channel music_channel;
		ng::Channel sound_channel;
		
		Screen screen;
		
		Core ();
		~Core ();
		
		void reset ();
		void loop ();
		void quit ();
	};
	
} // demo

#endif

