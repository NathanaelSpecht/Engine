
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_frame_init (ngFrame* frame, int x, int y, int w, int h) {
	frame->x = x;
	frame->y = y;
	frame->w = w;
	frame->h = h;
	// tile is 1x1 by default, so even when grid is not being used,
	// tile can be used in computations. this simplifies the code.
	frame->columns = w;
	frame->rows = h;
	frame->tile_w = 1.0;
	frame->tile_h = 1.0;
}

void ng_frame_grid (ngFrame* frame, int columns, int rows) {
	// ^ change columns and recompute tile w, keeping w the same
	frame->columns = columns;
	frame->rows = rows;
	frame->tile_w = (float)frame->w / columns;
	frame->tile_h = (float)frame->h / rows;
}

void ng_frame_resize_absolute (ngFrame* frame, int w, int h) {
	frame->w = w;
	frame->h = h;
	frame->tile_w = (float)w / frame->columns;
	frame->tile_h = (float)h / frame->rows;
}

void ng_frame_scale_absolute (ngFrame* frame, int w, int h) {
	// ^ change w and recompute tile w, keeping columns the same
	int dx = (frame->w - w) / 2;
	int dy = (frame->h - h) / 2;
	frame->x = frame->x + dx;
	frame->y = frame->y + dy;
	frame->w = w;
	frame->h = h;
	frame->tile_w = (float)w / frame->columns;
	frame->tile_h = (float)h / frame->rows;
}

void ng_frame_resize_percent (ngFrame* frame, float sw, float sh) {
	float w = frame->w * sw;
	float h = frame->h * sh;
	ng_frame_resize_absolute(frame, (int)w, (int)h);
}

void ng_frame_scale_percent (ngFrame* frame, float sw, float sh) {
	// ^ change w by percent and recompute tile w, keeping columns the same
	float w = frame->w * sw;
	float h = frame->h * sh;
	ng_frame_scale_absolute(frame, (int)w, (int)h);
}

void ng_frame_resize_grid (ngFrame* frame, int columns, int rows) {
	frame->columns = columns;
	frame->rows = rows;
	frame->w = (int)(columns * frame->tile_w);
	frame->h = (int)(rows * frame->tile_h);
}

void ng_frame_scale_grid (ngFrame* frame, int columns, int rows) {
	// ^ change columns and recompute w, keeping tile w the same
	frame->columns = columns;
	frame->rows = rows;
	int w = (int)(columns * frame->tile_w);
	int h = (int)(rows * frame->tile_h);
	int dx = (frame->w - w) / 2;
	int dy = (frame->h - h) / 2;
	frame->x = frame->x + dx;
	frame->y = frame->y + dy;
	frame->w = w;
	frame->h = h;
}

void ng_frame_in (const ngFrame* frame, SDL_Rect* rect) {
	rect->x = (int)((rect->x - frame->x) / frame->tile_w);
	rect->y = (int)((rect->y - frame->y) / frame->tile_h);
	rect->w = (int)(rect->w / frame->tile_w);
	rect->h = (int)(rect->h / frame->tile_h);
}

void ng_frame_out (const ngFrame* frame, SDL_Rect* rect) {
	rect->x = (int)((rect->x * frame->tile_w) + frame->x);
	rect->y = (int)((rect->y * frame->tile_h) + frame->y);
	rect->w = (int)(rect->w * frame->tile_w);
	rect->h = (int)(rect->h * frame->tile_h);
}

void ng_view_init (ngView* view, ngFrame* in, ngFrame* out) {
	view->in = *in;
	view->out = *out;
}

void ng_view_in (const ngView* view, SDL_Rect* rect) {
	ng_frame_in(&(view->out), rect); // out: absolute to relative
	// convert relative coord spaces: out to in
	// in.columns / out.columns = rect.x' / rect.x
	float scale_x = (float)view->in.columns / view->out.columns;
	float scale_y = (float)view->in.rows / view->out.rows;
	rect->x = (int)(scale_x * rect->x);
	rect->y = (int)(scale_y * rect->y);
	rect->w = (int)(scale_x * rect->w);
	rect->h = (int)(scale_x * rect->h);
	ng_frame_out(&(view->in), rect); // in: relative to absolute
}

void ng_view_out (const ngView* view, SDL_Rect* rect) {
	ng_frame_in(&(view->in), rect); // in: absolute to relative
	// convert relative coord spaces: in to out
	// out.columns / in.columns = rect.x' / rect.x
	float scale_x = (float)view->out.columns / view->in.columns;
	float scale_y = (float)view->out.rows / view->in.rows;
	rect->x = (int)(scale_x * rect->x);
	rect->y = (int)(scale_y * rect->y);
	rect->w = (int)(scale_x * rect->w);
	rect->h = (int)(scale_x * rect->h);
	ng_frame_out(&(view->out), rect); // out: relative to absolute
}

