
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_filescreen_init (fdFileScreen* s, fdScreen* screen, fdCore* core) {
	s->core = core;
	s->screen = screen;
	// tiles
	ng_rect_init(&s->header, 5, 1, 30, 3);
	ng_rect_init(&s->frame, 1, 5, 38, 24);
	// tiles in frame
	ng_rect_init(&s->save1, 1, 1, 36, 5);
}

void fd_filescreen_event (fdFileScreen* s) {
	ngEvent* e = &s->core->event;
	// if mouse press save1, then worldscreen
	// if key press escape, then titlescreen
	if (e->mode == NG_MOUSE_PRESS) {
		ngRect p;
		fd_frame_mouse(&p, s->core, s->screen, &s->frame);
		
		if (ng_rect_contains(&s->save1, p.x, p.y)) {
			s->screen->mode = FD_WORLDSCREEN;
		}
	} else if (e->mode == NG_KEY_PRESS) {
		int k = e->key.scancode;
		
		if (k == SDL_SCANCODE_ESCAPE) {
			s->screen->mode = FD_TITLESCREEN;
		}
	}
}

void fd_filescreen_draw (fdFileScreen* s) {
	fd_frame_draw_rect(&s->header, s->core, s->screen, NULL);
	fd_frame_draw_rect(&s->frame, s->core, s->screen, NULL);
	fd_frame_draw_rect(&s->save1, s->core, s->screen, &s->frame);
}


