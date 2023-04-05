
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngtime.h"

// Pause for at least 1 millisecond (ms).
// Returns ms since program start (might overflow).
// 'last' is the value returned from previous call to tick(), or 0.
uint32_t ng::tick (uint32_t last) {
	uint32_t now;
	now = SDL_GetTicks();
	// Pause until time difference is large enough to measure.
	// Some OS do not pause for very short time periods, so this must be a loop.
	for (int i=1; now == last; i++) {
		SDL_Delay(i);
		now = SDL_GetTicks();
	}
	return now;
}

// Calculate ms time difference between 'now' and 'last', regardless of overflow.
// Call tick() to get 'now' before calling delta().
int ng::delta (uint32_t now, uint32_t last) {
	int delta;
	if (now > last) {
		delta = now - last;
	} else {
		// 'now' overflowed during tick(). use 64-bit to calculate delta.
		uint64_t now64, last64;
		now64 = static_cast<uint64_t>(now) + static_cast<uint64_t>(UINT32_MAX);
		last64 = static_cast<uint64_t>(last);
		delta = static_cast<int>(now64 - last64);
	}
	return delta;
}

// Calculate ticks per second (tps), given:
//  - accummulated ticks and ms this second.
//  - delta ms this tick.
// Designed to be called every tick.
// acc_ticks and acc_ms reset to 0 when tps is re-calculated each second.
int ng::tps (int tps, int delta, int* acc_ticks, int* acc_ms) {
	*acc_ticks = *acc_ticks + 1;
	*acc_ms += delta;
	// tps = ticks per 1000 ms
	if (*acc_ms >= 1000) {
		tps = *acc_ticks;
		*acc_ms = 0;
		*acc_ticks = 0;
	}
	return tps;
}

ng::Time::Time () {
	this->now = 0;
	this->last = 0;
	this->acc_ticks = 0;
	this->acc_ms = 0;
	this->delta = 0;
	this->tps = 0;
	this->ticks = 0;
	this->max = 0;
}

ng::Time::~Time () {}

void ng::Time::reset () {
	// internal
	this->now = SDL_GetTicks();
	this->last = this->now;
	this->acc_ticks = 0;
	this->acc_ms = 0;
	// public
	this->delta = 10;
	this->tps = 100;
	this->ticks = 0;
	this->max = 10;
}

void ng::Time::tick () {
	this->now = ng::tick(this->last);
	this->delta = ng::delta(this->now, this->last);
	this->tps = ng::tps(this->tps, this->delta, &this->acc_ticks, &this->acc_ms);	
	this->last = this->now;
	this->ticks++;
	
	if (this->delta > this->max) {
		this->max = this->delta;
	}
}


