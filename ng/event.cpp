
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void ng::Graphics::window_event (SDL_Event* const e) {
	switch (e->window.event) {
		case SDL_WINDOWEVENT_RESIZED: {
			this->rect.w = e->window.data1;
			this->rect.h = e->window.data2;
			break;
		} case SDL_WINDOWEVENT_SIZE_CHANGED: {
			this->rect.w = e->window.data1;
			this->rect.h = e->window.data2;
			break;
		} case SDL_WINDOWEVENT_MAXIMIZED: {
			SDL_GetWindowSize(this->window, &this->rect.w, &this->rect.h);
			break;
		} case SDL_WINDOWEVENT_RESTORED: {
			SDL_GetWindowSize(this->window, &this->rect.w, &this->rect.h);
			break;
		}
	}
}

void ng::Mouse::init () {
	this->left = ng::Release;
	this->middle = ng::Release;
	this->right = ng::Release;
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->scroll_x = 0;
	this->scroll_y = 0;
}

void ng::Mouse::press (SDL_Event* const e) {
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			this->left = ng::Press;
			break;
		} case SDL_BUTTON_MIDDLE: {
			this->middle = ng::Press;
			break;
		} case SDL_BUTTON_RIGHT: {
			this->right = ng::Press;
			break;
		}
	}
	this->dx = e->button.x - this->x;
	this->dy = e->button.y - this->y;
	this->x = e->button.x;
	this->y = e->button.y;
}

void ng::Mouse::release (SDL_Event* const e) {
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			this->left = ng::Release;
			break;
		} case SDL_BUTTON_MIDDLE: {
			this->middle = ng::Release;
			break;
		} case SDL_BUTTON_RIGHT: {
			this->right = ng::Release;
			break;
		}
	}
	this->dx = e->button.x - this->x;
	this->dy = e->button.y - this->y;
	this->x = e->button.x;
	this->y = e->button.y;
}

void ng::Mouse::move (SDL_Event* const e) {
	this->x = e->motion.x;
	this->y = e->motion.y;
	this->dx = e->motion.xrel;
	this->dy = e->motion.yrel;
}

void ng::Mouse::scroll (SDL_Event* const e) {
	this->scroll_x = e->wheel.x;
	this->scroll_y = e->wheel.y;
	if (e->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
		this->scroll_x = this->scroll_x * -1;
		this->scroll_y = this->scroll_y * -1;
	}
}

void ng::Key::init () {
	this->lshift = ng::Release;
	this->rshift = ng::Release;
	this->lctrl = ng::Release;
	this->rctrl = ng::Release;
	this->lalt = ng::Release;
	this->ralt = ng::Release;
	this->caps = ng::Release;
}

void ng::Key::press (SDL_Event* const e) {
	this->scancode = e->key.keysym.scancode;
	this->keycode = e->key.keysym.sym;
	uint16_t mod = e->key.keysym.mod;
	this->lshift = !!(mod & KMOD_LSHIFT);
	this->rshift = !!(mod & KMOD_RSHIFT);
	this->lctrl = !!(mod & KMOD_LCTRL);
	this->rctrl = !!(mod & KMOD_RCTRL);
	this->lalt = !!(mod & KMOD_LALT);
	this->ralt = !!(mod & KMOD_RALT);
	this->caps = !!(mod & KMOD_CAPS);
}

void ng::Key::release (SDL_Event* const e) {
	this->scancode = e->key.keysym.scancode;
	this->keycode = e->key.keysym.sym;
	uint16_t mod = e->key.keysym.mod;
	this->lshift = !!(mod & KMOD_LSHIFT);
	this->rshift = !!(mod & KMOD_RSHIFT);
	this->lctrl = !!(mod & KMOD_LCTRL);
	this->rctrl = !!(mod & KMOD_RCTRL);
	this->lalt = !!(mod & KMOD_LALT);
	this->ralt = !!(mod & KMOD_RALT);
	this->caps = !!(mod & KMOD_CAPS);
}

void ng::Event::init (Graphics* const g) {
	this->mode = ng::None;
	this->mouse.init();
	this->key.init();
	for (int i=0; i<NG_EVENT_TEXT; i++) {
		this->text[i] = '\0';
	}
	this->g = g;
}

bool ng::Event::next () {
	while (SDL_PollEvent(&this->event)) {
		switch (this->event.type) {
			case SDL_QUIT: {
				this->mode = ng::Quit;
				return true;
			} case SDL_WINDOWEVENT: {
				this->mode = ng::WindowEvent;
				this->g->window_event(&this->event);
				return true;
			} case SDL_MOUSEBUTTONDOWN: {
				this->mode = ng::MousePress;
				this->mouse.press(&this->event);
				return true;
			} case SDL_MOUSEBUTTONUP: {
				this->mode = ng::MouseRelease;
				this->mouse.release(&this->event);
				return true;
			} case SDL_MOUSEMOTION: {
				this->mode = ng::MouseMove;
				this->mouse.move(&this->event);
				return true;
			} case SDL_MOUSEWHEEL: {
				this->mode = ng::MouseScroll;
				this->mouse.scroll(&this->event);
				return true;
			} case SDL_KEYDOWN: {
				this->mode = ng::KeyPress;
				this->key.press(&this->event);
				return true;
			} case SDL_KEYUP: {
				this->mode = ng::KeyRelease;
				this->key.release(&this->event);
				return true;
			} case SDL_TEXTINPUT: {
				this->mode = ng::TextInput;
				this->text_input(&this->event);
				return true;
			} default: {
				this->mode = ng::None;
			}
		}
	}
	return false;
}

void ng::Event::consume () {
	this->mode = ng::None;
}

bool ng::Event::exists () {
	return this->mode != ng::None;
}

void ng::Event::text_input (SDL_Event* const e) {
	char* text = e->text.text;
	int i=0;
	for (; i<NG_EVENT_TEXT-1 && text[i] != '\0'; i++) {
		this->text[i] = text[i];
	}
	for (; i<NG_EVENT_TEXT; i++) {
		this->text[i] = '\0';
	}
}


