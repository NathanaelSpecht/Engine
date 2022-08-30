
#include "tis_string.h"
#include <stddef.h>
#include <stdlib.h>

int string_length (const char* s) {
	if (s == NULL) {
		return 0;
	} else {
		int i = 0;
		for (; s[i] != '\0'; i++) {}
		return i;
	}
}

void string_delete (char** s) {
	char* t = *s;
	if (t != NULL) {
		free(t);
		t = NULL;
		*s = t;
	}
}

bool string_equals (const char* a, const char* b) {
	if (a == b) { // both null, or both point to same memory.
		return true;
	} else if (a == NULL || b == NULL) {
		return false;
	} else {
		int i = 0;
		for (; a[i] != '\0' && b[i] != '\0'; i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		if (a[i] != b[i]) {
			return false;
		} else {
			return true;
		}
	}
}

void string_copy (const char* a, char** s) {
	char* t = *s;
	if (a == t) { // both null, or both point to same memory.
		return;
	} else if (a == NULL && t != NULL) {
		free(t);
		t = NULL;
	} else {
		int n = string_length(a) + 1;
		t = realloc(t, n);
		for (int i = 0; i < n; i++) {
			t[i] = a[i];
		}
	}
	*s = t;
}

void substring (const char* a, int start, int length, char** s) {
	char* t = *s;
	int len = string_length(a);
	if (len > 0 && start >= 0 && start < len && length >= 0 && 
	start + length <= len) {
		if (a == t) { // both point to same memory.
			// substring in-place.
			int j = start;
			for (int i = 0; i < length; i++) {
				t[i] = a[j];
				j++;
			}
			t[length] = '\0';
			t = realloc(t, length + 1);
		} else { // different memories.
			t = realloc(t, length + 1);
			int j = start;
			for (int i = 0; i < length; i++) {
				t[i] = a[j];
				j++;
			}
			t[length] = '\0';
		}
		*s = t;
	}
}

void string_trim (char** s) {
	char* t = *s;
	int len = string_length(t);
	if (len > 0) {
		int i = 0; int j = len - 1;
		for (; i != j && (t[i] <= 32 || t[i] == 127); i++) {}
		for (; j != i && (t[j] <= 32 || t[j] == 127); j--) {}
		int n = (j + 1) - i;
		
		substring(t, i, n, &t);
		*s = t;
	}
}

void string_append_char (char ch, int length, char** s) {

}

void string_append (const char* a, char** s) {
	int len = string_length(a);
	if (len > 0) {
		char* t = *s;
		int n = string_length(t);
		int m = n + len;
		t = realloc(t, m + 1);
		for (int i = n; i < m; i++) {
			t[i] = a[i - n];
		}
		t[m] = '\0';
		*s = t;
	}
}

void string_prepend (const char* a, char** s) {
	int len = string_length(a);
	if (len > 0) {
		char* t = *s;
		int n = string_length(t);
		int m = len + n;
		t = realloc(t, m + 1);
		for (int i = len; i < m; i++) {
			t[i] = t[i - len];
		}
		t[m] = '\0';
		if (a != t) { // different memories.
			for (int i = 0; i < len; i++) {
				t[i] = a[i];
			}
		}
		*s = t;
	}
}

int string_find (const char* a, int start, const char* s) {
	return 0;
}

void string_replace (const char* a, int start, int length, char** s) {

}

void string_find_replace (const char* a, const char* b, char** s) {

}

int stringlist_length (char** list) {
	if (list == NULL) {
		return 0;
	} else {
		int i = 0;
		for (; list[i] != NULL; i++) {}
		return i;
	}
}

void stringlist_delete (char*** list) {
	char** t = *list;
	if (t != NULL) {
		for (int i = 0; t[i] != NULL; i++) {
			free(t[i]);
			t[i] = NULL;
		}
		free(t);
		t = NULL;
		*list = t;
	}
}

void stringlist_add (const char* s, char*** list) {
	if (s != NULL) {
		char** t = *list;
		int len = stringlist_length(t);
		t = realloc(t, sizeof(char*) * (len + 2));
		char* u = NULL;
		string_copy(s, &u);
		t[len] = u;
		t[len + 1] = NULL;
		*list = t;
	}
}

void string_split (const char* s, char ch, char*** list) {

}

void string_join (char** list, char ch, char** s) {

}

