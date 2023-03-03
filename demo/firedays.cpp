
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_core_init (fdCore* c) {
	try {
		ng::init();
		ng_time_init(&c->time);
		ng_graphics_init(&c->graphics, "Fire Days Demo", 640, 480);
		//TODO audio & channels
		ng_event_init(&c->event, &c->graphics);
	} catch (const std::exception& ex) {
		std::cout << NG_HERE << ": can't init: " << ex.what();
		exit(EXIT_FAILURE);
	}
}

void fd_core_quit (fdCore* c) {
	ng_graphics_quit(&c->graphics);
	ng::quit();
}

void fd_screen_init (fdScreen* s) {
	s->mode = FD_TITLESCREEN;
	ng_rect_init(&s->rect, 0, 0, 640, 480); // 4:3
	ng_grid_init(&s->char_grid, &s->rect, 80, 30); // 80x30 8x16 chars 4:3
	ng_grid_init(&s->tile_grid, &s->rect, 40, 30); // 40x30 16x16 tiles 4:3
	ng_color_init(&s->background_color, 0, 0, 0);
	ng_color_init(&s->draw_color, 255, 255, 255);
}

//TODO image bank
//TODO clip bank

void fd_frame_mouse(ngRect* r, fdCore* c, fdScreen* s, ngRect* frame) {
	ng_rect_init(r, c->event.mouse.x, c->event.mouse.y, 0, 0);
	ng_rect_portal(r, &c->graphics.rect, &s->rect);
	ng_absolute_to_relative(r, NULL, &s->tile_grid);
	if (frame != NULL) {
		ng_absolute_to_relative(r, frame, NULL);
	}
}

void fd_frame_draw_rect(const ngRect* r, fdCore* c, fdScreen* s, ngRect* frame) {
	ngRect r2 = *r;
	if (frame != NULL) {
		ng_relative_to_absolute(&r2, frame, NULL);
	}
	ng_relative_to_absolute(&r2, NULL, &s->tile_grid);
	ng_rect_portal(&r2, &s->rect, &c->graphics.rect);
	ng_draw_rect(&c->graphics, &r2, NG_FRAME);
}


