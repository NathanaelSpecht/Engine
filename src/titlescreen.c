
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_titlescreen_init (fdTitleScreen* s, fdScreen* screen, fdCore* core) {
	s->core = core;
	s->screen = screen;
	// tiles
	ng_rect_init(&s->header, 5, 5, 30, 10);
	ng_rect_init(&s->frame, 14, 20, 12, 5);
	// tiles in frame
	ng_rect_init(&s->start_btn, 1, 1, 10, 1);
	ng_rect_init(&s->quit_btn, 1, 3, 10, 1);
}

void fd_titlescreen_event (fdTitleScreen* s) {
	ngEvent* e = &s->core->event;
	// if mouse press start, then filescreen
	// if mouse press quit, then quit
	if (e->mode == NG_MOUSE && e->mouse.event == NG_MOUSE_PRESS) {
		ngRect p;
		fd_frame_mouse(&p, s->core, s->screen, &s->frame);
		
		if (ng_rect_contains(&s->start_btn, p.x, p.y)) {
			s->screen->mode = FD_FILESCREEN;
		} else if (ng_rect_contains(&s->quit_btn, p.x, p.y)) {
			s->screen->mode = FD_NONE;
		}
	}
}

void fd_titlescreen_draw (fdTitleScreen* s) {
	fd_frame_draw_rect(&s->header, s->core, s->screen, NULL);
	fd_frame_draw_rect(&s->frame, s->core, s->screen, NULL);
	fd_frame_draw_rect(&s->start_btn, s->core, s->screen, &s->frame);
	fd_frame_draw_rect(&s->quit_btn, s->core, s->screen, &s->frame);
}


