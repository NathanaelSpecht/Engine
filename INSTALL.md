
# Engine

This can be downloaded or cloned from GitHub:
- [My GitHub](https://github.com/NathanaelSpecht/Engine).
- `git clone https://github.com/NathanaelSpecht/Engine`.

I've tested engie on Windows 10 (via MinGW) and Linux (Ubuntu 22).
It might work on other platforms.

# Dependencies

Runtime Dependencies:
- [SDL2](https://libsdl.org). Put `SDL2.dll` next to the compiled app.

Windows (via MinGW) Compile-time Dependencies:
- [MinGW-w64](https://mingw-w64.org).
- [GNU Make](https://gnu.org/software/make).
- [GCC](https://gcc.gnu.org).
- [SDL2](https://libsdl.org). Included in `sdl/windows/mingw/` folder.

Linux (Ubuntu) Compile-time Dependencies:
- [GNU Make](https://gnu.org/software/make).
- [GCC](https://gcc.gnu.org).
- [SDL2](https://libsdl.org). Included in `sdl/ubuntu/` folder.

# Compiling

Compile with `make` (or `mingw32-make` in MinGW-w64 on Windows).

To compile engie with your own projects, your project folder must have the 
following structure: (or just change the `Makefile` to match your project)
- `Makefile`
- `main.c`
- `src/` your project's .c and .h files.
- `ng/` engie's .c and .h files.
- `sdl/` SDL's folders.

Include `ng.h` in your code.
Refer to Fire Days Demo's code to learn how to use engie.


