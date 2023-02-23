
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_rect_init (ngRect* r, int x, int y, int w, int h) {
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
}

void ng_rect_to_sdl (SDL_Rect* r, const ngRect* copy) {
	r->x = copy->x;
	r->y = copy->y;
	r->w = copy->w;
	r->h = copy->h;
}

int ng_rect_contains (const ngRect* r, int x, int y) {
	int xc = ng_contains(r->x, r->w, x);
	int yc = ng_contains(r->y, r->h, y);
	if (!xc || !yc) {
		return NG_FALSE;
	} else if (xc == NG_EDGE || yc == NG_EDGE) {
		return NG_EDGE;
	} else {
		return NG_TRUE;
	}
}

int ng_rect_overlaps (const ngRect* r1, const ngRect* r2) {
	int xo = ng_overlaps(r1->x, r1->w, r2->x, r2->w);
	int yo = ng_overlaps(r1->y, r1->h, r1->y, r1->h);
	if (!xo || !yo) {
		return NG_FALSE;
	} else if (xo == NG_EDGE || yo == NG_EDGE) {
		return NG_EDGE;
	} else {
		return NG_TRUE;
	}
}

void ng_grid_init (ngGrid* g, const ngRect* r, int columns, int rows) {
	g->columns = columns;
	g->rows = rows;
	g->tile_w = (float)r->w / columns;
	g->tile_h = (float)r->h / rows;
}

void ng_absolute_to_relative (ngRect* r, const ngRect* rel_rect,
const ngGrid* rel_grid) {
	if (rel_rect != NULL) {
		r->x = r->x - rel_rect->x;
		r->y = r->y - rel_rect->y;
	}
	if (rel_grid != NULL) {
		r->x = (int)(r->x / rel_grid->tile_w);
		r->y = (int)(r->y / rel_grid->tile_h);
		r->w = (int)(r->w / rel_grid->tile_w);
		r->h = (int)(r->h / rel_grid->tile_h);
	}
}

void ng_relative_to_absolute (ngRect* r, const ngRect* rel_rect,
const ngGrid* rel_grid) {
	if (rel_grid != NULL) {
		r->x = (int)(r->x * rel_grid->tile_w);
		r->y = (int)(r->y * rel_grid->tile_h);
		r->w = (int)(r->w * rel_grid->tile_w);
		r->h = (int)(r->h * rel_grid->tile_h);
	}
	if (rel_rect != NULL) {
		r->x = r->x + rel_rect->x;
		r->y = r->y + rel_rect->y;
	}
}

void ng_rect_portal (ngRect* r, const ngRect* src, const ngRect* dest) {
	ng_absolute_to_relative(r, src, NULL);
	// convert relative coord spaces: src to dest
	// r.x' / r.x = dest.w / src.w --> r.x' = (dest.w / src.w) * r.x
	float scale_x = (float)dest->w / src->w;
	float scale_y = (float)dest->h / src->h;
	r->x = (int)(scale_x * r->x);
	r->y = (int)(scale_y * r->y);
	r->w = (int)(scale_x * r->w);
	r->h = (int)(scale_y * r->h);
	ng_relative_to_absolute(r, dest, NULL);
}

void ng_grid_portal (ngGrid* g, const ngRect* src, const ngRect* dest) {
	// convert relative coord spaces: src to dest
	// g.tile_w' / g.tile_w = dest.w / src.w
	// --> g.tile_w' = (dest.w / src.w) * g.tile_w
	float scale_x = (float)dest->w / src->w;
	float scale_y = (float)dest->h / src->h;
	g->tile_w = scale_x * g->tile_w;
	g->tile_h = scale_y * g->tile_h;
}

void ng_color_init (ngColor* color, int r, int g, int b) {
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
}

