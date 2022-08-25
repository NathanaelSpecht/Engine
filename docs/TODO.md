# Game Engine

Don't re-invent the wheel:
- [x] Write in C for easy compatibility with SDL2.
TIS is not meant to be a wrapper for SDL, but is meant to be used alongside it.

Don't use macros for compilation:
- [ ] Put OS-specific code in different linux.c and windows.c files, and use 
one os.h file to ensure they all have the same API. 
- [x] Use makefile to pick which .c file to compile for a particular OS. 

Detect bugs before release with:
- [x] Compiler flags
- [x] Tests
- [ ] Log files

Code:
- [ ] String functions with better boundary condition checking than the c 
standard library. Is meant to replace the c standard library's `string.h`, 
should not be used alongside it because possible name collisions. Includes 
type-to-string and string-to-type conversion functions, as well as is-type
functions to check if a string-to-type conversion will succeed.
- [ ] File function wrappers around the c standard library's `stdio.h`.
Is meant as quality of life improvement.
- [ ] Network function wrappers around the network sockets functions for each
platform. Is meant as quality of life improvement.
- [ ] State machines meant for dialogue, animation, event chains, gui, network 
connections, and ai. Anything with more than two states that needs simple logic 
for switching between them.
- [ ] Text and sprite animation rendering.
- [ ] Music function wrappers around SDL's audio functions. Is meant as quality 
of life improvement.
- [ ] World, scene, object, hitbox, entity, and vehicle modeling. 3D model of 
the game world, disparate from the process used to render it. Compatible with
state machines.
- [ ] Transform functions between 3D and 2D space. Translate, scale, rotate, 
and project.

