#Game Engine

Write in C for easy compatibility with SDL2.

Don't use macros for compilation. 
Put OS-specific code in different .c files, and include the same .h file to ensure they all have the same API. 
Use makefile to pick which .c file to compile for a particular OS.

Use compiler flags, test suite, and log files to detect bugs before release.

#Game Logic

Write in Lua so developers don't have to recompile the project when making their game. Also makes modding easy.
