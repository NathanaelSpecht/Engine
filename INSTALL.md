# Engine

This can be downloaded or cloned from GitHub:
- [My GitHub](https://github.com/NathanaelSpecht/Engine).
- `git clone https://github.com/NathanaelSpecht/Engine`.

I've tested Engine on Linux and Windows.
It might work on other platforms.

# Dependencies

Many of engie's functions depend on the [SDL2 library](https://libsdl.org).
A version of SDL2 is included in the `sdl2/` folder, but you may want to 
replace it with the most recent version for best compatibility with your 
platform.

Engie's makefile also requires these applications:
- [GCC](https://gcc.gnu.org).
- [GNU Make](https://gnu.org/software/make).

# Compiling

Compile with `make` (or `mingw32-make` in MinGW-w64 on Windows).
Run with `./app` (requires `SDL2.dll` on Windows).

To compile engie with your own projects, your project folder must have the 
following structure:
- `Makefile`
- `main.c`
- `src/` your project's .c and .h files.
- `ng/` engie's .c and .h files.
- `sdl2/` SDL's folders.

Include `ng.h` in your code to use engie's functions and data types.

