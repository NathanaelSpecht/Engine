
/*  tis_string.h -- interface of the 'TIS' game engine library.
    version 0.1, 2022 August 30
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

