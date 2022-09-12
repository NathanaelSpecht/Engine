# Trees In Space (TIS) Game Engine

TIS can be downloaded or cloned from GitHub:
- [TIS GitHub](https://github.com/NathanaelSpecht/TreesInSpaceEngine).
- `git clone https://github.com/NathanaelSpecht/TreesInSpaceEngine`.

I intend to support TIS only for Linux and Windows.
It may or may not work on other platforms.

## Dependencies

Some functions in TIS depend on the [SDL2 library](https://libsdl.org).
A version of SDL2 is included with TIS in the `sdl2/` folder, but you may want 
replace it with the most recent version for best compatibility with your 
platform.

The compilation process included with TIS requires these applications:
- [GCC](https://gcc.gnu.org).
- [GNU Make](https://gnu.org/software/make).

## Test Your Environment

To test your development environment, use the included `hello.c` test program:

Compile with `make hello`.

Hello will compile if TIS is compatible with your environment.
If you want, you can run with `./hello` to print "hello" to stdout, for that 
sweet sweet catharsis that comes after all the pain of getting a new 
development environment setup correctly.

## Test TIS

To test TIS, use the included `test.c` test program:

Compile with `make test` then run with `./test`.

Tests will be conducted on every function in TIS.
Passing tests will print "pass" to stdout.
Failing tests will print "FAIL" to stdout.

Functions that pass all tests are ready for use.

## Using TIS on Linux and Windows

To use TIS in your own projects, copy TIS's `Makefile` and 
`tis/` folder into your project folder.
Then compile TIS along with your own code using the included `Makefile`.

Compile with `make` then run with `./app`.

The TIS makefile assumes your project folder has the following structure:
- `Makefile`
- `main.c`
- `src/` your project's .c and .h files.
- `tis/` TIS's .c and .h files.
- `sdl2/` SDL's `lib/` and `include/` folders.
- `SDL2.dll`

Refer to `docs/API.md` for an overview of the functions in TIS.
The API should be up-to-date with `tis/`.

