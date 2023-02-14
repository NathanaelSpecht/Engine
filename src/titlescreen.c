
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
	if (e->mode == NG_MOUSE && e->mouse.event == NG_MOUSE_PRESS) {
		ngRect p;
		ng_rect_init(&p, e->mouse.x, e->mouse.y, 0, 0);
		ng_rect_portal(&p, &s->core->graphics.rect, &s->screen->rect);
		ng_absolute_to_relative(&p, NULL, &s->screen->tile_grid);
		ng_absolute_to_relative(&p, &s->frame, NULL);
		
		if (ng_rect_contains(&s->quit_btn, p.x, p.y)) {
			s->screen->mode = FD_NONE;
		} else if (ng_rect_contains(&s->start_btn, p.x, p.y)) {
			s->screen->mode = FD_FILESCREEN;
		}
	}
}

void fd_titlescreen_draw (fdTitleScreen* s) {
	ngRect r;
	
	r = s->header;
	ng_relative_to_absolute(&r, NULL, &s->screen->tile_grid);
	ng_rect_portal(&r, &s->screen->rect, &s->core->graphics.rect);
	ng_draw_rect(&s->core->graphics, &r, NG_FRAME);
	
	r = s->frame;
	ng_relative_to_absolute(&r, NULL, &s->screen->tile_grid);
	ng_rect_portal(&r, &s->screen->rect, &s->core->graphics.rect);
	ng_draw_rect(&s->core->graphics, &r, NG_FRAME);
	
	r = s->start_btn;
	ng_relative_to_absolute(&r, &s->frame, NULL);
	ng_relative_to_absolute(&r, NULL, &s->screen->tile_grid);
	ng_rect_portal(&r, &s->screen->rect, &s->core->graphics.rect);
	ng_draw_rect(&s->core->graphics, &r, NG_FRAME);
	
	r = s->quit_btn;
	ng_relative_to_absolute(&r, &s->frame, NULL);
	ng_relative_to_absolute(&r, NULL, &s->screen->tile_grid);
	ng_rect_portal(&r, &s->screen->rect, &s->core->graphics.rect);
	ng_draw_rect(&s->core->graphics, &r, NG_FRAME);
}


