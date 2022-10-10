
/* Copyright (C) 2022 Nathanael Specht */

#include "filex.h"
#include "stringx.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

bool file_access (const char* file) {
	// checks if app should have access to file, based on filepath.
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
		remove(file);
	}
}

void file_read (const char* file, char** ascii) {
	if (file_access(file)) {
		FILE* fp = NULL;
		fp = fopen(file, "r");
		if (fp == NULL) {
			return;
		}
		string_append(ascii, "");
		int ch = 0;
		int n = string_length(*ascii);
		while ((ch = fgetc(fp)) != EOF) {
			if (ch > 0 && ch < 127) {
				string_append_char(ascii, ch, n);
				n++;
			}
		}
		fclose(fp);
	}
}

void file_write (const char* file, const char* ascii) {
	if (file_access(file) && ascii != NULL && ascii[0] != '\0') {
		FILE* fp = NULL;
		fp = fopen(file, "w");
		if (fp == NULL) {
			return;
		}
		for (int i = 0; ascii[i] != '\0'; i++) {
			if (ascii[i] > 0 && ascii[i] < 127) {
				if (fputc(ascii[i], fp) == EOF) {
					break;
				}
			}
		}
		fclose(fp);
	}
}

void file_append (const char* file, const char* ascii) {
	if (file_access(file) && ascii != NULL && ascii[0] != '\0') {
		FILE* fp = NULL;
		fp = fopen(file, "a");
		if (fp == NULL) {
			return;
		}
		for (int i = 0; ascii[i] != '\0'; i++) {
			if (ascii[i] > 0 && ascii[i] < 127) {
				if (fputc(ascii[i], fp) == EOF) {
					break;
				}
			}
		}
		fclose(fp);
	}
}

