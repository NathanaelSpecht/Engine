
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_event_init (ngEvent* e, ngGraphics* g) {
	e->mode = NG_NONE;
	ng_mouse_init(&e->mouse);
	ng_key_init(&e->key);
	e->g = g;
}

bool ng_event_next (ngEvent* e) {
	while (SDL_PollEvent(&e->event)) {
		switch (e->event.type) {
			case SDL_QUIT: {
				e->mode = NG_QUIT;
				return true;
			} case SDL_WINDOWEVENT: {
				e->mode = NG_WINDOW;
				ng_window_event(e->g, &e->event);
				return true;
			} case SDL_KEYDOWN: {
				e->mode = NG_KEY;
				ng_key_press(&e->key, &e->event);
				return true;
			} case SDL_KEYUP: {
				e->mode = NG_KEY;
				ng_key_release(&e->key, &e->event);
				return true;
			} case SDL_TEXTINPUT: {
				e->mode = NG_KEY;
				ng_text_input(&e->key, &e->event);
				return true;
			} case SDL_MOUSEBUTTONDOWN: {
				e->mode = NG_MOUSE;
				ng_mouse_press(&e->mouse, &e->event);
				return true;
			} case SDL_MOUSEBUTTONUP: {
				e->mode = NG_MOUSE;
				ng_mouse_release(&e->mouse, &e->event);
				return true;
			} case SDL_MOUSEMOTION: {
				e->mode = NG_MOUSE;
				ng_mouse_move(&e->mouse, &e->event);
				return true;
			} case SDL_MOUSEWHEEL: {
				e->mode = NG_MOUSE;
				ng_mouse_scroll(&e->mouse, &e->event);
				return true;
			} default: {
				e->mode = NG_NONE;
			}
		}
	}
	return false;
}

void ng_window_event (ngGraphics* g, SDL_Event* e) {
	switch (e->window.event) {
		case SDL_WINDOWEVENT_RESIZED: {
			g->rect.w = e->window.data1;
			g->rect.h = e->window.data2;
			break;
		} case SDL_WINDOWEVENT_SIZE_CHANGED: {
			g->rect.w = e->window.data1;
			g->rect.h = e->window.data2;
			break;
		} case SDL_WINDOWEVENT_MAXIMIZED: {
			SDL_GetWindowSize(g->window, &g->rect.w, &g->rect.h);
			break;
		} case SDL_WINDOWEVENT_RESTORED: {
			SDL_GetWindowSize(g->window, &g->rect.w, &g->rect.h);
			break;
		}
	}
}

void ng_mouse_init (ngMouse* m) {
	m->event = NG_NONE;
	m->left = NG_RELEASED;
	m->middle = NG_RELEASED;
	m->right = NG_RELEASED;
	m->x = 0;
	m->y = 0;
	m->dx = 0;
	m->dy = 0;
	m->scroll_x = 0;
	m->scroll_y = 0;
}

void ng_mouse_press (ngMouse* m, SDL_Event* e) {
	m->event = NG_MOUSE_PRESS;
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			m->left = NG_PRESSED;
			break;
		} case SDL_BUTTON_MIDDLE: {
			m->middle = NG_PRESSED;
			break;
		} case SDL_BUTTON_RIGHT: {
			m->right = NG_PRESSED;
			break;
		}
	}
	m->dx = e->button.x - m->x;
	m->dy = e->button.y - m->y;
	m->x = e->button.x;
	m->y = e->button.y;
}

void ng_mouse_release (ngMouse* m, SDL_Event* e) {
	m->event = NG_MOUSE_RELEASE;
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			m->left = NG_RELEASED;
			break;
		} case SDL_BUTTON_MIDDLE: {
			m->middle = NG_RELEASED;
			break;
		} case SDL_BUTTON_RIGHT: {
			m->right = NG_RELEASED;
			break;
		}
	}
	m->dx = e->button.x - m->x;
	m->dy = e->button.y - m->y;
	m->x = e->button.x;
	m->y = e->button.y;
}

void ng_mouse_move (ngMouse* m, SDL_Event* e) {
	m->event = NG_MOUSE_MOVE;
	m->x = e->motion.x;
	m->y = e->motion.y;
	m->dx = e->motion.xrel;
	m->dy = e->motion.yrel;
}

void ng_mouse_scroll (ngMouse* m, SDL_Event* e) {
	m->event = NG_MOUSE_SCROLL;
	m->scroll_x = e->wheel.x;
	m->scroll_y = e->wheel.y;
	if (e->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
		m->scroll_x = m->scroll_x * -1;
		m->scroll_y = m->scroll_y * -1;
	}
}

void ng_key_init (ngKey* k) {
	k->event = NG_NONE;
	k->lshift = NG_RELEASED;
	k->rshift = NG_RELEASED;
	k->lctrl = NG_RELEASED;
	k->rctrl = NG_RELEASED;
	k->lalt = NG_RELEASED;
	k->ralt = NG_RELEASED;
	k->caps = NG_RELEASED;
	for (int i=0; i<NG_KEYTEXT; i++) {
		k->text[i] = '\0';
	}
}

void ng_key_press (ngKey* k, SDL_Event* e) {
	k->event = NG_KEY_PRESS;
	k->scancode = e->key.keysym.scancode;
	k->keycode = e->key.keysym.sym;
	uint16_t mod = e->key.keysym.mod;
	k->lshift = !!(mod & KMOD_LSHIFT);
	k->rshift = !!(mod & KMOD_RSHIFT);
	k->lctrl = !!(mod & KMOD_LCTRL);
	k->rctrl = !!(mod & KMOD_RCTRL);
	k->lalt = !!(mod & KMOD_LALT);
	k->ralt = !!(mod & KMOD_RALT);
	k->caps = !!(mod & KMOD_CAPS);
}

void ng_key_release (ngKey* k, SDL_Event* e) {
	k->event = NG_KEY_RELEASE;
	k->scancode = e->key.keysym.scancode;
	k->keycode = e->key.keysym.sym;
	uint16_t mod = e->key.keysym.mod;
	k->lshift = !!(mod & KMOD_LSHIFT);
	k->rshift = !!(mod & KMOD_RSHIFT);
	k->lctrl = !!(mod & KMOD_LCTRL);
	k->rctrl = !!(mod & KMOD_RCTRL);
	k->lalt = !!(mod & KMOD_LALT);
	k->ralt = !!(mod & KMOD_RALT);
	k->caps = !!(mod & KMOD_CAPS);
}

void ng_text_input (ngKey* k, SDL_Event* e) {
	k->event = NG_TEXT_INPUT;
	char* text = e->text.text;
	int i=0;
	for (; i<NG_KEYTEXT-1 && text[i] != '\0'; i++) {
		k->text[i] = text[i];
	}
	for (; i<NG_KEYTEXT; i++) {
		k->text[i] = '\0';
	}
}


