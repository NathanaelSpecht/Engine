
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_levelscreen_init (fdLevelScreen* s, fdScreen* screen, fdCore* core) {
	s->core = core;
	s->screen = screen;
	fd_hudmenu_init(&s->hud_menu, screen, core);
	fd_pausemenu_init(&s->pause_menu, screen, core);
}

void fd_levelscreen_event (fdLevelScreen* s) {
	//TODO
}

void fd_levelscreen_draw (fdLevelScreen* s) {
	fd_hudmenu_draw(&s->hud_menu);
	fd_pausemenu_draw(&s->pause_menu);
}


