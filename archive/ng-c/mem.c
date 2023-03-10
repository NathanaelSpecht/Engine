
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

/*
void* ng_new (size_t n) {
	return malloc(n);
}

void* ng_resize (void* p, size_t n) {
	return realloc(p, n);
}

void* ng_free (void* p) {
	free(p);
	return NULL;
}
*/

/*
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
*/


