
/*  test.c  Unit tests for TIS.
    Copyright (C) 2022  Trees in Space
*/

#include "tis_string.h"
#include "tis_file.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

int main (int argc, char** argv) {
	printf("Starting test\n");
	
	printf("\n[tis_string]:\n");
	
	{
		printf("string_length: ");
		if (string_length(NULL) == -1 && string_length("") == 0 && 
		string_length("a") == 1 && string_length("hi") == 2 &&
		string_length("Hello\nWorld!") == 12) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_equals: ");
		if (string_equals(NULL, NULL) == true && string_equals("", "") == true &&
		string_equals("Hello", "Hello") == true && 
		string_equals("Hello", NULL) == false && 
		string_equals("Hello", "World") == false &&
		string_equals(NULL, "World") == false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_copy: ");
		char* a = NULL;
		a = string_copy(NULL);
		char* b = NULL;
		b = string_copy("");
		char* c = NULL;
		c = string_copy("a");
		char* d = NULL;
		d = string_copy("Hello\nWorld!");
		char* e = NULL;
		e = string_copy("Fizz");
		e = string_copy("");
		char* f = NULL;
		f = string_copy("Buzz");
		f = string_copy(NULL);
		if (a == NULL && string_equals("", b) && string_equals("a", c) &&
		string_equals("Hello\nWorld!", d) && string_equals("", e) &&
		f == NULL) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
		if (a != NULL) {
			free(a);
		}
		if (b != NULL) {
			free(b);
		}
		if (c != NULL) {
			free(c);
		}
		if (d != NULL) {
			free(d);
		}
		if (e != NULL) {
			free(e);
		}
		if (f != NULL) {
			free(f);
		}
	}
	
	{
		printf("string_trim: ");
		char* a = NULL;
		a = string_copy(NULL);
		string_trim(&a);
		char* b = NULL;
		b = string_copy("");
		string_trim(&b);
		char* c = NULL;
		c = string_copy(" ");
		string_trim(&c);
		char* d = NULL;
		d = string_copy(" a ");
		string_trim(&d);
		char* e = NULL;
		e = string_copy("\n\t Hello\n\tWorld ! \t\n");
		string_trim(&e);
		if (a == NULL && string_equals("", b) && string_equals("", c) &&
		string_equals("a", d) && string_equals("Hello\n\tWorld !", e)) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
		if (a != NULL) {
			free(a);
		}
		if (b != NULL) {
			free(b);
		}
		if (c != NULL) {
			free(c);
		}
		if (d != NULL) {
			free(d);
		}
		if (e != NULL) {
			free(e);
		}
	}
	
	{
		printf("string_assign: ");
		char* a = NULL;
		a = string_copy(NULL);
		string_assign(NULL, &a);
		char* b = NULL;
		b = string_copy("");
		string_assign("", &b);
		char* c = NULL;
		c = string_copy("a");
		string_assign("a", &c);
		char* d = NULL;
		d = string_copy("Hello");
		string_assign("World", &d);
		char* e = NULL;
		e = string_copy("Hello");
		string_assign("", &e);
		char* f = NULL;
		f = string_copy("World");
		string_assign(NULL, &f);
		if (a == NULL && string_equals("", b) && string_equals("a", c) &&
		string_equals("World", d) && string_equals("", e) && f == NULL) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
		if (a != NULL) {
			free(a);
		}
		if (b != NULL) {
			free(b);
		}
		if (c != NULL) {
			free(c);
		}
		if (d != NULL) {
			free(d);
		}
		if (e != NULL) {
			free(e);
		}
		if (f != NULL) {
			free(f);
		}
	}
	
	{
		printf("string_append: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_prepend: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("substring: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_find: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_replace: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_replace_all: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_split: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_join: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_is_bool: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_is_int: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_is_float: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_to_bool: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_to_int: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("string_to_float: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("bool_to_string: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("int_to_string: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("float_to_string: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("ascii_to_hex: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("hex_to_ascii: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	printf("\n[tis_file]:\n");
	
	{
		printf("file_read_ascii: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("file_read_hex: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("file_log: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("file_write_ascii: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("file_write_hex: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("file_append_ascii: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
	}
	
	{
		printf("file_append_hex: ");
		if (false) {
			printf("pass\n");
		} else {
			printf("FAILURE\n");
		}
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

