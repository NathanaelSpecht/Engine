
# Engine Changelog

# 2023

## 2023 April

TODO: Physics system with vertex-meshes and springs. The meshes can rotate.

TODO: Change nggui to use vec and math changes.
Change button to use label.
Remove text, should be std::string.

April 23:
- Change nggui to use vec and math changes.

April 22:
- Change nggraphics to use vec and math changes.
- Change graphics to be consistent with canvas: center is (0,0), and
positive y axis points up.

April 21:
- Affine transforms in ngvec.

April 20:
- Add vec3 and mat3 for 2d affine transforms in ngvec.
- Split rect2 into rect2(x,y,w,h) and box2(x,y,rx,ry).
- Remove line2, should be 2 vec2s (points a and b).
- Remove basis2, should be affine transform (mat3).
- Remove space2, should be affine transform (mat3).
- Remove grid2, should be affine transform (mat3).

April 19:
- Move vec2 and mat2 to ngvec.

April 18:
- Change vec2 and add mat2 in ngmath.h

April 15:
- Change demo to use vec2, rect2, space2, etc.
- Remove unused code in demo.
- Remove unused ngmath classes.

April 14:
- Change graphics, gui, and test to use vec2, rect2, space2, etc.

April 13:
- Changed ngmath from rects and hitboxes to vectors and meshes, part 1.
- Changed ngmath classes (vec, rect, space, etc.) to use linear algebra.
- Math class names also indicate whether 2d or 3d (instead of function names).

April 06:
- Button and label code.

April 05:
- Added constructors and destructors for all classes.
- Removed unused functions.
- Added constructors and destructors for demo.
- Text processing code.

April 03:
- Changed arrays to std::vectors.

April 02:
- Fixed mouse scaling bug.
- Added how-to instructions to README.
- Release version 0.0.3.

April 01:
- Change demo from int to double.

## 2023 March

March 31:
- Change nggui from int to double.
- Change test from int to double.
- Fixed canvas scaling bug.
- The changes from int to double fixed some performance problems.
- Still works on Windows.

March 28:
- Change nggraphics from int to double.
- Collider code for vec, rect, and mass.

March 27:
- Join grid with rect into space, and remove grid.
- Split hitbox into rect and mass, and remove hitbox.
- Move vec, rect, space, and mass to ngmath.
- Remove range, axis, and scale.
- Change ngmath from int to double.
- Remove unused code in ngmath.

March 26:
- Move tileset and text-drawing code to nggui.

March 24:
- Canvas, Hitbox, Scale, Range, and nggui.
- Still works on Windows.

March 21:
- Refactor ngtime.
- Replaced NULL function parameters with overloaded functions
that don't take those parameters.

March 17:
- Tileset and text-drawing code.

March 15:
- Split ng.h into different headers, and rename sections with ng:
ngtime, nggraphics, ngaudio, ngevent.
- Put includes, defines, types, init, and quit in ngcore.
- Combine physics and math into ngmath.
- Audio and channel volume.

March 14:
- Background music and music license.
- Handle events, draw image, and play music in test app.
- Play music in demo.
- Clarify file formats and license/attribution for game data.
- Still works on Windows.

March 12:
- Change audio from 8-bit to float32.

March 10:
- Move C files to archive folder.

March 05:
- Use namespaces and classes for demo.
- Still works on Windows.

March 04:
- Use namespaces and classes for Engie.
- Start using namespaces and classes for demo (work in progress).

March 03:
- Port Engie from C to C++.
- Still works on Windows.
- Change return error codes into thrown exceptions.
Most functions return void now.

March 01:
- Release version 0.0.1.
- Split Fire Days demo into its own repo.

## 2023 February

February 26:
- Simplify README, remove redundant INSTALL.
- Rename src folder to demo, rename firedays to fireday.
- Reorganize sdl folder.
- Move art folder into demo.
- Still works on Windows.

February 24:
- Vector and rect collision.
- Integer angle, sin, cos, sqrt, and distance.
- Circle functions.

February 23:
- First physics functions.

February 22:
- Remove memory functions. See ng.h for reasons.
- String and file functions assume str can't be NULL.
Clear a str with strnul function (set it to nul char '\0').

February 18:
- Quick string functions.
- File functions use quick string functions where possible.

February 17:
- Fix memory and string functions.
- Refactor file functions.
- Code still works on Windows.

February 16:
- Memory and string functions.

February 14:
- Title, file, world, and level screens.
- HUD, pause, and debug menus.
- Simplified event modes.

February 06:
- Refactor Fire Days's game state into core and screen.
- Refactor Fire Days's init into core and screen.
- Shallow copy core and screen into screens when they init.

February 03:
- Refactor frames and views into rects and grids.
Less code for more functionality.
- Refactor image and graphics variables into rects and colors.
- Mouse, keyboard, and game state.

February 01:
- 1 file per screen.

## 2023 January

January 30:
- Remove unused audio files.
- Better install instructions.
- Rect functions.
- Screen code and start of the Fire Days Demo.

January 24:
- Copy engine changes from private game repo to public engine repo.
- Make `LICENSE`, `CHANGELOG.md`, and `INSTALL.md` more obvious.
- Remove redundant `docs/` folder from `ng/`.

January 20:
- Frames and views.

January 16:
- Refactor audio.

January 09:
- Redesign engine to decouple a lot of things from each other.
- Refactor time.
- Refactor graphics.

January 05:
- I think I broke something before leaving for winter break.
- Revert changes back to December 18. Everything works now.

# 2022

## 2022 December

December 18:
- Flip spritesheet for opposite direction

December 17:
- Combine animations, text, and tiles into spritesheet data type
- Less reliance on enums
- Separate logic for rendering and physics/audio
	- independent render fps and physics/audio ups now possible!

December 07:
- Refactor texture loading into its own function

## 2022 November

November 26:
- Audio code

November 21:
- First music
- Remove API.md, made redundant by already having descriptions in ng.h

November 07:
- Move graphics code to graphics.c

November 02:
- First art
- Reorganize header files into single ng.h, to prevent circular dependencies

## 2022 October

October 10:
- Rename project to engine (ng)
- Utility code

## 2022 September

September 14:
- 2D vector and matrix code
- Float conversion code

September 12:
- File code
- Bool and int conversion code
- Rework build system

## 2022 August

August 30:
- Test graphics for text
- String code
- API and install instructions
- SDL Library
- Licensing

August 02:
- Readme
- todo list
- changelog


