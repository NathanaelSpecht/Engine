
// Copyright (C) 2022 - 2023 Nathanael Specht

#include "demo.h"

demo::Menu::Menu () {}

demo::Menu::~Menu () {}

void demo::Menu::set_title (Core* core, const char* yes_text, const char* no_text) {
	this->canvas.set(&core->screen.canvas, 0.0, -1.0, 16.0, 8.0);
	this->header.set(0.0, 9.5, 22.0, 7.0);
	this->yes_button.set(yes_text, 1.0, 0.0, 1.75, 14.0, 2.5);
	this->no_button.set(no_text, 1.0, 0.0, -1.75, 14.0, 2.5);
}

void demo::Menu::set_pause (Core* core, const char* yes_text, const char* no_text) {
	this->canvas.set(&core->screen.canvas, 0.0, -1.0, 16.0, 8.0);
	this->header.set(0.0, 9.5, 22.0, 7.0);
	this->yes_button.set(yes_text, 1.0, 0.0, 1.75, 14.0, 2.5);
	this->no_button.set(no_text, 1.0, 0.0, -1.75, 14.0, 2.5);
}

int demo::Menu::event (Core* core) {
	if (!this->events) {
		return ng::None;
	}
	
	// if key press escape, then toggle pausemenu
	if (core->event.mode == ng::KeyPress) {
		int k = core->event.key.scancode;
		
		if (k == SDL_SCANCODE_ESCAPE) {
			this->draws = !this->draws;
			core->event.consume();
			return ng::None;
		}
	}
	
	// if mouse press yes, then return yes
	// else if mouse press no, then return no
	// else return none
	if (this->draws && core->event.mode == ng::MousePress) {
		ng::Vec2 p;
		p.set(core->event.mouse.x, core->event.mouse.y);
		this->canvas.get_mouse(&p);
		
		if (this->yes_button.contains(&p)) {
			core->event.consume();
			return demo::MenuYes;
		}
		else if (this->no_button.contains(&p)) {
			core->event.consume();
			return demo::MenuNo;
		}
	}
	
	return ng::None;
}

void demo::Menu::draw (Core* core) {
	if (!this->draws) {
		return;
	}
	
	ng::Rect2 canvas_rect;
	this->canvas.get_rect(&canvas_rect);
	this->canvas.graphics->set_color(&core->screen.canvas_fillcolor);
	this->canvas.draw_rect(&canvas_rect, ng::DrawFill);
	this->canvas.graphics->set_color(&core->screen.canvas_framecolor);
	this->canvas.draw_rect(&canvas_rect, ng::DrawFrame);
	
	this->canvas.draw_rect(&this->header, ng::DrawFrame);
	this->canvas.draw_button(&core->font, &this->yes_button);
	this->canvas.draw_button(&core->font, &this->no_button);
}

demo::Screen::Screen () {}

demo::Screen::~Screen () {}

void demo::Screen::reset (Core* core) {
	{
		ng::Space2 space(core->graphics.w*0.5, core->graphics.h*0.5, 16.0, -16.0);
		this->canvas.set(&core->graphics, &space,
			ng::columns(space.i, core->graphics.w),
			ng::columns(space.j, core->graphics.h));
	}
	this->canvas_fillcolor.set(0, 0, 0);
	this->canvas_framecolor.set(255, 255, 255);
	this->mouse.set(0.0, 0.0);
	
	this->title.set_title(core, "Start", "Quit");
	this->pause.set_pause(core, "Resume", "Quit");
}

void demo::Screen::set_mode (int mode) {
	this->mode = mode;
	
	switch (mode) {
		case demo::TitleMode: {
			this->title.events = true;
			this->title.draws = true;
			this->pause.events = false;
			this->pause.draws = false;
			break;
		}
		case demo::LevelMode: {
			this->title.events = false;
			this->title.draws = false;
			this->pause.events = true;
			this->pause.draws = false;
			break;
		}
		default: {}
	}
}

void demo::Screen::event (Core* core) {
	if (core->event.mode == ng::MousePress) {
		this->mouse.set(core->event.mouse.x, core->event.mouse.y);
		this->canvas.get_mouse(&this->mouse);
	}

	int menu_event;
	switch (this->mode) {
		case demo::TitleMode: {
			// title menu
			menu_event = this->title.event(core);
			switch (menu_event) {
				case demo::MenuYes: {
					this->set_mode(demo::LevelMode);
					return;
				}
				case demo::MenuNo: {
					this->set_mode(ng::None);
					return;
				}
				default: {}
			}
			
			// title screen
			// no events
			break;
		}
		case demo::LevelMode: {
			// level pause menu
			menu_event = this->pause.event(core);
			switch (menu_event) {
				case demo::MenuYes: {
					this->set_mode(demo::LevelMode);
					return;
				}
				case demo::MenuNo: {
					this->set_mode(demo::TitleMode);
					return;
				}
				default: {}
			}
			
			// level screen
			// no events
			break;
		}
		default: {}
	}
}

void demo::Screen::draw (Core* core) {
	ng::Rect2 canvas_rect;
	this->canvas.get_rect(&canvas_rect);
	this->canvas.graphics->set_color(&core->screen.canvas_fillcolor);
	this->canvas.draw_rect(&canvas_rect, ng::DrawFill);
	this->canvas.graphics->set_color(&core->screen.canvas_framecolor);
	this->canvas.draw_rect(&canvas_rect, ng::DrawFrame);
	
	switch (this->mode) {
		case demo::TitleMode: {
			// title screen
			// nothing else for now
			
			// title menu
			this->title.draw(core);
			break;
		}
		case demo::LevelMode: {
			// level screen
			// nothing else for now
			
			// level pause menu
			this->pause.draw(core);
			break;
		}
		default: {}
	}
}


