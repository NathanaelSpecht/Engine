
/*  tis_string.h  String API for TIS.
    Copyright (C) 2022  Trees in Space
*/

#ifndef TIS_STRING_H
#define TIS_STRING_H

#include <stdbool.h>

int string_length (const char* target);
/* Finds the length of a string, not including the null-terminator. Strings 
   with only null chars have a length of 0. Null pointers have a length of -1.
*/

bool string_equals (const char* a, const char* b);
/* Checks if two strings are equal. */

char* string_copy (const char* target);
/* Allocates a string and copies an existing string into it. */

void string_trim (char** target);
/* Reallocates an existing string and trims all whitespace off both ends. */

void string_assign (const char* assign, char** target);
/* Reallocates an existing string and copies another string into it. */

void string_append (const char* append, char** target);
/* Reallocates an existing string and appends another string to it. */

void string_prepend (const char* prepend, char** target);
/* Reallocates an existing string and prepends another string to it. */

char* substring (int start, int length, const char* target);
/* Allocates a string and copies part of an existing string into it. start 
   and length describe the part to copy.
*/

int string_find (const char* search, int start, const char* target);
/* Finds the index of the first occurrance of a string in another string, 
   starting at a given index.
*/

void string_replace (const char* search, int start, char** target);
/* Replaces the first occurrance of a string in another string, starting at 
   a given index.
*/

void string_replace_all (const char* search, char** target);
/* Replaces all occurrances of a string in another string. */

char** string_split (int count, char separator, const char* target);
/* Splits an existing string on a given separator into a newly-allocated 
   list of strings. You may supply a positive count to tell string_split to 
   return up to that many strings, or a negative count to keep going until the 
   end of target. Just like strings, the list of strings is null-terminated.
*/

char* string_join (const char** list, char separator);
/* Joins an existing list of strings together with the given separator into 
   one newly-allocated string. Just like strings, the list of strings should be 
   null-terminated.
*/

bool string_is_bool (const char* target);
/* Checks if an existing string can be evaluated as a bool. */

bool string_is_int (const char* target);
/* Checks if an existing string can be evaluated as an int. */

bool string_is_float (const char* target);
/* Checks if an existing string can be evaluated as a float. */

bool string_to_bool (const char* target);
/* Evaluates an existing string as a bool. */

int string_to_int (const char* target);
/* Evaluates an existing string as an int. */

float string_to_float (const char* target);
/* Evaluates an existing string as a float. */

char* bool_to_string (bool target);
/* Evaluates a bool as a string. */

char* int_to_string (int target);
/* Evaluates an int as a string. */

char* float_to_string (float target);
/* Evaluates a float as a string. */

char* ascii_to_hex (const char* ascii);
/* Converts a us-ascii string to hexadecimal. */

char* hex_to_ascii (const char* hex, const char* option);
/* Converts a hexadecimal string to us-ascii. US-ascii strings are 
   null-terminated and 7 bits, so you're given an option for this function's 
   response to offending hexadecimal codes:
	- If "" or null-pointer, then output "".
	- Else if "charX", then output the char X.
	- Else output the option string, followed by "XX" where XX is the 
	offending hexadecimal code.
*/

#endif

/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Trees in Space  treesinspacecompany@gmail.com
*/

