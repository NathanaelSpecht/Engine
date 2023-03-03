
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_debugmenu_init (fdDebugMenu* m, fdScreen* screen, fdCore* core) {
	m->core = core;
	m->screen = screen;
	// tiles
	ng_rect_init(&m->frame, 0, 29, 40, 1);
	// tiles in frame
	ng_rect_init(&m->version, 0, 0, 25, 1);
	ng_rect_init(&m->fps, 30, 0, 10, 1);
}

void fd_debugmenu_event (fdDebugMenu* m) {
	ngEvent* e = &m->core->event;
	// if key press f3, then toggle debugmenu
	if (e->mode == NG_KEY_PRESS) {
		int k = e->key.scancode;
		
		if (k == SDL_SCANCODE_F3) {
			m->mode = !m->mode;
		}
	}
}

void fd_debugmenu_draw (fdDebugMenu* m) {
	if (!m->mode) {
		return;
	}
	
	fd_frame_draw_rect(&m->frame, m->core, m->screen, NULL);
	fd_frame_draw_rect(&m->version, m->core, m->screen, &m->frame);
	fd_frame_draw_rect(&m->fps, m->core, m->screen, &m->frame);
}


