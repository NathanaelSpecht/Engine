
/* Copyright (C) 2022 Nathanael Specht */

#ifndef STRINGX_H
#define STRINGX_H

#include <stdbool.h>

int string_length (const char* s);
void string_delete (char** s);
bool string_equals (const char* a, const char* b);
void string_copy (char** s, const char* a);
void substring (char** s, const char* a, int start, int length);
void string_trim (char** s);
void string_append_char (char** s, char ch, int length);
void string_append (char** s, const char* a);
void string_prepend (char** s, const char* a);
int string_find (const char* a, int start, const char* s);
void string_replace (char** s, const char* a, int start, int length);
void string_find_replace (char** s, const char* a, const char* b);
bool string_starts_with (const char* s, const char* a);

int stringlist_length (char** list);
void stringlist_delete (char*** list);
void stringlist_add (char*** list, const char* s);
void string_split (char*** list, const char* s, char ch);
void string_join (char** s, char** list, char ch);

#endif

