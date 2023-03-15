
# Engine

**IMPORTANT!**
**THIS PROJECT IS EXPERIMENTAL AND MAY CHANGE AT ANY TIME WITHOUT ANY NOTICE!**
**USE AT YOUR OWN RISK!**

Lovingly referred to as "Engie" (ng).

Engie is meant to act as glue code between programs and whatever libraries
I happen to be using at the time for driver support (audio, graphics, events,
networking, windowing, etc). It is a standard interface between programs
and those libraries, a kind of software engine.

Engie also has:
- integer approximations of some math functions, and
- collision functions for game physics.

# Version

The release version is 0.0.2.
The experimental/dev version is 0.0.3.

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

Engie's API is `ng.h`. The comments are the documentation.

# Licensing

The `LICENSE` file applies to:
- Engie source files in the `ng/` folder,
- Engie documentation: `README.md` and `CHANGELOG.md`.
- Engie demo in the `demo/` folder, `demo.cpp` and `Makefile`.
- Engie tests in the `test/` folder, `test.cpp` and `Makefile`.

Modern versions of Engie are written in C++.
The old C files from Engie version 0.0.1 are in the `archive/` folder.
They have their own license.

SDL2's files and license are in the `sdl/` folder, `README-SDL.txt`, and
`SDL2.dll`.

Demo and test images, music, and data files are in the `game-data/` folder.
They have their own license.

Engie will always be free and open source.

# Thank You For Reading

Nathanael Specht


