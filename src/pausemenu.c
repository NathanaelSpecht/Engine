
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_pausemenu_init (fdPauseMenu* m, fdScreen* screen, fdCore* core) {
	m->core = core;
	m->screen = screen;
}

void fd_pausemenu_event (fdPauseMenu* m) {
	if (m->mode) {
		//TODO
	}
}

void fd_pausemenu_draw (fdPauseMenu* m) {
	if (m->mode) {
		//TODO
	}
}


