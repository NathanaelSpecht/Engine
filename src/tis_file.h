
/*  tis_file.h -- interface of the 'TIS' game engine library.
    version 0.1, 2022 August 30
*/

#ifndef TIS_FILE_H
#define TIS_FILE_H

#include <stdbool.h>

bool file_exists (const char* file);
void file_delete (const char* file);
void file_read (const char* file, char** ascii);
void file_write (const char* ascii, const char* file);
void file_append (const char* ascii, const char* file);

#endif

