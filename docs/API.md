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

# tis.h

# tis_string.h

`int string_length (char* target)`
- [ ] Finds the length of a string, not including the null-terminator. Strings 
with only null chars have a length of 0. Null pointers have a length of -1.

`bool string_equals (char* a, char* b)`
- [ ] Checks if two strings are equal.

`char* copy string_copy (char* target)`
- [ ] Allocates a string and copies an existing string into it.

`void string_trim (char** target)`
- [ ] Reallocates an existing string and trims all whitespace off both ends.

`void string_assign (char* assign, char** target)`
- [ ] Reallocates an existing string and copies another string into it.

`void string_append (char* append, char** target)`
- [ ] Reallocates an existing string and appends another string to it.

`void string_prepend (char* prepend, char** target)`
- [ ] Reallocates an existing string and prepends another string to it.

`char* sub substring (int start, int length, char* target)`
- [ ] Allocates a string and copies part of an existing string into it. `start` 
and `length` describe the part to copy.

`int first string_find (char* search, int start, char* target)`
- [ ] Finds the index of the first occurrance of a string in another string, 
starting at a given index.

`void string_replace (char* search, int start, char** target)`
- [ ] Replaces the first occurrance of a string in another string, starting at 
a given index.

`void string_replace_all (char* search, char** target)`
- [ ] Replaces all occurrances of a string in another string.

`char** list string_split (int count, char separator, char* target)`
- [ ] Splits an existing string on a given separator into a newly-allocated 
list of strings. You may supply a positive `count` to tell `string_split` to 
return up to that many strings, or a negative `count` to keep going until the 
end of `target`. Just like strings, the list of strings is null-terminated.

`char* join string_join (char** list, char separator)`
- [ ] Joins an existing list of strings together with the given separator into 
one newly-allocated string. Just like strings, the list of strings should be 
null-terminated.

`bool isbool string_is_bool (char* target)`
- [ ] Checks if an existing string can be evaluated as a bool.

`bool isint string_is_int (char* target)`
- [ ] Checks if an existing string can be evaluated as an int.

`bool isfloat string_is_float (char* target)`
- [ ] Checks if an existing string can be evaluated as a float.

`bool eval string_to_bool (char* target)`
- [ ] Evaluates an existing string as a bool.

`int eval string_to_int (char* target)`
- [ ] Evaluates an existing string as an int.

`float eval string_to_float (char* target)`
- [ ] Evaluates an existing string as a float.

`char* eval bool_to_string (bool target)`
- [ ] Evaluates a bool as a string.

`char* eval int_to_string (int target)`
- [ ] Evaluates an int as a string.

`char* eval float_to_string (float target)`
- [ ] Evaluates a float as a string.

`char* hex ascii_to_hex (char* ascii)`
- [ ] Converts a us-ascii string to hexadecimal.

`char* ascii hex_to_ascii (char* hex, char* option)`
- [ ] Converts a hexadecimal string to us-ascii. US-ascii strings are 
null-terminated and 7 bits, so you're given an `option` for this function's 
response to offending hexadecimal codes:
	- If "" or null-pointer, then output "".
	- Else if "charX", then output the char X.
	- Else output the `option` string, followed by "XX" where XX is the 
	offending hexadecimal code.

# tis_file.h

`void file_log (char* data)`
- [ ] Appends a timestamp to `log` file, followed by us-ascii data.

`char* data file_read_ascii (char* file)`
- [ ] Opens a file, reads all of its data into a us-ascii string, and closes 
the file.

`char* data file_read_hex (char* file)`
- [ ] Opens a file, reads all of its data into a hexadecimal string, and closes 
the file.

`void file_write_ascii (char* data, char* file)`
- [ ] If file does not exist: creates a new file, writes us-ascii data into 
it, and closes the file. If file exists: overwrites the file with us-ascii 
data, and closes the file.

`void file_write_hex (char* data, char* file)`
- [ ] If file does not exist: creates a new file, writes hexadecimal data into 
it, and closes the file. If file exists: overwrites the file with hexadecimal 
data, and closes the file.

`void file_append_ascii (char* data, char* file)`
- [ ] If file does not exist: works the same as `file_write_ascii`. If file 
exists: appends us-ascii data to the end, and closes the file.

`void file_append_hex (char* data, char* file)`
- [ ] If file does not exist: works the same as `file_write_hex`. If file 
exists: appends hexadecimal data to the end, and closes the file.

# tis_network.h

# tis_state.h

# tis_transform.h

# tis_render.h

# tis_music.h

# tis_world.h


