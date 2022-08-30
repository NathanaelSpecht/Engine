
/*  tis_string.h  String API for TIS.
    Copyright (C) 2022  Trees in Space
*/

#ifndef TIS_STRING_H
#define TIS_STRING_H

#include <stdbool.h>

int string_length (const char* s);
void string_delete (char** s);
bool string_equals (const char* a, const char* b);
void string_copy (const char* a, char** s);
void substring (const char* a, int start, int length, char** s);
void string_trim (char** s);
void string_append_char (char ch, int length, char** s);
void string_append (const char* a, char** s);
void string_prepend (const char* a, char** s);
int string_find (const char* a, int start, const char* s);
void string_replace (const char* a, int start, int length, char** s);
void string_find_replace (const char* a, const char* b, char** s);

int stringlist_length (char** list);
void stringlist_delete (char*** list);
void stringlist_add (const char* s, char*** list);
void string_split (const char* s, char ch, char*** list);
void string_join (char** list, char ch, char** s);

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

