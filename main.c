
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"
#include "firedays.h"

int main (int argc, char** argv) {
	
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		ng_here();
		printf("can't init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	// init game
	fdGameState game;
	game.screen_mode = NULL;
	game.screen_rect = NULL;
	game.char_grid = NULL;
	game.tile_grid = NULL;
	game.g = NULL;
	game.mouse = NULL;
	game.key = NULL;
	
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
	ngRect screen_rect;
	ng_rect_init(&screen_rect, 0, 0, 640, 480);
	game.screen_rect = &screen_rect;
	// ^ 4:3
	ngGrid char_grid;
	ng_grid_init(&char_grid, &screen_rect, 80, 30);
	game.char_grid = &char_grid;
	// ^ 80x30 8x16 chars, 4:3
	ngGrid tile_grid;
	ng_grid_init(&tile_grid, &screen_rect, 40, 30);
	game.tile_grid = &tile_grid;
	// ^ 40x30 16x16 tiles, 4:3
	
	ngGraphics g;
	if (!ng_graphics_init(&g, "Fire Days Demo", screen_rect.w, screen_rect.h)) {
		ng_here();
		printf("can't init graphics\n");
		exit(EXIT_FAILURE);
	}
	game.g = &g;
	ngColor background_color;
	ng_color_init(&background_color, 0, 0, 0);
	ngColor draw_color;
	ng_color_init(&draw_color, 255, 255, 255);
	
	int screen_mode = FD_TITLESCREEN;
	game.screen_mode = &screen_mode;
	
	fdTitleScreen title_screen;
	fd_titlescreen_init(&title_screen, &game);
	// ^ start
	fdFileScreen file_screen;
	fd_filescreen_init(&file_screen, &game);
	// ^ save select
	fdWorldScreen world_screen;
	fd_worldscreen_init(&world_screen, &game);
	// ^ level select
	fdLevelScreen level_screen;
	fd_levelscreen_init(&level_screen, &game);
	// ^ playing level
	fdDebugMenu debug_menu;
	fd_debugmenu_init(&debug_menu, &game);
	// ^ debug overlay
	
	ngColor color_key;
	ng_color_init(&color_key, 0, 0, 0);
	// ^ bmp transparent color
	// load image bank
	
	// start game
	//ng_channel_start_sound(&music, &music_breath, NG_LOOP);
	//ng_audio_play(&a);
	
	// init event
	SDL_Event event;
	ngMouse mouse;
	ng_mouse_init(&mouse);
	game.mouse = &mouse;
	ngKey key;
	ng_key_init(&key);
	game.key = &key;
	
	while (true) {
		while (SDL_PollEvent(&event)) {
			mouse.event = NG_NONE;
			key.event = NG_NONE;
			switch (event.type) {
				case SDL_QUIT: {
					goto quit;
				} case SDL_WINDOWEVENT: {
					ng_window_event(&g, &event);
					break;
				} case SDL_KEYDOWN: {
					ng_key_press(&key, &event);
					break;
				} case SDL_KEYUP: {
					ng_key_release(&key, &event);
					break;
				} case SDL_TEXTINPUT: {
					ng_text_input(&key, &event);
					break;
				} case SDL_MOUSEBUTTONDOWN: {
					ng_mouse_press(&mouse, &event);
					break;
				} case SDL_MOUSEBUTTONUP: {
					ng_mouse_release(&mouse, &event);
					break;
				} case SDL_MOUSEMOTION: {
					ng_mouse_move(&mouse, &event);
					break;
				} case SDL_MOUSEWHEEL: {
					ng_mouse_scroll(&mouse, &event);
					break;
				}
			}
			
			switch (screen_mode) {
				case FD_TITLESCREEN: {
					fd_titlescreen_event(&title_screen, &game);
					break;
				} case FD_FILESCREEN: {
					fd_filescreen_event(&file_screen, &game);
					break;
				} case FD_WORLDSCREEN: {
					fd_worldscreen_event(&world_screen, &game);
					break;
				} case FD_LEVELSCREEN: {
					fd_levelscreen_event(&level_screen, &game);
					break;
				}
			}
			fd_debugmenu_event(&debug_menu, &game);
		}
		
		{ // graphics
			ng_graphics_color(&g, &background_color);
			ng_graphics_clear(&g);
			
			ng_graphics_color(&g, &draw_color);
			switch (screen_mode) {
				case FD_TITLESCREEN: {
					fd_titlescreen_draw(&title_screen, &game);
					break;
				} case FD_FILESCREEN: {
					fd_filescreen_draw(&file_screen, &game);
					break;
				} case FD_WORLDSCREEN: {
					fd_worldscreen_draw(&world_screen, &game);
					break;
				} case FD_LEVELSCREEN: {
					fd_levelscreen_draw(&level_screen, &game);
					break;
				}
			}
			fd_debugmenu_draw(&debug_menu, &game);
			
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
	
	ng_graphics_quit(&g);
	
	SDL_Quit();
	return EXIT_SUCCESS;
}

