# TIS game engine API

This is the API provided for your code to interface with TIS.
**TIS is still in early development, so this API is subject to change.**

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

## tis_string.h

- [x] `int string_length (char* s)`
	- Finds the length of a string `s`, not including the null-terminator. NULL 
strings have length 0.

- [x] `void string_delete (char** s)`
	- Frees `s` and sets it to NULL, if not already NULL.

- [x] `bool string_equals (char* a, char* b)`
	- Checks if two strings are equal.

- [x] `void string_copy (char** s, char* a)`
	- Copies `a` into `s`.

- [x] `void substring (char** s, char* a, int start, int length)`
	- Takes a substring of `a` and stores it in `s`. `start` and `length`
describe the substring.

- [x] `void string_trim (char** s)`
	- Trims all whitespace off both ends of `s`.

- [x] `void string_append_char (char** s, char ch, int length)`
	- Quickly appends char `ch` to `s`. `length` is the length of `s`.

- [x] `void string_append (char** s, char* a)`
	- Appends `a` to `s`.

- [x] `void string_prepend (char** s, char* a)`
	- Prepends `a` to `s`.

- [x] `int string_find (char* a, int start, char* s)`
	- Finds the first index in `s` of a string `a`, starting at `start`.

- [x] `void string_replace (char** s, char* a, int start, int length)`
	- Replaces a region in `s` with `a`. `start` and `length` describe the 
region to replace.

- [x] `void string_find_replace (char** s, char* a, char* b)`
	- Replaces all regions matching `a` in `s` with `b`.

- [x] `bool string_starts_with (char* s, char* a)`
	- Checks if string `s` starts with string `a`.

- [x] `int stringlist_length (char** list)`
	- Finds the number of strings in `list`, not including the null-terminator. 
NULL lists have length 0.

- [x] `void stringlist_delete (char*** list)`
	- Frees `list` and sets it to NULL, if not already NULL.

- [x] `void stringlist_add (char*** list, char* s)`
	- Appends a string `s` to the end of `list`.

- [x] `void string_split (char*** list, char* s, char ch)`
	- Splits `s` on separator `ch` into a list of strings `list`.

- [x] `void string_join (char** s, char** list, char ch)`
	- Joins `list` on `ch` into a string `s`.

## tis_convert.h

- [x] `bool string_is_bool (char* s)`
	- Checks string `s` can be evaluated as bool.

- [x] `bool string_is_int (char* s)`
	- Checks if `s` can be evaluated as int.

- [x] `bool string_is_float (char* s)`
	- Checks if `s` can be evaluated as float.

- [x] `bool string_to_bool (char* s)`
	- Evaluates `s` as bool.

- [x] `int string_to_int (char* s)`
	- Evaluates `s` as int.

- [x] `float string_to_float (char* s)`
	- Evaluates `s` as float.

- [x] `void bool_to_string (char** s bool b)`
	- Evaluates bool `b` as a string, storing it in `s`.

- [x] `void int_to_string (char** s, int i)`
	- Evaluates int `i` as a string `s`.

- [ ] `void float_to_string (char** s, float f)`
	- Evaluates float `f` as a string `s`.

## tis_file.h

- [x] `bool file_exists (char* file)`
	- Checks if `file` exists.

- [x] `void file_delete (char* file)`
	- Deletes `file`.

- [x] `void file_read (char* file, char** ascii)`
	- Opens `file`, reads all of its bytes as `ascii`, skips unrepresentable 
bytes, and closes the file.

- [x] `void file_write (char* file, char* ascii)`
	- Writes `ascii` into `file`. If file does not exist, creates it, otherwise 
overwrites it.

- [x] `void file_append (char* file, char* ascii)`
	- Appends `ascii` to end of `file`. If file does not exist, works the same 
as `file_write`, else appends to end.

## tis_vector.h

## tis_render2d.h

## tis_music.h

## tis_world2d.h