int ng_image_init (ngGraphics* g, ngImage* image, const char* file,
const ngColor* key) {
	image->texture = NULL;
	ng_rect_init(&image->rect, 0, 0, 0, 0);
	ng_color_init(&image->color, 255, 255, 255);
	image->flip = NG_NONE;
	image->angle = 0.0;
	
	SDL_Surface* surface = NULL;
	surface = SDL_LoadBMP(file);
	if (surface == NULL) {
		return NG_ERROR;
	}
	
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 
	key->r, key->g, key->b)) != 0) {
		SDL_FreeSurface(surface);
		return NG_ERROR;
	}
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTextureFromSurface(g->renderer, surface);
	if (texture == NULL) {
		SDL_FreeSurface(surface);
		return NG_ERROR;
	}
	
	image->texture = texture;
	image->rect.w = surface->w;
	image->rect.h = surface->h;
	
	return NG_SUCCESS;
}

void ng_image_quit (ngImage* image) {
	if (image->texture != NULL) {
		SDL_DestroyTexture(image->texture);
		image->texture = NULL;
	}
}

int ng_image_color (ngImage* image, const ngColor* color) {
	if (SDL_SetTextureColorMod(image->texture, color->r, color->g, color->b) != 0) {
		return NG_ERROR;
	}
	image->color.r = color->r;
	image->color.g = color->g;
	image->color.b = color->b;
	return NG_SUCCESS;
}

int ng_image_alpha (ngImage* image, const ngColor* color) {
	if (SDL_SetTextureAlphaMod(image->texture, color->a) != 0) {
		return NG_ERROR;
	}
	image->color.a = color->a;
	return NG_SUCCESS;
}

void ng_image_flip (ngImage* image, int flip) {
	image->flip = flip;
}

void ng_image_angle (ngImage* image, double angle) {
	image->angle = angle;
}

int ng_graphics_init (ngGraphics* g, const char* title, int w, int h) {
	g->window = NULL;
	g->renderer = NULL;
	ng_rect_init(&g->rect, 0, 0, w, h);
	ng_color_init(&g->color, 0, 0, 0);
	
	g->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
	if (g->window == NULL) {
		return NG_ERROR;
	}
	g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
	if (g->renderer == NULL) {
		return NG_ERROR;
	}
	
	return NG_SUCCESS;
}

void ng_graphics_quit (ngGraphics* g) {
	if (g->renderer != NULL) {
		SDL_DestroyRenderer(g->renderer);
		g->renderer = NULL;
	}
	if (g->window != NULL) {
		SDL_DestroyWindow(g->window);
		g->window = NULL;
	}
}

int ng_graphics_color (ngGraphics* g, const ngColor* color) {
	if (SDL_SetRenderDrawColor(g->renderer, color->r, color->g, color->b,
	g->color.a) != 0) {
		return NG_ERROR;
	}
	g->color.r = color->r;
	g->color.g = color->g;
	g->color.b = color->b;
	return NG_SUCCESS;
}

int ng_graphics_alpha (ngGraphics* g, const ngColor* color) {
	int blendmode;
	if (color->a == 255) {
		blendmode = SDL_BLENDMODE_NONE;
	} else {
		blendmode = SDL_BLENDMODE_BLEND;
	}
	if (SDL_SetRenderDrawBlendMode(g->renderer, blendmode) != 0 ||
	SDL_SetRenderDrawColor(g->renderer, g->color.r, g->color.g, g->color.b,
	color->a) != 0) {
		return NG_ERROR;
	}
	g->color.a = color->a;
	return NG_SUCCESS;
}

int ng_graphics_clear (ngGraphics* g) {
	if (SDL_RenderClear(g->renderer) != 0) {
		return NG_ERROR;
	}
	return NG_SUCCESS;
}

void ng_graphics_draw (ngGraphics* g) {
	SDL_RenderPresent(g->renderer);
}

