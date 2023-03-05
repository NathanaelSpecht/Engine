
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

int main (int argc, char** argv) {
	fd::GameState game;
	game.init();
	game.loop();
	game.quit();
	return EXIT_SUCCESS;
}


