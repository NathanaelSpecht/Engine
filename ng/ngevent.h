
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#ifndef NGEVENT_H
#define NGEVENT_H

#include "ngcore.h"
#include "nggraphics.h"

#define NG_EVENT_TEXT 33

namespace ng {

	enum EnumEvent {
		Quit = 1,
		WindowEvent = 2,
		MousePress = 3,
		MouseRelease = 4,
		MouseMove = 5,
		MouseScroll = 6,
		KeyPress = 7,
		KeyRelease = 8,
		TextInput = 9
	};

	class Mouse {
	public:
		bool left;
		bool middle;
		bool right;
		int x;
		int y;
		int dx;
		int dy;
		int scroll_x;
		int scroll_y;
		
		Mouse ();
		~Mouse ();
		
		// Internal. Called by event::init.
		void reset ();
		
		// Internal. Called by event::next.
		// Set this to mouse press event from SDL.
		bool press (SDL_Event* const);
		
		// Internal. Called by event::next.
		// Set this to mouse release event from SDL.
		bool release (SDL_Event* const);
		
		// Internal. Called by event::next.
		// Set this to mouse move event from SDL.
		void move (SDL_Event* const);
		
		// Internal. Called by event::next.
		// Set this to mouse scroll event from SDL.
		void scroll (SDL_Event* const);
	};
	
	class Key {
	public:
		int scancode; // SDL_Scancode
		int keycode; // SDL_Keycode
		bool lshift;
		bool rshift;
		bool lctrl;
		bool rctrl;
		bool lalt;
		bool ralt;
		bool caps;
		
		Key ();
		~Key ();
		
		// Internal. Called by event::init.
		void reset ();
		
		// Internal. Called by event::next.
		// Set this to key press event from SDL.
		void press (SDL_Event* const);
		
		// Internal. Called by event::next.
		// Set this to key release event from SDL.
		void release (SDL_Event* const);
	};
	
	class Event {
	public:
		int mode;
		Mouse mouse;
		Key key;
		
		// UTF-8 text. Always ends in '\0' (max input is 32, +1 for nul)
		char text[NG_EVENT_TEXT]; // ARRAY! DO NOT FREE!
		
		// Internal.
		// Pointer to graphics, so this can handle window events internally.
		Graphics* graphics;
		
		// Internal SDL event.
		SDL_Event event;
		
		Event ();
		~Event ();
		
		void reset (Graphics* const);
		
		// Set this to next event and return true, or
		// there are no events so set mode = ng::None and return false.
		bool next ();
		
		// Set mode = ng::None.
		void consume ();
		
		// Return mode != ng::None.
		bool exists ();
		
		// Internal. Called by next.
		// Set this to text input event from SDL.
		void text_input (SDL_Event* const);
		
		// Internal. Called by next.
		// Set graphics to window event from SDL.
		void window_event (SDL_Event* const);
	};

}

#endif


