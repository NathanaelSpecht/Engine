
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
	if (ch > 0 && ch < 127 && length >= 0) {
		char* t = *s;
		t = realloc(t, length + 2);
		t[length] = ch;
		t[length + 1] = '\0';
		*s = t;
	}
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
	if (a == NULL && s == NULL) {
		if (start == 0) {
			return 0;
		} else {
			return -1;
		}
	} else if (a == NULL || s == NULL) {
		return -1;
	} else if (a[0] == '\0' && s[0] == '\0') {
		if (start == 0) {
			return 0;
		} else {
			return -1;
		}
	} else if (a[0] == '\0' || s[0] == '\0') {
		return -1;
	} else {
		for (int i = start; s[i] != '\0'; i++) {
			if (a[0] == s[i]) {
				for (int j = 0; a[j] != '\0'; j++) {
					if (a[j] != s[i + j]) {
						goto skip_return;
					}
				}
				return i;
				skip_return:
			}
		}
		return -1;
	}
}

void string_replace (const char* a, int start, int length, char** s) {
	char* t = *s;
	if (a == NULL && t == NULL) {
		return;
	} else if (a == NULL && t != NULL) {
		if (start == 0 && length == string_length(t)) {
			string_delete(&t);
			*s = t;
		}
	} else if (a != NULL && t == NULL) {
		if (start == 0 && length == 0) {
			string_copy(a, &t);
			*s = t;
		}
	} else {
		int m = string_length(t);
		if (start >= 0 && (start + length) <= m) {
			int len = string_length(a);
			int n = m + (len - length);
			if (n <= m) {
				int i = start;
				for (int j = 0; j < len; j++) {
					t[i] = a[j];
					i++;
				}
				for (int j = start + length; j < m; j++) {
					t[i] = t[j];
					i++;
				}
				t[i] = '\0';
				t = realloc(t, n + 1);
			} else {
				t = realloc(t, n + 1);
				t[n] = '\0';
				int i = n - 1;
				for (int j = m - 1; j >= start + length; j--) {
					t[i] = t[j];
					i--;
				}
				for (int j = len - 1; j >= 0; j--) {
					t[i] = a[j];
					i--;
				}
			}
			*s = t;
		}
	}
}

void string_find_replace (const char* a, const char* b, char** s) {
	char* t = *s;
	if (t == NULL) {
		if (a == NULL) {
			string_copy(b, &t);
			*s = t;
		}
	} else if (t[0] == '\0') {
		if (a != NULL && a[0] == '\0') {
			string_copy(b, &t);
			*s = t;
		}
	} else {
		int length = string_length(a);
		int len = string_length(b);
		for (int i = 0; t[i] != '\0';) {
			i = string_find(a, i, t);
			if (i == -1) {
				break;
			} else {
				string_replace(b, i, length, &t);
				i += len;
			}
		}
		*s = t;
	}
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
	if (ch > 0 && ch < 127 && s != NULL) {
		char** t = *list;
		stringlist_add("", &t);
		int n = 0;
		int m = stringlist_length(t);
		for (int i = 0; s[i] != '\0'; i++) {
			if (s[i] == ch) {
				stringlist_add("", &t);
				n = 0;
				m++;
			} else {
				string_append_char(s[i], n, &(t[m - 1]));
				n++;
			}
		}
		*list = t;
	}
}

void string_join (char** list, char ch, char** s) {
	if (ch > 0 && ch < 127 && list != NULL) {
		int n = string_length(*s);
		for (int i = 0; list[i] != NULL; i++) {
			string_append(list[i], s);
			n += string_length(list[i]);
			if (list[i + 1] != NULL) {
				string_append_char(ch, n, s);
				n++;
			}
		}
	}
}

