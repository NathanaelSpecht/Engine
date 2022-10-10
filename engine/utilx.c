
/* Copyright (C) Nathanael Specht */

#include <stdlib.h>
#include "utilx.h"

void* delete (void* ptr) {
	if (ptr != NULL) {
		free(ptr);
	}
	return NULL;
}

void* alloc (void* ptr, int64 n) {
	void* ret;
	if (n <= 0) {
		ret = delete(ptr);
	} else {
		ret = realloc(ptr, n);
		if (ret == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	return ret;
}

void* alloc_ignore_error (void* ptr, int64 n) {
	void* ret;
	if (n <= 0) {
		ret = delete(ptr);
	} else {
		ret = realloc(ptr, n);
	}
	return ret;
}

