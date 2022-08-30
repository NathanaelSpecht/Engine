# Game Engine

This is my personal TODO list.
See `API.md` for API documentation for the TIS game engine.

Don't re-invent the wheel:
- [x] Write in C for easy compatibility with SDL2.
TIS is not meant to be a wrapper for SDL, but is meant to be used alongside it.

Don't use macros for compilation:
- [ ] Put OS-specific code in different `linux.c` and `windows.c` files, and 
use one `os.h` file to ensure they all have the same API. 
- [x] Use makefile to pick which `.c` file to compile for a particular OS. 

Detect bugs before release with:
- [x] Compiler flags
- [x] Tests
- [ ] Log files

