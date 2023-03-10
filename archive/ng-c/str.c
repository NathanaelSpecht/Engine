
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "ng.h"

int64_t ng_strlen (const char* s) {
	return strlen(s);
}

int ng_strcmp (const char* s, const char* a) {
	return strcmp(s, a);
}

char* ng_strnul (char* s) {
	s = realloc(s, 1);
	s[0] = '\0';
	return s;
}

char* ng_strcpy (char* s, const char* a) {
	int64_t len = ng_strlen(a);
	return ng_qstrcpy(s, a, len);
}

char* ng_strcat (char* s, const char* a) {
	int64_t s_len = ng_strlen(s);
	int64_t a_len = ng_strlen(a);
	return ng_qstrcat(s, s_len, a, a_len);
}

char* ng_strcatc (char* s, char c) {
	// calls strcat(s,char[2])
	int64_t s_len = ng_strlen(s);
	return ng_qstrcatc(s, s_len, c);
}

char* ng_substr (char* s, const char* a, int64_t start, int64_t len) {
	// calls strncpy(s,a+start,len)
	int64_t a_len = ng_strlen(a);
	return ng_qsubstr(s, a, a_len, start, len);
}

int64_t ng_strdelim (const char* s, const char* delim, int64_t start) {
	// first delim char from start
	int64_t len = ng_strlen(s);
	return ng_qstrdelim(s, len, delim, start);
}

int64_t ng_strndelim (const char* s, const char* delim, int64_t start) {
	// first non-delim char from start
	int64_t len = ng_strlen(s);
	return ng_qstrndelim(s, len, delim, start);
}

// quick str functions. the 'q' stands for quick.
char* ng_qstrcpy (char* s, const char* a, int64_t len) {
	if (len == 0) {
		return ng_strnul(s);
	}
	s = realloc(s, len+1);
	return strcpy(s, a);
}

char* ng_qstrcat (char* s, int64_t s_len, const char* a, int64_t a_len) {
	int64_t len = s_len + a_len;
	s = realloc(s, len+1);
	return strcat(s, a);
}

char* ng_qstrcatc (char* s, int64_t s_len, char c) {
	int64_t len = s_len + 1;
	s = realloc(s, len+1);
	char a[2] = {c, '\0'};
	return strcat(s, a);
}

char* ng_qsubstr (char* s, const char* a, int64_t a_len, int64_t start, int64_t len) {
	if (start == a_len) {
		return ng_strnul(s);
	} else if (start + len > a_len) {
		len = a_len - start;
	}
	s = realloc(s, len+1);
	s = strncpy(s, a+start, len);
	s[len] = '\0';
	return s;
}

int64_t ng_qstrdelim (const char* s, int64_t len, const char* delim, int64_t start) {
	// first delim char from start
	for (int64_t i=start; s[i] != '\0'; i++) {
		if (ng_strchr(delim, s[i])) {
			return i;
		}
	}
	return -1;
}

int64_t ng_qstrndelim (const char* s, int64_t len, const char* delim, int64_t start) {
	// first non-delim char from start
	for (int64_t i=start; s[i] != '\0'; i++) {
		if (!ng_strchr(delim, s[i])) {
			return i;
		}
	}
	return -1;
}

bool ng_strchr (const char* s, char c) {
	for (int64_t i=0; s[i] != '\0'; i++) {
		if (s[i] == c) {
			return true;
		}
	}
	return false;
}

void ng_strupper (char* s) {
	for (int64_t i=0; s[i] != '\0'; i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			s[i] = s[i] - 32;
		}
	}
}

void ng_strlower (char* s) {
	for (int64_t i=0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] = s[i] + 32;
		}
	}
}

char* ng_atoh (char* s, const char* a, char c) {
	// pass an uppercase/lowercase letter to output uppercase/lowercase hex.
	// if the letter is X/x, also prepends "0x".
	int64_t len = ng_strlen(a);
	return ng_qatoh(s, a, len, c);
}

double ng_atof (const char* s) {
	return atof(s);
}

int64_t ng_atoi (const char* s) {
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
	int64_t len = ng_strlen(a);
	return ng_qhtoa(s, a, len);
}

char* ng_ftoa (char* s, const char* fmt, double d) {
	// calls sprintf(s,fmt,d)
	// Max buffer length:
	// smallest subnormal double is about 5*10^-324
	// plus 3 chars for "-0." and 1 char for '\0'
	// plus strlen(fmt) for non-format-specifier chars
	// gives 324+4+strlen(fmt) = 328+strlen(fmt)
	int64_t len = 328 + ng_strlen(fmt);
	char a[len];
	int64_t n = sprintf(a, fmt, d);
	if (n < 0) {
		return ng_strnul(s);
	}
	s = realloc(s, n+1);
	s = strncpy(s, a, n);
	s[n] = '\0';
	return s;
}

char* ng_itoa (char* s, const char* fmt, int64_t i) {
	// calls sprintf(s,fmt,i)
	// Max buffer length:
	// smallest int64_t is -9,223,372,036,854,775,808 or 19 digits
	// plus 1 char for '-' and 1 char for '\0'
	// plus strlen(fmt) for non-format-specifier chars
	// gives 19+2+strlen(fmt) = 21+strlen(fmt)
	int64_t len = 21 + ng_strlen(fmt);
	char a[len];
	int64_t n = sprintf(a, fmt, i);
	if (n < 0) {
		return ng_strnul(s);
	}
	s = realloc(s, n+1);
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

// more quick str functions
char* ng_qatoh (char* s, const char* a, int64_t len, char c) {
	bool upper;
	if (c >= 'A' && c <='Z') {
		upper = true;
	} else {
		upper = false;
	}
	
	int64_t n = len * 2;
	int64_t i;
	if (c == 'X' || c == 'x') {
		n+=2;
		s = realloc(s, n+1);
		s[0] = '0';
		s[1] = 'x';
		i=2;
	} else {
		s = realloc(s, n+1);
		i=0;
	}
	
	int64_t k=0;
	char h;
	for (; i<len; i++) {
		h = (a[i] >> 4) & 0x0f;
		if (h < 10) {
			s[k] = h + '0';
		} else if (upper) {
			s[k] = (h - 10) + 'A';
		} else {
			s[k] = (h - 10) + 'a';
		}
		k++;
		
		h = a[i] & 0x0f;
		if (h < 10) {
			s[k] = h + '0';
		} else if (upper) {
			s[k] = (h - 10) + 'A';
		} else {
			s[k] = (h - 10) + 'a';
		}
		k++;
	}
	s[n] = '\0';
	return s;
}

char* ng_qhtoa (char* s, const char* a, int64_t len) {
	int64_t i=0;
	int64_t j = ng_strdelim(a, "0123456789abcdefABCDEF", 0);
	if (j < 0) {
		return ng_strnul(s);
	} else if (a[j] == '0' && a[j+1] == 'x') {
		i = j+2;
	} else {
		i = j;
	}
	
	int64_t n = (len+1) / 2;
	char b[n+1];
	int64_t k=0;
	char h;
	for (; i<len; i+=2) {
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
	return ng_qstrcpy(s, b, k);
}


