
/* Copyright (C) 2022 Nathanael Specht */

#ifndef FILEX_H
#define FILEX_H

#include <stdbool.h>

bool file_exists (const char* file);
void file_delete (const char* file);
void file_read (const char* file, char** ascii);
void file_write (const char* file, const char* ascii);
void file_append (const char* file, const char* ascii);

#endif

