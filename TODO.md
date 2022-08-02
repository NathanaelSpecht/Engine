# Game Engine

Write in C for easy compatibility with SDL2.
Not trying to re-invent the wheel here.

Put OS-specific code in different win.c and linux.c files, and use one os.h file to ensure they all have the same API. 
Use makefile to pick which .c file to compile for a particular OS. Don't use macros for compilation.

Use compiler flags, test suite, and log files to detect bugs before release.

TODOs. Every game uses these things, so they're implemented by the engine:

- [ ] Render map tiles, objects and vehicles in the map, and gui elements.

- [ ] Play music and sounds.

- [ ] Spaces and colliders. 
Spaces can be bigger or smaller on the inside than on the outside. 
Great for making large maps where space contraints are too much hassle to worry about, and/or for maps with impossible geometry.
Also useful when spaces can move or rotate, such as inside elevators, trains, ships, etc.

- [ ] Network protocols and multiplayer.
- [ ] Keyboard, mouse, and game controllers.
- [ ] Pathfinding.
- [ ] State machines for GUIs, animations, sounds, vehicles, and events.
- [ ] File save and load utilities.
- [ ] Config file, to tell the engine which categories of game logic and game file your game has, and where the files are.

# Game Logic

Write in Lua so developers don't have to recompile the project when making their game. Makes distributing game updates and mods easy.

TODOs. These things are unique to each game, so the game developer must implement them:

# Game Files

TODOs. These are things unique to each server, user, or save file:

