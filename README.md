
# Engine

**IMPORTANT!**
**THIS PROJECT IS EXPERIMENTAL AND MAY CHANGE AT ANY TIME WITHOUT ANY NOTICE!**
**USE AT YOUR OWN RISK!**

Engie the Game Engine (ng) sits between your program and SDL2.
It simplifies SDL2's API for audio, graphics, and events.
It also add things like audio channels and nested renderers.

## How To

To use Engie:
1. Call `ng::init()` to initialize SDL2.
2. Call `ng::quit()` to quit SDL2.

To use Engie's audio system:
1. Call `ng::Audio.init()` to create SDL2 audio player.
2. Load WAV files into SDL audio streams with `ng::Clip.init()`.
3. Create an `ng::Channel` for each audio channel.
For example, one channel for music and another for sound effects.
4. Channels handle instances of playing audio clips with `ng::Sound` objects.
Add sounds to each channel's queue with `ng::Channel.play()`.
5. Every tick:
	a. Fill the audio buffer with silence using `ng::Audio.clear()`.
	b. Mix each channel into the audio buffer with `ng::Audio.mix()`.
	c. Play the audio buffer with `ng::Audio.play()`.
6. Call `ng::Clip.quit()` on each clip to free its SDL audio stream.
7. Call `ng::Channel.quit()` on each channel to free its sound queue.
8. Call `ng::Audio.quit()` to destroy SDL2 audio player.

To use Engie's graphics system:
1. Call `ng::Graphics.init()` to create SDL2 window and renderer.
2. Load BMP files into SDL textures with `ng::Image.init()`.
3. Every tick:
	a. Clear the graphics buffer using `ng::Graphics.clear()`.
	b. Draw to the graphics buffer with `ng::Graphics.draw_T()`. (T is type).
	e. Draw the graphics buffer to the screen with `ng::Graphics.draw()`.
4. Call `ng::Image.quit()` on each image to free its SDL texture.
5. Call `ng::Graphics.quit()` to destroy SDL2 window and renderer.

To use Engie's gui system:
1. Init graphics and images as normal.
2. Create an `ng::Canvas` for each space to draw to.
For example, one canvas for the window, then smaller canvases for the
inventory bar, head-up display, and pop-up menus.
(If you're familiar with HTML, a canvas is like a div.)
3. Every tick:
	a. Clear the graphics as normal.
	b. Draw to the window canvas with `ng::Canvas.draw_T()`. (T is type).
	c. Clear a nested canvas using `ng::Canvas.clear()`.
	d. Draw to a nested canvas with `ng::Canvas.draw_T()`.
	e. Draw the graphics as normal.
4. Canvas has no queue, so there is no Canvas.quit().
5. Quit the graphics and images as normal.

To use Engie's event system:
1. Call `ng::Event.init()` to create SDL2 event.
2. Every tick:
	a. Get next event with `ng::Event.next()`.
	b. Process events with switch(`ng::Event.mode`) case `ng::EnumEventMode`.
3. There is no Event.quit().

To use Engie's time system:
1. Call `ng::Time.init()` to create time-keeping variables.
2. Every tick:
	a. Calculate duration of this tick and average tps with `ng::Time.tick()`.
3. There is no Time.quit().

## TLDR

Read the test and demo programs for examples of how to use Engie.

# Version

The current release version is 0.0.3.
The current experimental/dev version is 0.0.4.

More details are in the `CHANGELOG.md`.

# Demo and Test

This project contains a demo for Engie, a physics game about fire.
In the `demo/` folder, and `demo.cpp`.

Tests are in the `test/` folder, and `test.cpp`.

# Build

To use Engie, you must build it along with your project:
- `#include "ng.h"` in code that uses it, and
- include Engie source files and SDL2 library in your build scripts.

# Documentation

The API of a C++ program is its header files. So too with Engie.
`ng.h` includes the following header files:
- `ngcore.h` has forward declarations of all classes and defines.
- `ngmath.h` has math functions and Vec, Rect, Space, Mass.
- `ngaudio.h` has Clip, Sound, Channel, Audio.
- `nggraphics.h` has Color, Image, Graphics.
- `nggui.h` has Tileset, Canvas.
- `ngevent.h` has Mouse, Key, Event.
- `ngtime.h` has Time.

The comments and this readme file are the documentation.

# Licensing

The `LICENSE` file applies to:
- Engie source files in the `ng/` folder,
- Engie documentation: `README.md` and `CHANGELOG.md`.
- Engie demo in the `demo/` folder, `demo.cpp` and `Makefile`.
- Engie tests in the `test/` folder, `test.cpp` and `Makefile`.

Modern versions of Engie are written in C++.
The old C files from Engie version 0.0.1 are in the `archive/` folder.
They are deprecated as-of version 0.0.3, and will be removed in version 0.1.
They have their own license.

SDL2's files and license are in the `sdl/` folder, `README-SDL.txt`, and
`SDL2.dll`.

Images, music, and other data files for the demo and test programs are
in the `game-data/` folder.
They have their own license.

Engie will always be free and open source.

# Thank You For Reading

Nathanael Specht


