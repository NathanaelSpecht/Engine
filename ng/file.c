
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

FILE* ng_fopen (const char* file, const char* mode) {
	// returns NULL on error
	if (file == NULL || mode == NULL || file[0] == '\0' || mode[0] == '\0') {
		return NULL;
	}
	FILE* fp = NULL;
	fp = fopen(file, mode);
	if (fp == NULL) {
		return NULL;
	}
	return fp;
}

char* ng_fgets (char* s, FILE* fp, int buf) {
	// returns chars read before error/EOF
	s = ng_free(s);
	if (fp == NULL || feof(fp) != 0 || ferror(fp) != 0) {
		return s;
	}
	// Buf is the number of chars to read at a time.
	// - Larger buffers allow faster reads, but skip data when an error occurs,
	//   and require ftell and fseek to return to where it left off.
	// - Reading 1 char at a time is slow, but will pick up right where it
	//   left off after errors are dealt with.
	if (buf > 1) {
		char a[buf+1];
		while (fgets(a, buf+1, fp) != NULL) {
			s = ng_strcat(s, a);
			if (feof(fp) != 0) {
				break;
			}
		}
	} else {
		int c;
		while ((c = fgetc(fp)) != EOF) {
			s = ng_strcatc(s, (char)c);
		}
	}
	return s;
}

int ng_fputs (const char* s, FILE* fp) {
	if (fp == NULL || feof(fp) != 0 || ferror(fp) != 0) {
		return NG_ERROR;
	} else if (s == NULL || fputs(s, fp) >= 0) {
		return NG_SUCCESS;
	} else {
		return NG_ERROR;
	}
}

FILE* ng_fclose (FILE* fp) {
	// always returns NULL
	if (fp != NULL) {
		fclose(fp);
	}
	return NULL;
}

int ng_rename (const char* oldfile, const char* newfile) {
	if (oldfile == NULL || newfile == NULL || oldfile[0] == '\0' || newfile[0] == '\0') {
		return NG_ERROR;
	} else if (!ng_exist(oldfile, 'w') || ng_exist(newfile, 'r')) {
		return NG_ERROR;
	} else if (rename(oldfile, newfile) == 0) {
		return NG_SUCCESS;
	} else {
		return NG_ERROR;
	}
}

int ng_delete (const char* file) {
	if (file == NULL || file[0] == '\0') {
		return NG_ERROR;
	} else if (!ng_exist(file, 'w')) {
		return NG_ERROR;
	} else if (remove(file) == 0) {
		return NG_SUCCESS;
	} else {
		return NG_ERROR;
	}
}

bool ng_exist (const char* file, char perm) {
	// file exists and program/user has permission
	// check for 'r'ead/'w'rite/'+'both access
	if (file == NULL || file[0] == '\0') {
		return false;
	} else if (!ng_strchr("rw+", perm)) {
		return false;
	}
	
	FILE* fp = NULL;
	if (perm == 'r') {
		fp = ng_fopen(file, "r");
	} else if (perm == 'w') {
		fp = ng_fopen(file, "wx");
	} else if (perm == '+') {
		fp = ng_fopen(file, "r+");
	} else {
		return false;
	}
	
	if (fp == NULL) {
		return false;
	}
	
	fp = ng_fclose(fp);
	return true;
}

/*
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
*/


