
/*  tis_convert.h -- interface of the 'TIS' game engine library.
    version 0.1, 2022 August 30
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

