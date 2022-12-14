
/* Copyright (C) 2022 Nathanael Specht */

#ifndef CONVERTX_H
#define CONVERTX_H

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

