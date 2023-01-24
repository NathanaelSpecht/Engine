
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

bool ng_file_exists (const char* file) {
	FILE* f = NULL;
	f = fopen(file, "r");
	if (f == NULL) {
		return false;
	}
	fclose(f);
	return true;
}

void ng_file_delete (const char* file) {
	remove(file);
}

char* ng_file_read (const char* file) {
	FILE* f = NULL;
	f = fopen(file, "r");
	if (f == NULL) {
		return NULL;
	}
	uint64_t n = 0;
	char* s = malloc(1);
	for (int c = 0; (c = fgetc(f)) != EOF; n++) {
		s = realloc(s, n + 2);
		s[n] = (char)c;
	}
	fclose(f);
	s[n] = '\0';
	return s;
}

void ng_file_write (const char* file, const char* s) {
	FILE* f = NULL;
	f = fopen(file, "w");
	if (f == NULL) {
		return;
	}
	for (int i = 0; s[i] != '\0'; i++) {
		if (fputc(s[i], f) == EOF) {
			break;
		}
	}
	fclose(f);
}

void ng_file_append (const char* file, const char* s) {
	FILE* f = NULL;
	f = fopen(file, "a");
	if (f == NULL) {
		return;
	}
	for (int i = 0; s[i] != '\0'; i++) {
		if (fputc(s[i], f) == EOF) {
			break;
		}
	}
	fclose(f);
}

