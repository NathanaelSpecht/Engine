# TIS Game Engine

TIS is not your typical game engine, and is not a standalone program.
Rather, TIS is a collection of functions you can use to create a game.

Documentation can be found in the `tis/docs/` folder:
- `INSTALL.md`: Installation instructions.
- `API.md`: Descriptions and API for modules and their functions.
- `CHANGELOG.md`: The current version and dates of changes.

Check the git log for a detailed list of changes.

## What Can I Expect From TIS?

I plan to add the following modules to TIS.
Checked items are complete, in the sense that all tests are passing.
"Upcoming modules" will be added. "Future modules" may or may not be added.

Upcoming Modules:
- [x] String functions that are easier to use than the ones in `string.h`. Is 
meant to replace the c standard library's `string.h`, but can be used alongside 
it, because there are no name collisions.
- [ ] Conversion functions for string-to-type and type-to-string conversion, 
and is-type functions to check if a string-to-type conversion will succeed.
- [x] File function wrappers around the c standard library's `stdio.h`.
- [ ] Vector and matrix operations in 2d and 3d.
- [ ] 2D Rendering functions for text and sprite animations.
- [ ] Music function wrappers around SDL's audio functions, and math operations 
needed for music processing.
- [ ] 2D world, scene, object, hitbox, entity, and vehicle modeling. 2D model 
of the game world, disparate from the process used to render it.

Future Modules:
- [ ] Network function wrappers around the network sockets.
- [ ] 3D rendering functions for textured polygon meshes and 3D animations.
- [ ] 3D world, scene, object, hitbox, entity, and vehicle modeling. 3D model 
of the game world, disparate from the process used to render it.

## Licensing

TIS's files and license are in the `tis/` folder.

SDL2's files and license are in the `sdl2/` folder.

Graphics and audio files and licenses are in the `data/` folder.

TIS will always be free and open source.

Nathanael Specht
Trees in Space

