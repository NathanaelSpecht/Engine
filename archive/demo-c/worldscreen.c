
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "fireday.h"

void fd_worldscreen_init (fdWorldScreen* s, fdScreen* screen, fdCore* core) {
	s->core = core;
	s->screen = screen;
	// tiles
	ng_rect_init(&s->header, 5, 1, 30, 3);
	ng_rect_init(&s->frame, 1, 5, 38, 24);
	// tiles in frame
	ng_rect_init(&s->level1, 1, 1, 4, 3);
}

void fd_worldscreen_event (fdWorldScreen* s) {
	ngEvent* e = &s->core->event;
	// if mouse press level1, then levelscreen
	// if key press escape, then filescreen
	if (e->mode == NG_MOUSE_PRESS) {
		ngRect p;
		fd_frame_mouse(&p, s->core, s->screen, &s->frame);
		
		if (ng_rect_contains(&s->level1, p.x, p.y)) {
			s->screen->mode = FD_LEVELSCREEN;
		}
	} else if (e->mode == NG_KEY_PRESS) {
		int k = e->key.scancode;
		
		if (k == SDL_SCANCODE_ESCAPE) {
			s->screen->mode = FD_FILESCREEN;
		}
	}
}

void fd_worldscreen_draw (fdWorldScreen* s) {
	fd_frame_draw_rect(&s->header, s->core, s->screen, NULL);
	fd_frame_draw_rect(&s->frame, s->core, s->screen, NULL);
	fd_frame_draw_rect(&s->level1, s->core, s->screen, &s->frame);
}


