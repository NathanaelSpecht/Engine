
/* Copyright (C) 2023 Nathanael Specht */

#ifndef NGCORE_H
#define NGCORE_H

#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <vector>

#include "SDL.h"

#define NG_HERE __func__ << ":" << __LINE__

// Use exceptions instead of returning an error code.
// Throw logic_error when parameters fail checks at the start of a function.
// Throw runtime_error when a problem occurs during function execution.
// For example:
/*
if (SDL_Init(...) != 0) {
	throw std::runtime_error(SDL_GetError());
}
...
catch (const std::exception& ex) {
	std::cout << NG_HERE << ": can't init: " << ex.what();
}
*/

namespace ng {

// Every enum that can be something or nothing, uses ng::None for nothing.
// Enums that can be nothing will start at 1 instead of 0.
enum EnumNone {
	None = 0
};

// ng::Edge represents a fuzzy condition that could be true, false, or both.
// If you only need true and false, you should use bool instead.
// If you need three mutually exclusive states, you should use your own enum instead.
enum EnumTernary {
	False = 0,
	Edge = 1,
	True = 2
};

void init ();
void quit ();

// Forward declarations, to avoid "has not been declared" compilation errors.
// ngmath
class Vec;
class Rect;
class Space;
class Mass;

// nggraphics
class Color;
class Image;
class Graphics;

// nggui
class Text;
class Tileset;
class Button;
class Label;
class Canvas;

// ngaudio
class Clip;
class Sound;
class Channel;
class Audio;

// ngevent
class Mouse;
class Key;
class Event;

// ngtime
class Time;

} // namespace ng

#endif


