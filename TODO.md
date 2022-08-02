# Game Engine

Write in C for easy compatibility with SDL2.
Not trying to re-invent the wheel here.

Put OS-specific code in different win.c and linux.c files, and use one os.h file to ensure they all have the same API. 
Use makefile to pick which .c file to compile for a particular OS. 
Don't use macros for compilation.

Use compiler flags, test suite, and log files to detect bugs before release.

TODOs. Every game uses these things, so they're implemented by the engine:

- [ ] Developer mode, for creating new maps and objects.
Use the engine as a modeling and development tool.

- [ ] Render map tiles, objects and vehicles in the map, and gui elements.
Vehicles are special objects that contain maps and objects, and may contain other vehicles, so they have special rendering.

- [ ] Play music and sounds.
- [ ] Spaces and colliders. 
Spaces can be bigger or smaller on the inside than on the outside, and may contain other spaces.
Great for making large maps where space contraints are too much hassle to worry about, and/or for maps with impossible geometry.
Also useful when spaces can move or rotate, such as inside vehicles.

- [ ] Network protocols and multiplayer.
- [ ] Translate keybindings to user inputs for use by the game logic, in context.
For example, keyboard key W may mean "walk forward" or "drive vehicle forward" depending on the contexts "standing" or "sitting in driver's seat".

- [ ] Pathfinding.
- [ ] State machines for GUIs, animations, sounds, vehicles, and events.
- [ ] File save and load utilities.
- [ ] Config file, to tell the engine which categories of game logic and game file your game has, and where the files are.

# Game Logic

Write in Lua so developers don't have to recompile the project when making their game. 
Makes distributing game updates and mods easy.

TODOs. These things are unique to each game, so the game developer must implement them:

- [ ] Layout of new maps and objects. User-created custom vehicles also implemented here.
Add functionality to developer mode, and/or spawn in new objects and maps during gameplay.

- [ ] Logic of maps and objects.
- [ ] Servers and users, user authentication, and network security logic.
- [ ] Controls logic. This is what each user input does, not the keybindings for those inputs.
- [ ] NPC logic. This code describes what NPCs do and how they decide to do it.
Will move NPC decision making into state machines before release. Will need one state machine per category of NPC.

- [ ] Layout of GUIs and non-customizable vehicles.
- [ ] Logic of GUIs, vehicles, animations, sounds, and events.
These are the state transitions in the state machines, and the code that runs in each case.

# Game Files

TODOs. These are things unique to each server, user, or save file:

- [ ] Mods.

- [ ] Graphics for animations and GUIs.
- [ ] Music and sounds.
- [ ] Maps, vehicles, and objects.
- [ ] Servers and users.
- [ ] Keyboard, mouse, and game controller keybindings and contexts, and which user inputs they translate to for the game logic.
- [ ] Settings.
