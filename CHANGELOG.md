
# Engine Changelog

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


