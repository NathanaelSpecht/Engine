
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

void* ng_new (size_t n) {
	if (n < 1) {
		return NULL;
	}
	void* a = malloc(n);
	if (a == NULL) {
		exit(EXIT_FAILURE);
	}
	return a;
}

void* ng_resize (void* a, size_t n) {
	if (n < 1) {
		return ng_free(a);
	}
	a = realloc(a, n);
	if (a == NULL) {
		exit(EXIT_FAILURE);
	}
	return a;
}

void* ng_free (void* a) {
	if (a != NULL) {
		free(a);
	}
	return NULL;
}

void* ng_debug_new (size_t n, const char* file, int line) {
	if (n < 1) {
		return NULL;
	}
	void* a = malloc(n);
	if (a == NULL) {
		printf("%s:%d: memory error\n", file, line);
		exit(EXIT_FAILURE);
	}
	return a;
}

void* ng_debug_resize (void* a, size_t n, const char* file, int line) {
	if (n < 1) {
		return ng_free(a);
	}
	a = realloc(a, n);
	if (a == NULL) {
		printf("%s:%d: memory error\n", file, line);
		exit(EXIT_FAILURE);
	}
	return a;
}

void* ng_xnew (size_t n) {
	if (n < 1) {
		return NULL;
	}
	return malloc(n);
}

void* ng_xresize (void* a, size_t n) {
	if (n < 1) {
		return ng_free(a);
	}
	return realloc(a, n);
}

void* ng_debugx_new (size_t n, const char* file, int line) {
	if (n < 1) {
		return NULL;
	}
	void* a = malloc(n);
	if (a == NULL) {
		printf("%s:%d: memory error\n", file, line);
	}
	return a;
}

void* ng_debugx_resize (void* a, size_t n, const char* file, int line) {
	if (n < 1) {
		return ng_free(a);
	}
	a = realloc(a, n);
	if (a == NULL) {
		printf("%s:%d: memory error\n", file, line);
	}
	return a;
}


