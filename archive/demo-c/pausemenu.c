
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "fireday.h"

void fd_pausemenu_init (fdPauseMenu* m, fdScreen* screen, fdCore* core) {
	m->core = core;
	m->screen = screen;
	// tiles
	ng_rect_init(&m->header, 5, 5, 30, 3);
	ng_rect_init(&m->frame, 14, 13, 12, 5);
	// tiles in frame
	ng_rect_init(&m->resume_btn, 1, 1, 10, 1);
	ng_rect_init(&m->quit_btn, 1, 3, 10, 1);
}

void fd_pausemenu_event (fdPauseMenu* m) {
	ngEvent* e = &m->core->event;
	// if key press escape, then toggle pausemenu
	if (e->mode == NG_KEY_PRESS) {
		int k = e->key.scancode;
		
		if (k == SDL_SCANCODE_ESCAPE) {
			m->mode = !m->mode;
			return;
		}
	}
	
	if (!m->mode) {
		return;
	}
	// if mouse press resume, then hide pausemenu
	// if mouse press quit, then hide pausemenu and goto worldscreen
	if (e->mode == NG_MOUSE_PRESS) {
		ngRect p;
		fd_frame_mouse(&p, m->core, m->screen, &m->frame);
		
		if (ng_rect_contains(&m->resume_btn, p.x, p.y)) {
			m->mode = FD_NONE;
		} else if (ng_rect_contains(&m->quit_btn, p.x, p.y)) {
			m->screen->mode = FD_WORLDSCREEN;
		}
	}
}

void fd_pausemenu_draw (fdPauseMenu* m) {
	if (!m->mode) {
		return;
	}
	
	fd_frame_draw_rect(&m->header, m->core, m->screen, NULL);
	fd_frame_draw_rect(&m->frame, m->core, m->screen, NULL);
	fd_frame_draw_rect(&m->resume_btn, m->core, m->screen, &m->frame);
	fd_frame_draw_rect(&m->quit_btn, m->core, m->screen, &m->frame);
}


