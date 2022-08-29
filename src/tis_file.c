
/*  tis_file.c  File API implementation for TIS.
    Copyright (C) 2022  Trees in Space
*/

#include "tis_file.h"
#include <stddef.h>

void file_log (const char* ascii) {
/* Appends a timestamp to log file, followed by us-ascii data. */

}

void file_read_ascii (const char* file, char** ascii) {
/* Opens a file, reads all of its data into a us-ascii string, and closes 
   the file.
*/

}

void file_read_hex (const char* file, char** hex) {
/* Opens a file, reads all of its data into a hexadecimal string, and closes 
   the file.
*/

}

void file_write_ascii (const char* ascii, const char* file) {
/* If file does not exist: creates a new file, writes us-ascii data into 
   it, and closes the file. If file exists: overwrites the file with us-ascii 
   data, and closes the file.
*/

}

void file_write_hex (const char* hex, const char* file) {
/* If file does not exist: creates a new file, writes hexadecimal data into 
   it, and closes the file. If file exists: overwrites the file with hexadecimal 
   data, and closes the file.
*/

}

void file_append_ascii (const char* ascii, const char* file) {
/* If file does not exist: works the same as file_write_ascii. If file 
   exists: appends us-ascii data to the end, and closes the file.
*/

}

void file_append_hex (const char* hex, const char* file) {
/* If file does not exist: works the same as file_write_hex. If file 
   exists: appends hexadecimal data to the end, and closes the file.
*/

}

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
