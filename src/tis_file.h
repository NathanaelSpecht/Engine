
/*  tis_file.h -- interface of the 'TIS' game engine library.
    version 0.1, 2022 August 30
*/

#ifndef TIS_FILE_H
#define TIS_FILE_H

void read_text (const char* file, char** ascii);
void read_data (const char* file, char** hex);
void write_text (const char* ascii, const char* file);
void write_data (const char* hex, const char* file);
void append_text (const char* ascii, const char* file);
void append_data (const char* hex, const char* file);

#endif

