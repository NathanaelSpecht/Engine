
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
void bool_to_string (char** s, bool b);
void int_to_string (char** s, int i);
void float_to_string (char** s, float f, int d);

#endif

