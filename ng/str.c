
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

int64_t ng_strlen (const char* s) {
	if (s == NULL) {
		return 0;
	}
	return strlen(s);
}

int ng_strcmp (const char* s, const char* a) {
	if (s == NULL && a == NULL) {
		return 0;
	} else if (s == NULL) {
		return -1;
	} else if (a == NULL) {
		return 1;
	}
	return strcmp(s, a);
}

char* ng_strcpy (char* s, const char* a) {
	int64_t len = ng_strlen(a);
	if (a == NULL) {
		return ng_free(s);
	} else if (s == NULL) {
		s = ng_new(len+1);
	} else {
		s = ng_resize(s, len+1);
	}
	return strcpy(s, a);
}

char* ng_strcat (char* s, const char* a) {
	int64_t len = ng_strlen(a);
	if (a == NULL) {
		return s;
	} else if (s == NULL) {
		s = ng_new(len+1);
	} else {
		len = ng_strlen(s) + len;
		s = ng_resize(s, len+1);	
	}
	return strcat(s, a);
}

char* ng_strcatc (char* s, char c) {
	// calls strcat(s,char[2])
	if (s == NULL) {
		s = ng_new(2);
	} else {
		int64_t len = ng_strlen(s) + 1;
		s = ng_resize(s, len+1);
	}
	char a[2] = {c, '\0'};
	return strcat(s, a);
}

char* ng_strstr (const char* s, const char* a) {
	// TODO
	return NULL;
}

char* ng_strtok (char* s, const char* a) {
	// TODO
	return NULL;
}

double ng_atof (const char* s) {
	if (s == NULL) {
		return 0.0;
	}
	return atof(s);
}

int64_t ng_atoi (const char* s) {
	if (s == NULL) {
		return 0;
	}
	return atoll(s);
}

bool ng_atob (const char* s) {
	if (ng_strcmp(s, "true") == 0) {
		return true;
	} else {
		return false;
	}
}

char* ng_ftoa (char* s, const char* fmt, double d) {
	// TODO calls sprintf(s,fmt,d)
	return NULL;
}

char* ng_itoa (char* s, const char* fmt, int64_t i) {
	// TODO calls sprintf(s,fmt,i)
	return NULL;
}

char* ng_btoa (char* s, bool b) {
	char* a;
	if (b) {
		a = "true";
	} else {
		a = "false";
	}
	return ng_strcpy(s, a);
}


