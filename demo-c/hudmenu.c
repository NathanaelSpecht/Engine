
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "fireday.h"

void fd_hudmenu_init (fdHudMenu* m, fdScreen* screen, fdCore* core) {
	m->core = core;
	m->screen = screen;
	m->mode = FD_NONE;
	// tiles
	ng_rect_init(&m->frame, 1, 1, 18, 5);
	// tiles in frame
	ng_rect_init(&m->temp, 1, 1, 3, 3);
	ng_rect_init(&m->heat, 5, 1, 13, 2);
	ng_rect_init(&m->fuel, 5, 3, 13, 1);
}

void fd_hudmenu_event (fdHudMenu* m) {
	ngEvent* e = &m->core->event;
	// if key press f1, then toggle hudmenu
	if (e->mode == NG_KEY_PRESS) {
		int k = e->key.scancode;
		
		if (k == SDL_SCANCODE_F1) {
			m->mode = !m->mode;
		}
	}
}

void fd_hudmenu_draw (fdHudMenu* m) {
	if (!m->mode) {
		return;
	}
	
	fd_frame_draw_rect(&m->frame, m->core, m->screen, NULL);
	fd_frame_draw_rect(&m->temp, m->core, m->screen, &m->frame);
	fd_frame_draw_rect(&m->heat, m->core, m->screen, &m->frame);
	fd_frame_draw_rect(&m->fuel, m->core, m->screen, &m->frame);
}


