
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

FILE* ng_fopen (const char* file, const char* mode) {
	// returns NULL on error
	if (file[0] == '\0' || mode[0] == '\0') {
		return NULL;
	}
	return fopen(file, mode);
}

char* ng_fgets (char* s, FILE* fp, int buf) {
	// returns chars read before error/EOF
	s = ng_strnul(s);
	if (fp == NULL || feof(fp) || ferror(fp)) {
		return s;
	}
	// Buf is the number of chars to read at a time.
	// - Larger buffers allow faster reads, but skip data when an error occurs,
	//   and require ftell and fseek to return to where it left off.
	// - Reading 1 char at a time is slow, but will pick up right where it
	//   left off after errors are dealt with.
	int64_t s_len = 0;
	if (buf > 1) {
		char a[buf+1];
		int64_t a_len;
		while (fgets(a, buf+1, fp) != NULL) {
			// fgets stops at EOF or '\n' or buf, so len <= buf.
			// fgets does NOT return len, so it must be re-measured each time.
			a_len = ng_strlen(a);
			s = ng_qstrcat(s, s_len, a, a_len);
			s_len += a_len;
			if (feof(fp) != 0) {
				break;
			}
		}
	} else {
		int c;
		while ((c = fgetc(fp)) != EOF) {
			s = ng_qstrcatc(s, s_len, (char)c);
			s_len+=1;
		}
	}
	return s;
}

int64_t ng_fputs (const char* s, FILE* fp) {
	// returns chars written before error/len
	// writes 1 char at a time, as if by repeated calls to fputc.
	int64_t i=0;
	if (fp == NULL || feof(fp) || ferror(fp)) {
		return i;
	}
	
	for (; s[i] != '\0'; i++) {
		if (fputc((int)s[i], fp) == EOF) {
			break;
		}
	}
	return i;
}

int ng_fputc (char c, FILE* fp) {
	if (fp == NULL || feof(fp) || ferror(fp)) {
		return NG_ERROR;
	} else if (fputc((int)c, fp) != EOF) {
		return NG_SUCCESS;
	} else {
		return NG_ERROR;
	}
}

/*
int ng_fputs (const char* s, FILE* fp) {
	if (fp == NULL || feof(fp) != 0 || ferror(fp) != 0) {
		return NG_ERROR;
	} else if (s == NULL || fputs(s, fp) >= 0) {
		return NG_SUCCESS;
	} else {
		return NG_ERROR;
	}
}
*/

FILE* ng_fclose (FILE* fp) {
	// always returns NULL
	if (fp != NULL) {
		fclose(fp);
	}
	return NULL;
}

int ng_rename (const char* oldfile, const char* newfile) {
	if (oldfile[0] == '\0' || newfile[0] == '\0') {
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
	if (file[0] == '\0') {
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
	if (file[0] == '\0') {
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


