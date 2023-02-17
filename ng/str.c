
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
	if (a == NULL) {
		return ng_free(s);
	}
	int64_t len = ng_strlen(a);
	s = ng_resize(s, len+1);
	return strcpy(s, a);
}

char* ng_strcat (char* s, const char* a) {
	if (a == NULL) {
		return s;
	}
	int64_t len = ng_strlen(s) + ng_strlen(a);
	s = ng_resize(s, len+1);
	return strcat(s, a);
}

char* ng_strcatc (char* s, char c) {
	// calls strcat(s,char[2])
	int64_t len = ng_strlen(s) + 1;
	s = ng_resize(s, len+1);
	char a[2] = {c, '\0'};
	return strcat(s, a);
}

char* ng_substr (char* s, const char* a, int64_t start, int64_t len) {
	// calls strncpy(s,a+start,len)
	if (a == NULL || start < 0 || len < 0) {
		return ng_free(s);
	}
	s = ng_resize(s, len+1);
	s = strncpy(s, a+start, len);
	s[len] = '\0';
	return s;
}

int64_t ng_strdelim (const char* s, const char* delim, bool is, int64_t start) {
	// first delim/non-delim char from start
	if (s == NULL || delim == NULL || start < 0) {
		return -1;
	}
	int64_t i = start;
	while (s[i] != '\0' && (is ? !ng_strchr(delim, s[i]) : ng_strchr(delim, s[i]))) {
		i++;
	}
	if (s[i] == '\0') {
		return -1;
	}
	return i;
}

bool ng_strchr (const char* s, char c) {
	// returns strchr(s,c)!=NULL
	if (s == NULL) {
		return false;
	}
	return strchr(s, c) != NULL;
}

void ng_strupper (char* s) {
	if (s == NULL) {
		return;
	}
	for (int64_t i=0; s[i] != '\0'; i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			s[i] = s[i] - 32;
		}
	}
}

void ng_strlower (char* s) {
	if (s == NULL) {
		return;
	}
	for (int64_t i=0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] = s[i] + 32;
		}
	}
}

char* ng_atoh (char* s, const char* a) {
	if (a == NULL) {
		return ng_free(s);
	}
	int64_t len = ng_strlen(a);
	int64_t n = len * 2;
	s = ng_resize(s, n+1);
	int k=0;
	char h;
	for (int i=0; i<len; i++) {
		h = (a[i] >> 4) & 0x0f;
		if (h < 10) {
			s[k] = h + '0';
		} else {
			s[k] = (h - 10) + 'a';
		}
		k++;
		
		h = a[i] & 0x0f;
		if (h < 10) {
			s[k] = h + '0';
		} else {
			s[k] = (h - 10) + 'a';
		}
		k++;
	}
	s[n] = '\0';
	return s;
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
	return (int64_t)atoll(s);
}

bool ng_atob (const char* s) {
	if (ng_strcmp(s, "true") == 0) {
		return true;
	} else {
		return false;
	}
}

char* ng_htoa (char* s, const char* a) {
	if (a == NULL) {
		return ng_free(s);
	}
	int64_t len = ng_strlen(a);
	int64_t n = (len+1) / 2;
	char b[n+1];
	int64_t k=0;
	char h;
	for (int64_t i=0; i<len; i+=2) {
		h = a[i];
		if (h >= '0' && h <= '9') {
			h = h - '0';
		} else if (h >= 'A' && h <= 'F') {
			h = (h - 'A') + 10;
		} else if (h >= 'a' && h <= 'a') {
			h = (h - 'a') + 10;
		} else {
			break;
		}
		b[k] = (h << 4) & 0xf0;
		
		h = a[i+1];
		if (h >= '0' && h <= '9') {
			h = h - '0';
		} else if (h >= 'A' && h <= 'F') {
			h = (h - 'A') + 10;
		} else if (h >= 'a' && h <= 'a') {
			h = (h - 'a') + 10;
		} else {
			if (b[k] != '\0') {
				k++;
			}
			break;
		}
		b[k] = b[k] | (h & 0x0f);
		
		if (b[k] == '\0') {
			break;
		}
		k++;
	}
	b[k] = '\0';
	return ng_strcpy(s, b);
}

char* ng_ftoa (char* s, const char* fmt, double d) {
	// calls sprintf(s,fmt,d)
	if (fmt == NULL || fmt[0] == '\0') {
		return ng_free(s);
	}
	// Max buffer length:
	// smallest subnormal double is about 5*10^-324
	// plus 3 chars for "-0." and 1 char for '\0'
	// plus strlen(fmt) for non-format-specifier chars
	// gives 324+4+strlen(fmt) = 328+strlen(fmt)
	int64_t len = 328 + ng_strlen(fmt);
	char a[len];
	int64_t n = sprintf(a, fmt, d);
	if (n < 0) {
		return ng_free(s);
	}
	s = ng_resize(s, n+1);
	s = strncpy(s, a, n);
	s[n] = '\0';
	return s;
}

char* ng_itoa (char* s, const char* fmt, int64_t i) {
	// calls sprintf(s,fmt,i)
	if (fmt == NULL || fmt[0] == '\0') {
		return ng_free(s);
	}
	// Max buffer length:
	// smallest int64_t is -9,223,372,036,854,775,808 or 19 digits
	// plus 1 char for '-' and 1 char for '\0'
	// plus strlen(fmt) for non-format-specifier chars
	// gives 19+2+strlen(fmt) = 21+strlen(fmt)
	int64_t len = 21 + ng_strlen(fmt);
	char a[len];
	int64_t n = sprintf(a, fmt, i);
	if (n < 0) {
		return ng_free(s);
	}
	s = ng_resize(s, n+1);
	s = strncpy(s, a, n);
	s[n] = '\0';
	return s;
}

char* ng_btoa (char* s, bool b) {
	if (b) {
		return ng_strcpy(s, "true");
	} else {
		return ng_strcpy(s, "false");
	}
}


