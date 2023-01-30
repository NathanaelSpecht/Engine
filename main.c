
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

int main (int argc, char** argv) {
	
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		ng_here();
		printf("can't init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// init time
	ngTime t;
	ng_time_init(&t);
	
	// init audio
	/*
	ngAudio a;
	ng_audio_init(&a);
	ngChannel music, sound;
	ng_channel_init(&music);
	ng_channel_init(&sound);
	
	ngClip music_breath, sound_glass;
	ng_clip_init(&a, &music_breath, "music/Breath.wav");
	ng_clip_init(&a, &sound_glass, "music/smashing-glass.wav");
	*/
	
	// init graphics
	ngGraphics g;
	if (ng_graphics_init(&g, "Engine", 640, 480) < 0) {
		// ^ 80x30 8x16 chars, 4:3
		ng_here();
		printf("can't init graphics\n");
		exit(EXIT_FAILURE);
	}
	ngFrame screen;
	ng_frame_init(&screen, 8, 16, g.w-16, g.h-32);
	
	ngImage title_image;
	ng_image_init(&g, &title_image, "art/title-screen.bmp", 0, 0, 0, 0, 0);
	
	// start game
	//ng_channel_start_sound(&music, &music_breath, NG_LOOP);
	//ng_audio_play(&a);
	
	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					goto quit;
				} /* case SDL_WINDOWEVENT: {
					switch (event.window.event) {
						case SDL_WINDOWEVENT_MAXIMIZED: {
							SDL_GetWindowSize(g->window, &(g->w), &(g->h));
							break;
						} case SDL_WINDOWEVENT_RESTORED: {
							SDL_GetWindowSize(g->window, &(g->w), &(g->h));
							break;
						} case SDL_WINDOWEVENT_SIZE_CHANGED: {
							g->w = event.window.data1;
							g->h = event.window.data2;
							break;
						}
					}
					break;
				} */ case SDL_KEYDOWN: {
					int scancode = event.key.keysym.scancode;
					switch (scancode) {
						case SDL_SCANCODE_ESCAPE: {
							break;
						} case SDL_SCANCODE_RETURN: {
							//ng_channel_start_sound(&sound, &sound_glass, NG_PLAYONCE);
							break;
						} case SDL_SCANCODE_SPACE: {
							break;
						} case SDL_SCANCODE_W: {
							//player.move_up = 1 * 3;
							break;
						} case SDL_SCANCODE_A: {
							//player.move_left = 1 * 3;
							break;
						} case SDL_SCANCODE_S: {
							//player.move_down = 1 * 3;
							break;
						} case SDL_SCANCODE_D: {
							//player.move_right = 1 * 3;
							break;
						}
					}
					break;
				} case SDL_KEYUP: {
					int scancode = event.key.keysym.scancode;
					switch (scancode) {
						case SDL_SCANCODE_W: {
							//player.move_up = 0;
							break;
						} case SDL_SCANCODE_A: {
							//player.move_left = 0;
							break;
						} case SDL_SCANCODE_S: {
							//player.move_down = 0;
							break;
						} case SDL_SCANCODE_D: {
							//player.move_right = 0;
							break;
						}
					}
					break;
				}
			}
		}
		
		{ // graphics
			ng_graphics_color(&g, 0, 0, 0);
			ng_graphics_clear(&g);
			
			SDL_Rect dest = {screen.x, screen.y, screen.w, screen.h};
			//ng_frame_out(&screen, &dest);
			ng_draw_image(&g, &title_image, NULL, &dest, SDL_FLIP_NONE, 0.0);
			ng_graphics_color(&g, 255, 0, 0);
			ng_draw_rect(&g, &dest, false);
			
			ng_graphics_draw(&g);
		}
		
		{ // audio
			/*
			ng_audio_clear(&a);
			ng_audio_mix_channel(&a, &music);
			ng_audio_mix_channel(&a, &sound);
			ng_audio_queue(&a);
			*/
		}
		
		ng_time_tick(&t);
	}
	
quit:
	/*
	ng_clip_quit(&music_breath);
	ng_clip_quit(&sound_glass);
	ng_channel_quit(&music);
	ng_channel_quit(&sound);
	ng_audio_quit(&a);
	*/
	
	ng_image_quit(&title_image);
	ng_graphics_quit(&g);
	
	SDL_Quit();
	return EXIT_SUCCESS;
}

