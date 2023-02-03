
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_level_screen_init (fdLevelScreen* s) {
	//TODO
	fd_hud_menu_init(&s->hud_menu);
	fd_pause_menu_init(&s->pause_menu);
}

void fd_level_screen_draw (fdLevelScreen* s, ngGraphics* g) {
	//TODO
	fd_hud_menu_draw(&s->hud_menu, g);
	fd_pause_menu_draw(&s->pause_menu, g);
}


