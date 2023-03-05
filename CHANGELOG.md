
# Engine Changelog

# 2023

## 2023 March

March 05:
- Use namespaces and classes for demo.

March 04:
- Use namespaces and classes for Engie.
- Start using namespaces and classes for demo (work in progress).

March 03:
- Port Engie from C to C++.
- Still works on Windows.
- Change return error codes into thrown exceptions. Most functions return void now.

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


