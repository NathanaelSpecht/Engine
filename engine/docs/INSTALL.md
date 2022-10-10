# My Game Engine

This can be downloaded or cloned from GitHub:
- [My GitHub](https://github.com/NathanaelSpecht/Engine).
- `git clone https://github.com/NathanaelSpecht/Engine`.

I intend to support my game engine only for Linux and Windows.
It may or may not work on other platforms.

## Dependencies

Some functions in this depend on the [SDL2 library](https://libsdl.org).
A version of SDL2 is included in the `sdl2/` folder, but you may want 
replace it with the most recent version for best compatibility with your 
platform.

The makefile included with my engine requires these applications:
- [GCC](https://gcc.gnu.org).
- [GNU Make](https://gnu.org/software/make).

## Test Your Environment

To test your development environment, use the included `hello.c` test program:

Compile with `make hello`.

Hello will compile if my engine is compatible with your environment.
If you want, you can run with `./hello` to print "hello" to stdout, for that 
sweet sweet catharsis that comes after all the pain of getting a new 
development environment setup correctly.

## Test My Engine

To test this, use the included `test.c` test program:

Compile with `make test` then run with `./test`.

Tests will be conducted on every module in my game engine.
Passing tests will print "pass" to stdout.
Failing tests will print "FAIL" to stdout.

Modules that pass all tests are ready for experimental use.

## Using My Game Engine on Linux and Windows

To use this in your own projects, copy the `Makefile` and 
`engine/` folder into your project folder.
Then compile my engine along with your own code using the included `Makefile`.

Compile with `make` then run with `./app`.

The makefile assumes your project folder has the following structure:
- `Makefile`
- `main.c`
- `src/` your project's .c and .h files.
- `engine/` my game engine's .c and .h files.
- `sdl2/` SDL's `lib/` and `include/` folders.
- `SDL2.dll`

Refer to `docs/API.md` for my game engine's API.


