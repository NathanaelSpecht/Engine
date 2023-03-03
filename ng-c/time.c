
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_time_init (ngTime* t) {
	t->now = SDL_GetTicks();
	t->last = t->now;
	t->ticks = 0;
	t->delta = 10;
	t->tps = 100;
	t->count = 0;
	t->ms = 0;
}

void ng_time_tick (ngTime* t) {
	t->now = SDL_GetTicks();
	// if last tick was too fast to measure, delay for minimum time needed
	for (int i=1; t->now == t->last; i++) {
		SDL_Delay(i);
		t->now = SDL_GetTicks();
	}
	// Calculate delta time, using 64-bit to avoid overflows
	if (t->now > t->last) {
		t->delta = (int)((int64_t)(t->now) - t->last);
	} else {
		t->delta = (int)(((int64_t)UINT32_MAX + t->now) - t->last);
	}
	t->last = t->now;
	t->ticks++;
	t->count++;
	t->ms += t->delta;
	if (t->ms >= 1000) { // tps = ticks per second = ticks per 1000 ms
		t->tps = t->count;
		t->count = 0;
		t->ms = 0;
	}
}

