
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

// Private API

void fd_title_screen_init (fdTitleScreen*);
void fd_title_screen_draw (fdTitleScreen*, ngGraphics*, ngView*);
//void fd_file_screen_init (fdFileScreen*);
//void fd_file_screen_draw (fdFileScreen*, ngGraphics*, ngView*);
//void fd_world_screen_init (fdWorldScreen*);
//void fd_world_screen_draw (fdWorldScreen*, ngGraphics*, ngView*);
void fd_level_screen_init (fdLevelScreen*);
void fd_level_screen_draw (fdLevelScreen*, ngGraphics*, ngView*);
//void fd_creative_screen_init (fdCreativeScreen*);
//void fd_creative_screen_draw (fdCreativeScreen*, ngGraphics*, ngView*);
//void fd_debug_screen_init (fdDebugScreen*);
//void fd_debug_screen_draw (fdDebugScreen*, ngGraphics*, ngView*);

// Public API Implementation

void fd_screen_init (fdScreen* s, ngGraphics* g) {
	//TODO view
	s->mode = FD_NONE;
	fd_title_screen_init(&(s->title));
	fd_level_screen_init(&(s->level));
}

void fd_screen_draw (fdScreen* s, ngGraphics* g) {
	switch (s->mode) {
		case FD_TITLE: {
			fd_title_screen_draw(&(s->title), g, &(s->view));
			break;
		} case FD_LEVEL: {
			fd_level_screen_draw(&(s->level), g, &(s->view));
			break;
		}
	}
}

// Private API Implementation

void fd_title_screen_init (fdTitleScreen* s) {
	//TODO
}

void fd_title_screen_draw (fdTitleScreen* s, ngGraphics* g, ngView* v) {
	//TODO
}

//void fd_file_screen_init (fdFileScreen* s);

//void fd_file_screen_draw (fdFileScreen* s, ngGraphics* g, ngView* v);

//void fd_world_screen_init (fdWorldScreen* s);

//void fd_world_screen_draw (fdWorldScreen* s, ngGraphics* g, ngView* v);

void fd_level_screen_init (fdLevelScreen* s) {
	//TODO
}

void fd_level_screen_draw (fdLevelScreen* s, ngGraphics* g, ngView* v) {
	//TODO
}

//void fd_creative_screen_init (fdCreativeScreen* s);

//void fd_creative_screen_draw (fdCreativeScreen* s, ngGraphics* g, ngView* v);

//void fd_debug_screen_init (fdDebugScreen* s);

//void fd_debug_screen_draw (fdDebugScreen* s, ngGraphics* g, ngView* v);


