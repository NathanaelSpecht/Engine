
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng_event_init (ngEvent* e, ngGraphics* g) {
	e->mode = ng::None;
	ng_mouse_init(&e->mouse);
	ng_key_init(&e->key);
	for (int i=0; i<NG_EVENT_TEXT; i++) {
		e->text[i] = '\0';
	}
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
			} case SDL_MOUSEBUTTONDOWN: {
				e->mode = NG_MOUSE_PRESS;
				ng_mouse_press(&e->mouse, &e->event);
				return true;
			} case SDL_MOUSEBUTTONUP: {
				e->mode = NG_MOUSE_RELEASE;
				ng_mouse_release(&e->mouse, &e->event);
				return true;
			} case SDL_MOUSEMOTION: {
				e->mode = NG_MOUSE_MOVE;
				ng_mouse_move(&e->mouse, &e->event);
				return true;
			} case SDL_MOUSEWHEEL: {
				e->mode = NG_MOUSE_SCROLL;
				ng_mouse_scroll(&e->mouse, &e->event);
				return true;
			} case SDL_KEYDOWN: {
				e->mode = NG_KEY_PRESS;
				ng_key_press(&e->key, &e->event);
				return true;
			} case SDL_KEYUP: {
				e->mode = NG_KEY_RELEASE;
				ng_key_release(&e->key, &e->event);
				return true;
			} case SDL_TEXTINPUT: {
				e->mode = NG_TEXT_INPUT;
				ng_text_input(e, &e->event);
				return true;
			} default: {
				e->mode = ng::None;
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
	m->left = NG_RELEASE;
	m->middle = NG_RELEASE;
	m->right = NG_RELEASE;
	m->x = 0;
	m->y = 0;
	m->dx = 0;
	m->dy = 0;
	m->scroll_x = 0;
	m->scroll_y = 0;
}

void ng_mouse_press (ngMouse* m, SDL_Event* e) {
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			m->left = NG_PRESS;
			break;
		} case SDL_BUTTON_MIDDLE: {
			m->middle = NG_PRESS;
			break;
		} case SDL_BUTTON_RIGHT: {
			m->right = NG_PRESS;
			break;
		}
	}
	m->dx = e->button.x - m->x;
	m->dy = e->button.y - m->y;
	m->x = e->button.x;
	m->y = e->button.y;
}

void ng_mouse_release (ngMouse* m, SDL_Event* e) {
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			m->left = NG_RELEASE;
			break;
		} case SDL_BUTTON_MIDDLE: {
			m->middle = NG_RELEASE;
			break;
		} case SDL_BUTTON_RIGHT: {
			m->right = NG_RELEASE;
			break;
		}
	}
	m->dx = e->button.x - m->x;
	m->dy = e->button.y - m->y;
	m->x = e->button.x;
	m->y = e->button.y;
}

void ng_mouse_move (ngMouse* m, SDL_Event* e) {
	m->x = e->motion.x;
	m->y = e->motion.y;
	m->dx = e->motion.xrel;
	m->dy = e->motion.yrel;
}

void ng_mouse_scroll (ngMouse* m, SDL_Event* e) {
	m->scroll_x = e->wheel.x;
	m->scroll_y = e->wheel.y;
	if (e->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
		m->scroll_x = m->scroll_x * -1;
		m->scroll_y = m->scroll_y * -1;
	}
}

void ng_key_init (ngKey* k) {
	k->lshift = NG_RELEASE;
	k->rshift = NG_RELEASE;
	k->lctrl = NG_RELEASE;
	k->rctrl = NG_RELEASE;
	k->lalt = NG_RELEASE;
	k->ralt = NG_RELEASE;
	k->caps = NG_RELEASE;
}

void ng_key_press (ngKey* k, SDL_Event* e) {
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

void ng_text_input (ngEvent* t, SDL_Event* e) {
	char* text = e->text.text;
	int i=0;
	for (; i<NG_EVENT_TEXT-1 && text[i] != '\0'; i++) {
		t->text[i] = text[i];
	}
	for (; i<NG_EVENT_TEXT; i++) {
		t->text[i] = '\0';
	}
}


