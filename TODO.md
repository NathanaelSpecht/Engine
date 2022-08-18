# Game Engine

- [x] Write in C for easy compatibility with SDL2.
Not trying to re-invent the wheel here.

Don't use macros for compilation:

- [ ] Put OS-specific code in different win.c and linux.c files, and use one os.h file to ensure they all have the same API. 
- [x] Use makefile to pick which .c file to compile for a particular OS. 

Detect bugs before release with:

- [x] Compiler flags
- [ ] Test suite
- [ ] Log files

TODOs. Every game uses these things, so they're implemented by the engine:

- [ ] Render map tiles, objects and vehicles in the map, and gui elements.
Vehicles are special objects that contain maps and objects, and may contain other vehicles, so they have special rendering.
- [ ] Play background music and event sounds.
- [ ] Spaces and colliders. 
Spaces can be bigger or smaller on the inside than on the outside, and may contain other spaces.
Great for making large maps where space contraints are too much hassle to worry about, and/or for maps with impossible geometry.
- [ ] Network protocols and multiplayer.
- [ ] Translate keybindings to user inputs for use by the game logic, in context.
For example, keyboard key W may mean "walk forward" or "drive vehicle forward" depending on the contexts "standing" or "sitting in driver's seat".
- [ ] Pathfinding.
- [ ] State machines for GUIs, animations, sounds, vehicles, and events.
- [ ] State machines for each NPC category.
- [ ] File save and load utilities.
- [ ] Config file, to tell the engine which categories of game logic and game file your game has, and where the files are.

# Game Logic

- [x] Write in C so we can use the game engine as a set of functions. 
- [x] Open-source to make modding easy.

TODOs. These things are unique to each game, so the game developer must implement them. 
An example game - used for testing all features - is included with this engine:

- [ ] Developer mode, for creating new maps and objects.
Use the engine as a game design and modeling tool. This part is also multiplayer.
- [ ] Layout of new maps and objects. User-created custom vehicles also implemented here.
Add functionality to developer mode, and/or spawn in new objects and maps during gameplay.
- [ ] Logic of maps and objects.
- [ ] Servers and users, user authentication, and network security logic.
- [ ] Controls logic. This is what each user input does, not the keybindings for those inputs.
- [ ] Logic of NPCs and events. State machines with machine-learning abilities.
- [ ] Logic guidance. Guides NPCs and events around players by adjusting the weights on their state machines.
Great for horror games and/or difficulty that changes dynamically with gameplay.
- [ ] Layout of GUIs and non-customizable vehicles.
- [ ] Logic of GUIs, vehicles, animations, and sounds. Basic state machines.

# Game Files

TODOs. These are things unique to each server, user, or save file. 
Example files - used for testing all features - are included with this engine:

- [ ] Graphics for animations and GUIs.
- [ ] Music and sounds.
- [ ] Maps, vehicles, and objects.
- [ ] Servers and users.
- [ ] Keyboard, mouse, and game controller keybindings and contexts, and which user inputs they translate to for the game logic.
- [ ] Settings.
