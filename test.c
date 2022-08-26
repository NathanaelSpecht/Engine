
/*  test.c  Unit tests for TIS.
    Copyright (C) 2022  Trees in Space
*/

#include "tis_string.h"
#include "tis_file.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

void test (bool b, char* s);

void test (bool b, char* s) {
	if (b) { 
		printf("pass ");
	} else {
		printf("FAIL ");
	}
	if (s != NULL) {
		free(s);
	}
}

int main (int argc, char** argv) {
	printf("Starting test\n");
	
	printf("\n[tis_string]:\n");
	
	{
		printf("string_length: ");
		test(string_length(NULL) == -1, NULL);
		test(string_length("") == 0, NULL);
		test(string_length("a") == 1, NULL);
		test(string_length("hi") == 2, NULL);
		test(string_length("Hello\nWorld!") == 12, NULL);
		printf("\n");
	}
	
	{
		printf("string_equals: ");
		test(string_equals(NULL, NULL) == true, NULL);
		test(string_equals("", "") == true, NULL);
		test(string_equals("Hello", "Hello") == true, NULL);
		test(string_equals("Hello", NULL) == false, NULL);
		test(string_equals("Hello", "World") == false, NULL);
		test(string_equals(NULL, "World") == false, NULL);
		printf("\n");
	}
	
	{
		printf("string_copy: ");
		char* a = NULL;
		string_copy(NULL, &a);
		test(a == NULL, a);
		char* b = NULL;
		string_copy("", &b);
		test(string_equals("", b), b);
		char* c = NULL;
		string_copy("a", &c);
		test(string_equals("a", c), c);
		char* d = NULL;
		string_copy("Hello", &d);
		test(string_equals("Hello", d), d);
		char* e = NULL;
		string_copy("World", &e);
		string_copy("", &e);
		test(string_equals("", e), e);
		char* f = NULL;
		string_copy("Hello World!", &f);
		string_copy(NULL, &f);
		test(f == NULL, f);
		printf("\n");
	}
	
	{
		printf("string_trim: ");
		char* a = NULL;
		string_trim(&a);
		test(a == NULL, a);
		char* b = NULL;
		string_copy("", &b);
		string_trim(&b);
		test(string_equals("", b), b);
		char* c = NULL;
		string_copy("c", &c);
		string_trim(&c);
		test(string_equals("c", c), c);
		char* d = NULL;
		string_copy("d ", &d);
		string_trim(&d);
		test(string_equals("d", d), d);
		char* e = NULL;
		string_copy(" e", &e);
		string_trim(&e);
		test(string_equals("e", e), e);
		char* f = NULL;
		string_copy(" f ", &f);
		string_trim(&f);
		test(string_equals("f", f), f);
		char* g = NULL;
		string_copy(" hi ", &g);
		string_trim(&g);
		test(string_equals("hi", g), g);
		printf("\n");
	}
	
	{
		printf("string_append: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_prepend: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("substring: ");
		char* a = NULL;
		substring(0, 0, &a);
		test(a == NULL, a);
		char* b = NULL;
		string_copy("", &b);
		substring(0, 0, &a);
		test(string_equals("", b), b);
		char* c = NULL;
		string_copy("Hello World", &c);
		substring(0, 5, &c);
		test(string_equals("Hello", c), c);
		char* d = NULL;
		string_copy("Hello World", &d);
		substring(6, 5, &d);
		test(string_equals("World", d), d);
		char* e = NULL;
		string_copy("Hello", &e);
		substring(2, 7, &e);
		test(string_equals("llo", e), e);
		char* f = NULL;
		string_copy("Hello", &f);
		substring(5, 5, &f);
		test(string_equals("", f), f);
		char* g = NULL;
		string_copy("Hello", &g);
		substring(-5, 5, &g);
		test(string_equals("", g), g);
		char* h = NULL;
		string_copy("Hello", &h);
		substring(-2, 4, &h);
		test(string_equals("He", h), h);
		char* i = NULL;
		string_copy("Hello", &i);
		substring(-2, 10, &i);
		test(string_equals("Hello", i), i);
		printf("\n");
	}
	
	{
		printf("string_find: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_replace: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_replace_all: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_split: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_join: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_is_bool: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_is_int: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_is_float: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_to_bool: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_to_int: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("string_to_float: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("bool_to_string: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("int_to_string: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("float_to_string: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("ascii_to_hex: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("hex_to_ascii: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	printf("\n[tis_file]:\n");
	
	{
		printf("file_read_ascii: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("file_read_hex: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("file_log: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("file_write_ascii: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("file_write_hex: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("file_append_ascii: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	{
		printf("file_append_hex: ");
		char* a = NULL;
		test(false, a);
		printf("\n");
	}
	
	printf("\nClosing test\n");
	
	return 0;
}

/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    
    Trees in Space  treesinspacecompany@gmail.com
*/

