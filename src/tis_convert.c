
#include "tis_convert.h"
#include "tis_string.h"
#include <stddef.h>
#include <stdlib.h>

bool string_is_bool (const char* s) {
	return (string_equals(s, "true") || string_equals(s, "false"));
}

bool string_is_int (const char* s) {
	return false;
}

bool string_is_float (const char* s) {
	return false;
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

void float_to_string (char** s, float f) {

}

