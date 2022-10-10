# My Game Engine

This is a collection of functions I use to create my games.

Documentation can be found in the `engine/docs/` folder:
- `INSTALL.md`: Installation instructions.
- `API.md`: Descriptions and API for modules and their functions.
- `CHANGELOG.md`: The current version and dates of changes.

Check the git log for a detailed list of changes.

## What Can I Expect From This Engine?

I plan to add the following modules to my engine.
Checked items are complete, in the sense that all tests are passing.
"Upcoming modules" will be added. "Future modules" may or may not be added.

Upcoming Modules:
- [x] String functions that are meant to replace the c standard library's 
`string.h`, but can be used alongside it because there are no name collisions.
- [x] Conversion functions for string-to-type and type-to-string conversion, 
and is-type functions to check if a string-to-type conversion will succeed.
- [x] File function wrappers around the c standard library's `stdio.h`.
- [x] 2D Vector and matrix operations.
- [ ] 2D Rendering functions for text and sprite animations.
- [ ] 2D world, scene, object, hitbox, entity, and vehicle modeling. 2D model 
of the game world, disparate from the process used to render it.
- [ ] Music function wrappers around SDL's audio functions, and math operations 
needed for music processing.

Future Modules:
- [ ] Network function wrappers around the network sockets.
- [ ] 3D Vector and matrix operations.
- [ ] 3D rendering functions for textured polygon meshes and 3D animations.
- [ ] 3D world, scene, object, hitbox, entity, and vehicle modeling. 3D model 
of the game world, disparate from the process used to render it.

## Licensing

Game engine files and license are in the `engine/` folder.

SDL2's files and license are in the `sdl2/` folder.

Graphics and audio files and licenses are in the `data/` folder.

My game engine will always be free and open source.

Nathanael Specht


