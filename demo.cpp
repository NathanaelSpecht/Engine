
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "demo.h"

int main (int argc, char** argv) {
	demo::Core game;
	game.reset();
	game.loop();
	game.quit();
	return EXIT_SUCCESS;
}


