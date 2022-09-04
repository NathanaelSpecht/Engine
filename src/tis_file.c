
#include "tis_file.h"
#include "tis_string.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

bool file_access (const char* file) {
	if (file == NULL || string_equals("", file)) {
		return false;
	} else if (string_find("/", 0, file) == 0 || 
	string_find("C:\\", 0, file) == 0) {
		return false; // don't access files outside project folder.
	} else {
		return true;
	}
}

bool file_exists (const char* file) {
	if (file_access(file)) {
		FILE* fp = NULL;
		fp = fopen(file, "r");
		if (fp == NULL) {
			return false;
		} else {
			int i = fclose(fp);
			return true;
		}
	} else {
		return false;
	}
}

void file_delete (const char* file) {
	if (file_access(file)) {
		int i = remove(file);
	}
}

void file_read (const char* file, char** ascii) {
	if (file_access(file)) {
		FILE* fp = NULL;
		fp = fopen(file, "r");
		if (fp == NULL) {
			return;
		}
		string_append("", ascii);
		int ch = 0;
		int n = string_length(*ascii);
		while ((ch = fgetc(fp)) != EOF) {
			if (ch > 0 && ch < 127) {
				string_append_char(ch, n, ascii);
				n++;
			}
		}
		fclose(fp);
	}
}

void file_write (const char* ascii, const char* file) {
	if (file_access(file)) {
		
	}
}

void file_append (const char* ascii, const char* file) {
	if (file_access(file)) {
		
	}
}

