
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_debugmenu_init (fdDebugMenu* m, fdScreen* screen, fdCore* core) {
	m->core = core;
	m->screen = screen;
}

void fd_debugmenu_event (fdDebugMenu* m) {
	if (m->mode) {
		//TODO
	}
}

void fd_debugmenu_draw (fdDebugMenu* m) {
	if (m->mode) {
		//TODO
	}
}


