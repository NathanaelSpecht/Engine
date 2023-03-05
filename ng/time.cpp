
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng::Time::init () {
	this->now = SDL_GetTicks();
	this->last = this->now;
	this->ticks = 0;
	this->delta = 10;
	this->tps = 100;
	this->count = 0;
	this->ms = 0;
}

void ng::Time::tick () {
	this->now = SDL_GetTicks();
	// if last tick was too fast to measure, delay for minimum time needed
	for (int i=1; this->now == this->last; i++) {
		SDL_Delay(i);
		this->now = SDL_GetTicks();
	}
	// Calculate delta time, using 64-bit to avoid overflows
	if (this->now > this->last) {
		this->delta = (int)((int64_t)(this->now) - this->last);
	} else {
		this->delta = (int)(((int64_t)UINT32_MAX + this->now) - this->last);
	}
	this->last = this->now;
	this->ticks++;
	this->count++;
	this->ms += this->delta;
	if (this->ms >= 1000) { // tps = ticks per second = ticks per 1000 ms
		this->tps = this->count;
		this->count = 0;
		this->ms = 0;
	}
}

/*
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
*/

