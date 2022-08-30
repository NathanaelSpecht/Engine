# Trees in Space game engine API

This is the API provided for your code to interface with TIS.
**TIS is still in early development, so this API is subject to change.**

Behaviors:
- [ ] String functions with better boundary condition checking than the c 
standard library. Is meant to replace the c standard library's `string.h`, but 
can be used alongside it, because there are no name collisions.
- [ ] Conversion functions for string-to-type and type-to-string conversion, as 
well as is-type functions to check if a string-to-type conversion will succeed.
- [ ] File function wrappers around the c standard library's `stdio.h`.
Is meant as quality of life improvement.
- [ ] State machines meant for dialogue, animation, event chains, gui, network 
connections, and ai. Anything with more than two states that needs simple logic 
for switching between them.
- [ ] Transform functions between 3D and 2D space. Translate, scale, rotate, 
and project.
- [ ] Rendering functions for text and sprite animations.
- [ ] Music function wrappers around SDL's audio functions. Is meant as quality 
of life improvement.
- [ ] World, scene, object, hitbox, entity, and vehicle modeling. 3D model of 
the game world, disparate from the process used to render it. Compatible with
state machines.
- [ ] Network function wrappers around the network sockets. Is meant as quality 
of life improvement.

TIS functions return a value if they do not allocate memory. If a function 
allocates memory, then you must give the address of the pointer to that memory.
Doing so allows functions to realloc pointers passed to them without needing to 
return. For example, `my_string = change_string(my_string)` can instead be 
written as `change_string(&my_string)`. This is more readable and less verbose.

# tis_string.h

`int string_length (char* s)`
- [x] Finds the length of a string `s`, not including the null-terminator. NULL 
strings have length 0.

`void string_delete (char** s)`
- [x] Frees `s` and sets it to NULL, if not already NULL.

`bool string_equals (char* a, char* b)`
- [x] Checks if two strings are equal.

`void string_copy (char* a, char** s)`
- [x] Copies `a` into `s`.

`void substring (char* a, int start, int length, char** s)`
- [x] Takes a substring of `a` and stores it in `s`. `start` and `length`
describe the substring.

`void string_trim (char** s)`
- [x] Trims all whitespace off both ends of `s`.

`void string_append_char (char ch, int length, char** s)`
- [ ] Quickly appends char `ch` to `s`. `length` is the length of `s`.

`void string_append (char* a, char** s)`
- [ ] Appends `a` to `s`.

`void string_prepend (char* a, char** s)`
- [ ] Prepends `a` to `s`.

`int string_find (char* a, int start, char* s)`
- [ ] Finds the first index in `s` of a string `a`, starting at `start`.

`void string_replace (char* a, int start, int length, char** s)`
- [ ] Replaces a region in `s` with `a`. `start` and `length` describe the 
region to replace.

`void string_find_replace (char* a, char* b, char** s)`
- [ ] Replaces all regions matching `a` in `s` with `b`.

`int stringlist_length (char** list)`
- [x] Finds the number of strings in `list`, not including the null-terminator. 
NULL lists have length 0.

`void stringlist_delete (char*** list)`
- [x] Frees `list` and sets it to NULL, if not already NULL.

`void stringlist_add (char* s, char*** list)`
- [x] Appends a string `s` to the end of `list`.

`void string_split (char* s, char ch, char*** list)`
- [ ] Splits `s` on separator `ch` into a list of strings `list`.

`void string_join (char** list, char ch, char** s)`
- [ ] Joins `list` on `ch` into a string `s`.

# tis_convert.h

`bool string_is_bool (char* s)`
- [ ] Checks string `s` can be evaluated as bool.

`bool string_is_int (char* s)`
- [ ] Checks if `s` can be evaluated as int.

`bool string_is_float (char* s)`
- [ ] Checks if `s` can be evaluated as float.

`bool string_to_bool (char* s)`
- [ ] Evaluates `s` as bool.

`int string_to_int (char* s)`
- [ ] Evaluates `s` as int.

`float string_to_float (char* s)`
- [ ] Evaluates `s` as float.

`void bool_to_string (bool b, char** s)`
- [ ] Evaluates bool `b` as a string, storing it in `s`.

`void int_to_string (int i, char** s)`
- [ ] Evaluates int `i` as a string `s`.

`void float_to_string (float f, char** s)`
- [ ] Evaluates float `f` as a string `s`.

`void ascii_to_hex (char* ascii, char** hex)`
- [ ] Converts an `ascii` string to `hex`.

`void hex_to_ascii (char* hex, char* option, char** ascii)`
- [ ] Converts a `hex` string to `ascii`. Ascii cannot contain null or 8-bit 
codes, but hex can, so an `option` string is provided to choose the response to 
unrepresentable codes. Valid options are listed below:
	- "" or NULL -> skip
	- "stringX"    -> replace with string "X"
	- else       -> replace with `option` string, followed by 2-digit hex code

# tis_file.h

`void read_text (char* file, char** ascii)`
- [ ] Opens `file`, reads all of its bytes as `ascii`, skips unrepresentable 
bytes, and closes the file.

`void read_data (char* file, char** hex)`
- [ ] Opens `file`, reads all of its bytes as `hex`, and closes the file.

`void write_text (char* ascii, char* file)`
- [ ] Writes `ascii` into `file`. If file does not exist, creates it, otherwise 
overwrites it.

`void write_data (char* hex, char* file)`
- [ ] Writes `hex` codes as bytes into `file`. If file does not exist, creates 
it, otherwise overwrites it.

`void append_text (char* ascii, char* file)`
- [ ] Appends `ascii` to end of `file`. If file does not exist, works the same 
as `write_text`, else appends to end.

`void append_data (char* hex, char* file)`
- [ ] Appends `hex` codes as bytes to end of `file`. If file does not exist, 
works the same as `write_data`, else appends to end.

# tis_state.h

# tis_transform.h

# tis_render.h

# tis_music.h

# tis_world.h

# tis_network.h