int ng_image_init (ngGraphics* g, ngImage* image, const char* file,
int columns, int rows, int key_r, int key_g, int key_b) {
	image->texture = NULL;
	image->w = 0;
	image->h = 0;
	ng_image_grid(image, columns, rows);
	image->r = 255;
	image->g = 255;
	image->b = 255;
	image->a = 255;
	
	SDL_Surface* surface = NULL;
	surface = SDL_LoadBMP(file);
	if (surface == NULL) {
		return NG_ERROR;
	}
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 
	key_r, key_g, key_b)) != 0) {
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
	image->w = surface->w;
	image->h = surface->h;
	
	return NG_SUCCESS;
}

void ng_image_quit (ngImage* image) {
	if (image->texture != NULL) {
		SDL_DestroyTexture(image->texture);
		image->texture = NULL;
		image->w = 0;
		image->h = 0;
		image->grid = false;
		image->r = 0;
		image->g = 0;
		image->b = 0;
		image->a = 0;
	}
}

void ng_image_grid (ngImage* image, int columns, int rows) {
	if (columns == 0 && rows == 0) {
		image->grid = false;
		image->columns = 0;
		image->rows = 0;
		image->tile_w = 0;
		image->tile_h = 0;
		return;
	}
	image->grid = true;
	image->columns = columns;
	image->rows = rows;
	image->tile_w = image->w / columns;
	image->tile_h = image->h / rows;
}

int ng_image_color (ngImage* image, int r, int g, int b) {
	if (SDL_SetTextureColorMod(image->texture, r, g, b) != 0) {
		return NG_ERROR;
	}
	image->r = r;
	image->g = g;
	image->b = b;
	return NG_SUCCESS;
}

int ng_image_alpha (ngImage* image, int a) {
	if (SDL_SetTextureAlphaMod(image->texture, a) != 0) {
		return NG_ERROR;
	}
	image->a = a;
	return NG_SUCCESS;
}

int ng_graphics_init (ngGraphics* g, const char* title, int w, int h) {
	g->window = NULL;
	g->renderer = NULL;
	g->w = w;
	g->h = h;
	g->r = 255;
	g->g = 255;
	g->b = 255;
	g->a = 255;
	
	g->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w, h, 0);
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
	
	g->w = 0;
	g->h = 0;
	g->r = 0;
	g->g = 0;
	g->b = 0;
	g->a = 0;
}

int ng_graphics_color (ngGraphics* g2, int r, int g, int b) {
	if (SDL_SetRenderDrawColor(g2->renderer, r, g, b, g2->a) != 0) {
		return NG_ERROR;
	}
	g2->r = r;
	g2->g = g;
	g2->b = b;
	return NG_SUCCESS;
}

int ng_graphics_alpha (ngGraphics* g, int a) {
	int blendmode;
	if (a == 255) {
		blendmode = SDL_BLENDMODE_NONE;
	} else {
		blendmode = SDL_BLENDMODE_BLEND;
	}
	if (SDL_SetRenderDrawBlendMode(g->renderer, blendmode) != 0 ||
	SDL_SetRenderDrawColor(g->renderer, g->r, g->g, g->b, a) != 0) {
		return NG_ERROR;
	}
	g->a = a;
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

int ng_draw_image (ngGraphics* g, ngImage* image, const SDL_Rect* s,
const SDL_Rect* d, int flip, double angle) {
	if (image == NULL || image->texture == NULL) {
		return ng_draw_rect(g, d, true);
	}
	SDL_Rect src;
	if (s == NULL) {
		src.x = 0;
		src.y = 0;
		src.w = image->w;
		src.h = image->h;
	} else {
		src = *s;
	}
	if (image->grid) {
		src.x = src.x * image->tile_w;
		src.y = src.y * image->tile_h;
		src.w = src.w * image->tile_w;
		src.h = src.h * image->tile_h;
	}
	SDL_Rect dest;
	if (d == NULL) {
		dest.x = 0;
		dest.y = 0;
		dest.w = g->w;
		dest.h = g->h;
	} else {
		dest = *d;
	}
	if (flip == SDL_FLIP_NONE && angle == 0.0) {
		if (SDL_RenderCopy(g->renderer, image->texture, &src, &dest) != 0) {
			return NG_ERROR;
		}
	} else {
		if (SDL_RenderCopyEx(g->renderer, image->texture, &src, &dest,
		angle, NULL, flip) != 0) {
			return NG_ERROR;
		}
	}
	return NG_SUCCESS;
}

int ng_draw_rect (ngGraphics* g, const SDL_Rect* r, bool fill) {
	SDL_Rect dest;
	if (r == NULL) {
		dest.x = 0;
		dest.y = 0;
		dest.w = g->w;
		dest.h = g->h;
	} else {
		dest = *r;
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

