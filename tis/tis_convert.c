
#include "tis_convert.h"
#include "tis_string.h"
#include <stddef.h>
#include <stdlib.h>

bool string_is_bool (const char* s) {
	// bool is: true | false
	return (string_equals(s, "true") || string_equals(s, "false"));
}

bool string_is_int (const char* s) {
	// int is: (-)?(0-9)+ | 0x(0-9a-f)+
	if (s == NULL || s[0] == '\0') {
		return false;
	} else if (s[0] == '0' && s[1] == 'x') { // hexadecimal 
		int i = 2;
		for (; s[i] != '\0'; i++) {
			if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'f')) {
				return false;
			}
		}
		return true;
	} else { // decimal
		int i = 0;
		if (s[i] == '-') {
			i++;
		}
		if (s[i] < '0' || s[i] > '9') {
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
		// decimal part
		char* t = list[0];
		int i = 0;
		if (t[i] == '-') {
			i++;
		}
		if (t[i] < '0' || t[i] > '9') {
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
		} else if (len == 2) { // exponent part
			t = list[1];
			i = 0;
			if (t[i] == '-') {
				i++;
			}
			if (t[i] < '0' || t[i] > '9') {
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
		} else { // too many parts
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
	long long n = 0;
	if (s == NULL || s[0] == '\0') {
		return 0;
	} else if (s[0] == '0' && s[1] == 'x') { // hexadecimal 
		int i = 2;
		for (; s[i] != '\0'; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				n *= 16;
				n += (s[i] - '0') & 0x0f;
			} else if (s[i] >= 'a' && s[i] <= 'f') {
				n *= 16;
				n += ((s[i] - 'a') + 10) & 0x0f;
			} else {
				return 0;
			}
		}
		return (int)n;
	} else { // decimal
		long long sign = 1;
		int i = 0;
		if (s[i] == '-') {
			sign = -1;
			i++;
		}
		for (; s[i] != '\0'; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				n *= 10;
				n += (s[i] - '0') & 0x0f;
			} else {
				return 0;
			}
		}
		n *= sign;
		return (int)n;
	}
}

float string_to_float (const char* s) {
	double n = 0.0;
	if (s == NULL || s[0] == '\0') {
		return 0.0;
	} else {
		char** list = NULL;
		string_split(&list, s, 'e');
		int len = stringlist_length(list);
		// decimal part
		char* t = list[0];
		double e = 1.0;
		double sign = 1.0;
		int i = 0;
		if (t[i] == '-') {
			sign = -1.0;
			i++;
		}
		for (; t[i] != '.'; i++) {
			if (t[i] >= '0' && t[i] <= '9') {
				n *= 10.0;
				n += (double)((t[i] - '0') & 0x0f);
			} else {
				goto fail;
			}
		}
		e = 0.1;
		i++;
		for (; t[i] != '\0'; i++) {
			if (t[i] >= '0' && t[i] <= '9') {
				n += e * (double)((t[i] - '0') & 0x0f);
				e *= 0.1;
			} else {
				goto fail;
			}
		}
		n *= sign;
		if (len == 1) {
			stringlist_delete(&list);
			return (float)n;
		} else if (len == 2) { // exponent part
			t = list[1];
			int k = 0;
			sign = 1.0;
			i = 0;
			if (t[i] == '-') {
				sign = -1.0;
				i++;
			}
			for (; t[i] != '\0'; i++) {
				if (t[i] >= '0' && t[i] <= '9') {
					k *= 10;
					k += (t[i] - '0') & 0x0f;
				} else {
					goto fail;
				}
			}
			stringlist_delete(&list);
			e = 1.0;
			if (k == 0) {
				return n;
			} else if (sign > 0.0) {
				for (i = 0; i < k; i++) {
					e *= 10.0;
				}
			} else {
				for (i = 0; i < k; i++) {
					e *= 0.1;
				}
			}
			n *= e;
			return (float)n;
		} else { // too many parts
			goto fail;
		}
	fail:
		stringlist_delete(&list);
		return 0.0;
	}
}

void bool_to_string (char** s, bool b) {
	if (b) {
		string_copy(s, "true");
	} else {
		string_copy(s, "false");
	}
}

void int_to_string (char** s, int i, const char* mode) {
	int n = i;
	int sign = 1;
	char* c = NULL;
	string_copy(&c, "0");
	char* t = *s;
	string_copy(s, "");
	if (string_equals(mode, "d")) { // decimal
		if (n == 0) {
			string_copy(&t, "0");
			string_delete(&c);
			*s = t;
			return;
		} else if (n < 0) {
			n = -n;
			sign = -1;
		}
		for (; n > 0; n /= 10) {
			c[0] = (char)(n % 10) + '0';
			string_prepend(&t, c);
		}
		if (sign < 0) {
			string_prepend(&t, "-");
		}
		string_delete(&c);
		*s = t;
	} else if (string_equals(mode, "x")) { // hexadecimal
		//todo later
	}
}

void float_to_string (char** s, float f, const char* mode) {
	int n = f;
	if (string_equals(mode, "f")) { // decimal
	
	} else if (string_equals(mode, "e")) { // decimal exponent
	
	}
}

