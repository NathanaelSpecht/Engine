
#include "tis_convert.h"
#include "tis_string.h"
#include <stddef.h>
#include <stdlib.h>

bool string_is_bool (const char* s) {
	// bool is: true | false
	return (string_equals(s, "true") || string_equals(s, "false"));
}

bool string_is_int (const char* s) {
	// int is: (-)?(0-9)+
	if (s == NULL || s[0] == '\0') {
		return false;
	} else {
		int i = 0;
		if (s[i] == '-') {
			i++;
			if (s[i] < '0' || s[i] > '9') {
				return false;
			}
		} else if (s[i] < '0' || s[i] > '9') {
			return false;
		}
		i++;
		for (; s[i] != '\0'; i++) {
			if (s[i] < '0' || s[i] > '9') {
				return false;
			}
		}
		return true;
	}
}

bool string_is_float (const char* s) {
	// float is: (-)?(0-9)+.(0-9)+ | (-)?(0-9).(0-9)+(e)(-)?(0-9)+
	// aka: decimal | decimal e exponent
	if (s == NULL || s[0] == '\0') {
		return false;
	} else {
		char** list = NULL;
		string_split(&list, s, 'e');
		int len = stringlist_length(list);
		// decimal part:
		char* t = list[0];
		int i = 0;
		if (t[i] == '-') {
			i++;
			if (t[i] < '0' || t[i] > '9') {
				goto fail;
			}
		} else if (t[i] < '0' || t[i] > '9') {
			goto fail;
		}
		i++;
		for (; t[i] != '.'; i++) {
			if (t[i] < '0' || t[i] > '9') {
				goto fail;
			}
		}
		i++;
		if (t[i] < '0' || t[i] > '9') {
			goto fail;
		}
		i++;
		for (; t[i] != '\0'; i++) {
			if (t[i] < '0' || t[i] > '9') {
				goto fail;
			}
		}
		if (len == 1) {
			stringlist_delete(&list);
			return true;
		} else if (len == 2) { // exponent part:
			t = list[1];
			i = 0;
			if (t[i] == '-') {
				i++;
				if (t[i] < '0' || t[i] > '9') {
					goto fail;
				}
			} else if (t[i] < '0' || t[i] > '9') {
				goto fail;
			}
			i++;
			for (; t[i] != '\0'; i++) {
				if (t[i] < '0' || t[i] > '9') {
					goto fail;
				}
			}
			stringlist_delete(&list);
			return true;
		} else { // too many e
			goto fail;
		}
	fail:
		stringlist_delete(&list);
		return false;
	}
}

bool string_to_bool (const char* s) {
	return (string_equals(s, "true"));
}

int string_to_int (const char* s) {
	return 0;
}

float string_to_float (const char* s) {
	return 0.0;
}

void bool_to_string (char** s, bool b) {
	if (b) {
		string_copy(s, "true");
	} else {
		string_copy(s, "false");
	}
}

void int_to_string (char** s, int i) {

}

void float_to_string (char** s, float f, const char* mode) {

}

