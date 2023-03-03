
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng::init () {
	int retval = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
	if (retval != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void ng::quit () {
	SDL_Quit();
}


