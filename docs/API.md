# TIS game engine API

This is the API provided for your code to interface with TIS.
**TIS is still in early development, so this API is subject to change.**

Behaviors:
- [x] String functions with better boundary condition checking than the c 
standard library. Is meant to replace the c standard library's `string.h`, but 
can be used alongside it, because there are no name collisions.
- [ ] Conversion functions for string-to-type and type-to-string conversion, as 
well as is-type functions to check if a string-to-type conversion will succeed.
- [ ] File function wrappers around the c standard library's `stdio.h`.
Is meant as quality of life improvement.
- [ ] State machines meant for dialogue, animation, event chains, gui, network 
connections, and ai. Anything with more than two states that needs simple logic 
for switching between them.
- [ ] Transform functions for linear algebra. Translate, scale, rotate, and 
project between coordinate spaces.
- [ ] Music function wrappers around SDL's audio functions. Is meant as quality 
of life improvement.
- [ ] 2D Rendering functions for text and sprite animations.
- [ ] 2D world, scene, object, hitbox, entity, and vehicle modeling. 2D model 
of the game world, disparate from the process used to render it.

Future Behaviors:
- [ ] Network function wrappers around the network sockets. Is meant as quality 
of life improvement.
- [ ] 3D rendering functions for textured polygon meshes and 3D animations.
- [ ] 3D world, scene, object, hitbox, entity, and vehicle modeling. 3D model 
of the game world, disparate from the process used to render it.

TIS functions return a value if they do not allocate memory. If a function 
allocates memory, then you must give the address of the pointer to that memory.
Doing so allows functions to realloc pointers passed to them without needing to 
return. For example, `my_string = change_string(my_string)` can instead be 
written as `change_string(&my_string)`. This is more readable and less verbose.

## tis_string.h

- [x] `int string_length (char* s)`
	- Finds the length of a string `s`, not including the null-terminator. NULL 
strings have length 0.

- [x] `void string_delete (char** s)`
	- Frees `s` and sets it to NULL, if not already NULL.

- [x] `bool string_equals (char* a, char* b)`
	- Checks if two strings are equal.

- [x] `void string_copy (char* a, char** s)`
	- Copies `a` into `s`.

- [x] `void substring (char* a, int start, int length, char** s)`
	- Takes a substring of `a` and stores it in `s`. `start` and `length`
describe the substring.

- [x] `void string_trim (char** s)`
	- Trims all whitespace off both ends of `s`.

- [x] `void string_append_char (char ch, int length, char** s)`
	- Quickly appends char `ch` to `s`. `length` is the length of `s`.

- [x] `void string_append (char* a, char** s)`
	- Appends `a` to `s`.

- [x] `void string_prepend (char* a, char** s)`
	- Prepends `a` to `s`.

- [x] `int string_find (char* a, int start, char* s)`
	- Finds the first index in `s` of a string `a`, starting at `start`.

- [x] `void string_replace (char* a, int start, int length, char** s)`
	- Replaces a region in `s` with `a`. `start` and `length` describe the 
region to replace.

- [x] `void string_find_replace (char* a, char* b, char** s)`
	- Replaces all regions matching `a` in `s` with `b`.

- [x] `int stringlist_length (char** list)`
	- Finds the number of strings in `list`, not including the null-terminator. 
NULL lists have length 0.

- [x] `void stringlist_delete (char*** list)`
	- Frees `list` and sets it to NULL, if not already NULL.

- [x] `void stringlist_add (char* s, char*** list)`
	- Appends a string `s` to the end of `list`.

- [x] `void string_split (char* s, char ch, char*** list)`
	- Splits `s` on separator `ch` into a list of strings `list`.

- [x] `void string_join (char** list, char ch, char** s)`
	- Joins `list` on `ch` into a string `s`.

## tis_convert.h

- [ ] `bool string_is_bool (char* s)`
	- Checks string `s` can be evaluated as bool.

- [ ] `bool string_is_int (char* s)`
	- Checks if `s` can be evaluated as int.

- [ ] `bool string_is_float (char* s)`
	- Checks if `s` can be evaluated as float.

- [ ] `bool string_to_bool (char* s)`
	- Evaluates `s` as bool.

- [ ] `int string_to_int (char* s)`
	- Evaluates `s` as int.

- [ ] `float string_to_float (char* s)`
	- Evaluates `s` as float.

- [ ] `void bool_to_string (bool b, char** s)`
	- Evaluates bool `b` as a string, storing it in `s`.

- [ ] `void int_to_string (int i, char** s)`
	- Evaluates int `i` as a string `s`.

- [ ] `void float_to_string (float f, char** s)`
	- Evaluates float `f` as a string `s`.

## tis_file.h

- [x] `bool file_exists (char* file)`
	- Checks if `file` exists.

- [ ] `void file_delete (char* file)`
	- Deletes `file`.

- [x] `void file_read (char* file, char** ascii)`
	- Opens `file`, reads all of its bytes as `ascii`, skips unrepresentable 
bytes, and closes the file.

- [ ] `void file_write (char* ascii, char* file)`
	- Writes `ascii` into `file`. If file does not exist, creates it, otherwise 
overwrites it.

- [ ] `void file_append (char* ascii, char* file)`
	- Appends `ascii` to end of `file`. If file does not exist, works the same 
as `file_write`, else appends to end.

## tis_state.h

## tis_transform.h

## tis_render.h

## tis_music.h

## tis_world.h

## tis_network.h


