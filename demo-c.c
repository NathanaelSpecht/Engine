
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"
#include "fireday.h"

int main (int argc, char** argv) {
	fdCore core;
	fdScreen screen;
	fdTitleScreen title_screen;
	fdFileScreen file_screen;
	fdWorldScreen world_screen;
	fdLevelScreen level_screen;
	fdDebugMenu debug_menu;
	
	fd_core_init(&core);
	fd_screen_init(&screen);
	fd_titlescreen_init(&title_screen, &screen, &core);
	fd_filescreen_init(&file_screen, &screen, &core);
	fd_worldscreen_init(&world_screen, &screen, &core);
	fd_levelscreen_init(&level_screen, &screen, &core);
	fd_debugmenu_init(&debug_menu, &screen, &core);
	
	while (true) {
		while (ng_event_next(&core.event)) {
			if (core.event.mode == NG_QUIT) {
				goto quit;
			}
			
			switch (screen.mode) {
				case FD_TITLESCREEN: {
					fd_titlescreen_event(&title_screen);
					break;
				} case FD_FILESCREEN: {
					fd_filescreen_event(&file_screen);
					break;
				} case FD_WORLDSCREEN: {
					fd_worldscreen_event(&world_screen);
					break;
				} case FD_LEVELSCREEN: {
					fd_levelscreen_event(&level_screen);
					break;
				} default: {
					goto quit;
				}
			}
			fd_debugmenu_event(&debug_menu);
		}
		
		{
			ng_graphics_color(&core.graphics, &screen.background_color);
			ng_graphics_clear(&core.graphics);
			
			ng_graphics_color(&core.graphics, &screen.draw_color);
			switch (screen.mode) {
				case FD_TITLESCREEN: {
					fd_titlescreen_draw(&title_screen);
					break;
				} case FD_FILESCREEN: {
					fd_filescreen_draw(&file_screen);
					break;
				} case FD_WORLDSCREEN: {
					fd_worldscreen_draw(&world_screen);
					break;
				} case FD_LEVELSCREEN: {
					fd_levelscreen_draw(&level_screen);
					break;
				}
			}
			fd_debugmenu_draw(&debug_menu);
			
			ng_graphics_draw(&core.graphics);
		}
		
		{ //TODO audio
			/*
			ng_audio_clear(&a);
			ng_audio_mix_channel(&a, &music);
			ng_audio_mix_channel(&a, &sound);
			ng_audio_queue(&a);
			*/
		}
		
		ng_time_tick(&core.time);
	}
	
quit:
	fd_core_quit(&core);
	return EXIT_SUCCESS;
}

