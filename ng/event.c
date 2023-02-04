
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

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
	for (; i<NG_KEYTEXT && text[i] != '\0'; i++) {
		k->text[i] = text[i];
	}
	for (; i<NG_KEYTEXT; i++) {
		k->text[i] = '\0';
	}
}


