# Trees in Space game engine API

This is the API provided for your code to interface with TIS.
**TIS is still in early development, so this API is subject to change.**

Behaviors:
- [ ] String functions with better boundary condition checking than the c 
standard library. Is meant to replace the c standard library's `string.h`, 
should not be used alongside it because possible name collisions. Includes 
string-to-type and type-to-string conversion functions, as well as is-type
functions to check if a string-to-type conversion will succeed.
- [ ] File function wrappers around the c standard library's `stdio.h`.
Is meant as quality of life improvement.
- [ ] Network function wrappers around the network sockets. Is meant as quality 
of life improvement.
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

TIS functions return a value if they do not allocate memory. If a function does 
allocate memory, then you must give the address of the pointer to that memory.

# tis_string.h

`int string_length (char* s)`
- [ ] Finds the length of a string `s`, not including the null-terminator. 
Strings with only null chars have a length of 0. Null pointers have a length of 
-1.

`bool string_equals (char* a, char* b)`
- [ ] Checks if two strings are equal.

`void string_copy (char* a, char** s)`
- [ ] Reallocates an existing string `s` and copies another string `a` into it.

`void string_trim (char** s)`
- [ ] Reallocates an existing string `s` and trims all whitespace off both ends.

`void string_append (char* a, char** s)`
- [ ] Reallocates an existing string `s` and appends another string `a` to it.

`void string_prepend (char* a, char** s)`
- [ ] Reallocates an existing string `s` and prepends another string `a` to it.

`void substring (int start, int length, char** s)`
- [ ] Reallocates an existing string `s`, keeping part of it. `start` and 
`length` describe the part to keep.

`int string_find (char* find, int start, char* s)`
- [ ] Finds the index of the first occurrance of a string in another string 
`s`, starting at a given index.

`void string_replace (char* find, char* replace, int start, char** s)`
- [ ] Replaces the first occurrance of a string in another string `s`, starting 
at a given index.

`void string_replace_all (char* find, char* replace, char** s)`
- [ ] Replaces all occurrances of a string in another string `s`.

`void string_split (char* s, char ch, char*** list)`
- [ ] Splits an existing string `s` on a given separator `ch` into a 
reallocated list of strings. Just like strings, the list of strings is 
null-terminated.

`void string_join (char** list, char ch, char** s)`
- [ ] Joins an existing list of strings together with the given separator `ch` 
into one reallocated string `s`. Just like strings, the list of strings should 
be null-terminated.

`bool isbool string_is_bool (char* s)`
- [ ] Checks if an existing string can be evaluated as a bool.

`bool isint string_is_int (char* s)`
- [ ] Checks if an existing string can be evaluated as an int.

`bool isfloat string_is_float (char* s)`
- [ ] Checks if an existing string can be evaluated as a float.

`bool string_to_bool (char* s)`
- [ ] Evaluates an existing string as a bool.

`int string_to_int (char* s)`
- [ ] Evaluates an existing string as an int.

`float string_to_float (char* s)`
- [ ] Evaluates an existing string as a float.

`void bool_to_string (bool b, char** s)`
- [ ] Evaluates a bool as a string.

`void int_to_string (int i, char** s)`
- [ ] Evaluates an int as a string.

`void float_to_string (float f, char** s)`
- [ ] Evaluates a float as a string.

`void ascii_to_hex (char* ascii, char** hex)`
- [ ] Converts a us-ascii string to hexadecimal.

`void hex_to_ascii (char* hex, char* option, char** ascii)`
- [ ] Converts a hexadecimal string to us-ascii. US-ascii strings are 
null-terminated and 7 bits, so you must give an `option` for this function's 
response to offending hexadecimal codes:
	- If "" or null-pointer, then output "".
	- Else if "charX", then output the char X.
	- Else output the `option` string, followed by "XX" where XX is the 
	offending hexadecimal code.

# tis_file.h

`void file_log (char* ascii)`
- [ ] Appends a timestamp to `log` file, followed by us-ascii data.

`void file_read_ascii (char* file, char** ascii)`
- [ ] Opens a file, reads all of its data into a us-ascii string, and closes 
the file.

`void file_read_hex (char* file, char** hex)`
- [ ] Opens a file, reads all of its data into a hexadecimal string, and closes 
the file.

`void file_write_ascii (char* ascii, char* file)`
- [ ] If file does not exist: creates a new file, writes us-ascii data into 
it, and closes the file. If file exists: overwrites the file with us-ascii 
data, and closes the file.

`void file_write_hex (char* hex, char* file)`
- [ ] If file does not exist: creates a new file, writes hexadecimal data into 
it, and closes the file. If file exists: overwrites the file with hexadecimal 
data, and closes the file.

`void file_append_ascii (char* ascii, char* file)`
- [ ] If file does not exist: works the same as `file_write_ascii`. If file 
exists: appends us-ascii data to the end, and closes the file.

`void file_append_hex (char* hex, char* file)`
- [ ] If file does not exist: works the same as `file_write_hex`. If file 
exists: appends hexadecimal data to the end, and closes the file.

# tis_network.h

# tis_state.h

# tis_transform.h

# tis_render.h

# tis_music.h

# tis_world.h


