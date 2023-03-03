
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
- string and file functions that I find myself implementing frequently, and
- integer approximations of some math functions, and
- a particle physics model for games (NOT for science or engineering).

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

`CHANGELOG.md` contains a list of changes - each with a date and description -
that give a little more detail than `git log`.

# Licensing

The `LICENSE` file applies to:
- Engie source files in the `ng/` folder,
- Engie documentation: `README.md` and `CHANGELOG.md`.
- Engie demo in the `demo/` folder, `demo.cpp` and `Makefile`.
- Engie tests in the `test/` folder, `test.cpp` and `Makefile`.

Engie is currently being ported from C to C++.
The old C files from Engie version 0.0.1 are in
the `demo-c/` folder and `demo-c.c`, and in
the `test-c/` folder and `test-c.c`.
The `LICENSE` file also applies to this old code.

SDL2's files and license are in the `sdl/` folder, `README-SDL.txt`, and
`SDL2.dll`.

Engie will always be free and open source.

# Thank You For Reading

Nathanael Specht


