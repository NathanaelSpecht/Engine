
/*  tis_string.c  String API implementation for TIS.
    Copyright (C) 2022  Trees in Space
*/

#include "tis_string.h"
#include <stddef.h>

int string_length (const char* s) {
/* Finds the length of a string s, not including the null-terminator. Strings 
   with only null chars have a length of 0. Null pointers have a length of -1.
*/
	return -1;
}

bool string_equals (const char* a, const char* b) {
/* Checks if two strings are equal. */
	return false;
}

void string_copy (const char* a, char** s) {
/* Reallocates an existing string s and copies another string a into it. */

}

void string_trim (char** s) {
/* Reallocates an existing string s and trims all whitespace off both ends. */

}

void string_append (const char* a, char** s) {
/* Reallocates an existing string s and appends another string a to it. */

}

void string_prepend (const char* a, char** s) {
/* Reallocates an existing string s and prepends another string a to it. */

}

void substring (int start, int length, char** s) {
/* Reallocates an existing string s, keeping part of it. start and 
   length describe the part to keep.
*/

}

int string_find (const char* find, int start, const char* s) {
/* Finds the index of the first occurrance of a string in another string s, 
   starting at a given index.
*/
	return 0;
}

void string_replace (const char* find, const char* replace, int start, 
char** s) {
/* Replaces the first occurrance of a string in another string s, starting at 
   a given index.
*/

}

void string_replace_all (const char* find, const char* replace, char** s) {
/* Replaces all occurrances of a string in another string s. */

}

void string_split (const char* s, char ch, char*** list) {
/* Splits an existing string s on a given separator ch into a 
   reallocated list of strings. Just like strings, the list of strings is 
   null-terminated.
*/

}

void string_join (const char** list, char ch, char** s) {
/* Joins an existing list of strings together with the given separator ch 
   into one reallocated string s. Just like strings, the list of strings should 
   be null-terminated.
*/

}

bool string_is_bool (const char* s) {
/* Checks if an existing string can be evaluated as a bool. */
	return false;
}

bool string_is_int (const char* s) {
/* Checks if an existing string can be evaluated as an int. */
	return false;
}

bool string_is_float (const char* s) {
/* Checks if an existing string can be evaluated as a float. */
	return false;
}

bool string_to_bool (const char* s) {
/* Evaluates an existing string as a bool. */
	return false;
}

int string_to_int (const char* s) {
/* Evaluates an existing string as an int. */
	return 0;
}

float string_to_float (const char* s) {
/* Evaluates an existing string as a float. */
	return 0.0;
}

void bool_to_string (bool b, char** s) {
/* Evaluates a bool as a string. */

}

void int_to_string (int i, char** s) {
/* Evaluates an int as a string. */

}

void float_to_string (float f, char** s) {
/* Evaluates a float as a string. */

}

void ascii_to_hex (const char* ascii, char** hex) {
/* Converts a us-ascii string to hexadecimal. */

}

void hex_to_ascii (const char* hex, const char* option, char** ascii) {
/* Converts a hexadecimal string to us-ascii. US-ascii strings are 
   null-terminated and 7 bits, so you must give an option for this function's 
   response to offending hexadecimal codes:
	- If "" or null-pointer, then output "".
	- Else if "charX", then output the char X.
	- Else output the option string, followed by "XX" where XX is the 
	offending hexadecimal code.
*/

}

/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY { without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Trees in Space  treesinspacecompany@gmail.com
*/

