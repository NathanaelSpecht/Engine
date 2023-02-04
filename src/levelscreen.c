
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_levelscreen_init (fdLevelScreen* s, fdGameState* g) {
	fd_hudmenu_init(&s->hud_menu, g);
	fd_pausemenu_init(&s->pause_menu, g);
}

void fd_levelscreen_event (fdLevelScreen* s, fdGameState* g) {
	//TODO
}

void fd_levelscreen_draw (fdLevelScreen* s, fdGameState* g) {
	fd_hudmenu_draw(&s->hud_menu, g);
	fd_pausemenu_draw(&s->pause_menu, g);
}


