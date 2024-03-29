
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ngevent.h"

ng::Mouse::Mouse () {
	this->left = false;
	this->middle = false;
	this->right = false;
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->scroll_x = 0;
	this->scroll_y = 0;
}

ng::Mouse::~Mouse () {}

void ng::Mouse::reset () {
	this->left = false;
	this->middle = false;
	this->right = false;
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->scroll_x = 0;
	this->scroll_y = 0;
}

bool ng::Mouse::press (SDL_Event* const e) {
	this->dx = e->button.x - this->x;
	this->dy = e->button.y - this->y;
	this->x = e->button.x;
	this->y = e->button.y;
	
	bool first_press;
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			first_press = !this->left;
			this->left = true;
			break;
		} case SDL_BUTTON_MIDDLE: {
			first_press = !this->middle;
			this->middle = true;
			break;
		} case SDL_BUTTON_RIGHT: {
			first_press = !this->right;
			this->right = true;
			break;
		}
	}
	return first_press;
}

bool ng::Mouse::release (SDL_Event* const e) {
	this->dx = e->button.x - this->x;
	this->dy = e->button.y - this->y;
	this->x = e->button.x;
	this->y = e->button.y;
	
	bool first_release;
	switch (e->button.button) {
		case SDL_BUTTON_LEFT: {
			first_release = this->left;
			this->left = false;
			break;
		} case SDL_BUTTON_MIDDLE: {
			first_release = this->middle;
			this->middle = false;
			break;
		} case SDL_BUTTON_RIGHT: {
			first_release = this->right;
			this->right = false;
			break;
		}
	}
	return first_release;
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

ng::Key::Key () {
	this->scancode = 0;
	this->keycode = 0;
	this->lshift = false;
	this->rshift = false;
	this->lctrl = false;
	this->rctrl = false;
	this->lalt = false;
	this->ralt = false;
	this->caps = false;
}

ng::Key::~Key () {}

void ng::Key::reset () {
	this->scancode = 0;
	this->keycode = 0;
	this->lshift = false;
	this->rshift = false;
	this->lctrl = false;
	this->rctrl = false;
	this->lalt = false;
	this->ralt = false;
	this->caps = false;
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

ng::Event::Event () {
	this->mode = ng::None;
	for (int i=0; i<NG_EVENT_TEXT; i++) {
		this->text[i] = '\0';
	}
	this->graphics = NULL;
}

ng::Event::~Event () {}

void ng::Event::reset (Graphics* const g) {
	this->mode = ng::None;
	this->mouse.reset();
	this->key.reset();
	for (int i=0; i<NG_EVENT_TEXT; i++) {
		this->text[i] = '\0';
	}
	this->graphics = g;
}

bool ng::Event::next () {
	while (SDL_PollEvent(&this->event)) {
		switch (this->event.type) {
			case SDL_QUIT: {
				this->mode = ng::Quit;
				return true;
			} case SDL_MOUSEBUTTONDOWN: {
				// If mouse is held down, and produces many mouse presses,
				// only the first one produces an ng::MousePress event.
				if (this->mouse.press(&this->event)) {
					this->mode = ng::MousePress;
					return true;
				} else {
					this->mode = ng::None;
				}
			} case SDL_MOUSEBUTTONUP: {
				// If the mouse is released, and produces many mouse releases,
				// only the first one produces an ng::MouseRelease event.
				if (this->mouse.release(&this->event)) {
					this->mode = ng::MouseRelease;
					return true;
				} else {
					this->mode = ng::None;
				}
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
			} case SDL_WINDOWEVENT: {
				this->mode = ng::WindowEvent;
				this->window_event(&this->event);
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

void ng::Event::window_event (SDL_Event* const e) {
	switch (e->window.event) {
		case SDL_WINDOWEVENT_RESIZED: {
			this->graphics->w = static_cast<double>(e->window.data1);
			this->graphics->h = static_cast<double>(e->window.data2);
			break;
		} case SDL_WINDOWEVENT_SIZE_CHANGED: {
			this->graphics->w = static_cast<double>(e->window.data1);
			this->graphics->h = static_cast<double>(e->window.data2);
			break;
		} case SDL_WINDOWEVENT_MAXIMIZED: {
			int w, h;
			SDL_GetWindowSize(this->graphics->window, &w, &h);
			this->graphics->w = static_cast<double>(w);
			this->graphics->h = static_cast<double>(h);
			break;
		} case SDL_WINDOWEVENT_RESTORED: {
			int w, h;
			SDL_GetWindowSize(this->graphics->window, &w, &h);
			this->graphics->w = static_cast<double>(w);
			this->graphics->h = static_cast<double>(h);
			break;
		}
	}
}


