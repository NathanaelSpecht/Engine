
/*  tis_convert.h  Type conversion API for TIS.
    Copyright (C) 2022  Trees in Space
*/

#ifndef TIS_CONVERT_H
#define TIS_CONVERT_H

#include <stdbool.h>

bool string_is_bool (const char* s);
bool string_is_int (const char* s);
bool string_is_float (const char* s);
bool string_to_bool (const char* s);
int string_to_int (const char* s);
float string_to_float (const char* s);
void bool_to_string (bool b, char** s);
void int_to_string (int i, char** s);
void float_to_string (float f, char** s);
void ascii_to_hex (const char* ascii, char** hex);
void hex_to_ascii (const char* hex, const char* option, char** ascii);

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