int ng_draw_image (ngGraphics* g, ngImage* image, const ngRect* s,
const ngRect* d) {
	if (image == NULL || image->texture == NULL) {
		return ng_draw_rect(g, d, true);
	}
	SDL_Rect src;
	if (s != NULL) {
		ng_rect_to_sdl(&src, s);
	} else {
		ng_rect_to_sdl(&src, &image->rect);
	}
	SDL_Rect dest;
	if (d != NULL) {
		ng_rect_to_sdl(&dest, d);
	} else {
		ng_rect_to_sdl(&dest, &g->rect);
	}
	if (image->flip == NG_NONE && image->angle == 0.0) {
		if (SDL_RenderCopy(g->renderer, image->texture, &src, &dest) != 0) {
			return NG_ERROR;
		}
	} else {
		int flip;
		switch (image->flip) {
			case NG_FLIP_X: {
				flip = SDL_FLIP_HORIZONTAL;
				break;
			} case NG_FLIP_Y: {
				flip = SDL_FLIP_VERTICAL;
				break;
			} default: {
				flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
			}
		}
		if (SDL_RenderCopyEx(g->renderer, image->texture, &src, &dest,
		image->angle, NULL, flip) != 0) {
			return NG_ERROR;
		}
	}
	return NG_SUCCESS;
}

int ng_draw_rect (ngGraphics* g, const ngRect* r, bool fill) {
	SDL_Rect dest;
	if (r != NULL) {
		ng_rect_to_sdl(&dest, r);
	} else {
		ng_rect_to_sdl(&dest, &g->rect);
	}
	if (fill) {
		if (SDL_RenderFillRect(g->renderer, &dest) != 0) {
			return NG_ERROR;
		}
	} else {
		if (SDL_RenderDrawRect(g->renderer, &dest) != 0) {
			return NG_ERROR;
		}
	}
	return NG_SUCCESS;
}

int ng_draw_line (ngGraphics* g, int x1, int y1, int x2, int y2) {
	if (SDL_RenderDrawLine(g->renderer, x1, y1, x2, y2) != 0) {
		return NG_ERROR;
	}
	return NG_SUCCESS;
}

int ng_draw_point (ngGraphics* g, int x, int y) {
	if (SDL_RenderDrawPoint(g->renderer, x, y) != 0) {
		return NG_ERROR;
	}
	return NG_SUCCESS;
}

/*
void ng_graphics_render_text (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames,
const char* str, int di) {
	ngFrame cframe = *frame;
	int columns = g->images[frame->image].columns;
	int i, c;
	for (int y = 0; y < h_frames; y++) {
		for (int x = 0; x < w_frames; x++) {
			i = x + (y * w_frames);
			c = str[i];
			if (c == '\0') {
				return;
			}
			c += di;
			if (c < 0) {
				c = 0;
			}
			cframe.column = c % columns;
			cframe.row = c / columns;
			cframe.x = frame->x + (x * frame->w);
			cframe.y = frame->y + (y * frame->h);
			ng_graphics_render_frame(g, &cframe);
		}
	}
}

void ng_graphics_render_tile (ngGraphics* g, const ngFrame* frame, int w_frames, int h_frames) {
	int columns = g->images[frame->image].columns;
	int rows = g->images[frame->image].rows;
	if (columns < 3 || rows < 3) {
		return; // spritesheet must be at least 3x3
	}
	ngFrame tframe = *frame;
	for (int y = 0; y < h_frames; y++) {
		for (int x = 0; x < w_frames; x++) {
			if (y == 0) {
				tframe.row = 0;
			} else if (y < h_frames - 1) {
				tframe.row = 1;
			} else {
				tframe.row = 2;
			}
			if (x == 0) {
				tframe.column = 0;
			} else if (x < w_frames - 1) {
				tframe.column = 1;
			} else {
				tframe.column = 2;
			}
			tframe.x = frame->x + (x * frame->w);
			tframe.y = frame->y + (y * frame->h);
			ng_graphics_render_frame(g, &tframe);
		}
	}
}
*/

