
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
	// float is: (-)?(0-9)+.(0-9)+
	if (s == NULL || s[0] == '\0') {
		return false;
	} else {
		int i = 0;
		if (s[i] == '-') {
			i++;
		}
		if (s[i] < '0' || s[i] > '9') {
			return false;
		}
		i++;
		for (; s[i] != '.'; i++) {
			if (s[i] < '0' || s[i] > '9') {
				return false;
			}
		}
		i++;
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

bool string_to_bool (const char* s) {
	return (string_equals(s, "true"));
}

int string_to_int (const char* s) {
	long long n = 0;
	if (s == NULL || s[0] == '\0') {
		return 0;
	} else {
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
		double e = 1.0;
		double sign = 1.0;
		int i = 0;
		if (s[i] == '-') {
			sign = -1.0;
			i++;
		}
		for (; s[i] != '.'; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				n *= 10.0;
				n += (double)((s[i] - '0') & 0x0f);
			} else {
				return 0.0;
			}
		}
		e = 0.1;
		i++;
		for (; s[i] != '\0'; i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				n += e * (double)((s[i] - '0') & 0x0f);
				e *= 0.1;
			} else {
				return 0.0;
			}
		}
		n *= sign;
		return (float)n;
	}
}

void bool_to_string (char** s, bool b) {
	if (b) {
		string_copy(s, "true");
	} else {
		string_copy(s, "false");
	}
}

void int_to_string (char** s, int i) {
	int n = i;
	int sign = 1;
	char* c = NULL;
	string_copy(&c, "0");
	char* t = *s;
	string_copy(s, "");
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
}

void float_to_string (char** s, float f) {
	int n = f;
}

