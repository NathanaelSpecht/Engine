
/*  test.c  Unit tests for TIS.
    Copyright (C) 2022  Trees in Space
*/

#include "tis_string.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

void test (bool b) {
	if (b) { 
		printf("pass ");
	} else {
		printf("FAIL ");
	}
}

int main (int argc, char** argv) {
	printf("Starting test\n");
	
	printf("\n[tis_string]:\n");
	
	{
		printf("string_length: ");
		test(string_length(NULL) == 0);
		test(string_length("") == 0);
		test(string_length("a") == 1);
		test(string_length("hi") == 2);
		test(string_length("Hello\nWorld!") == 12);
		printf("\n");
	}
	
	{
		printf("string_delete: ");
		char* a = NULL;
		char* b = malloc(1);
		char* c = malloc(3);
		
		string_delete(&a);
		test(a == NULL);
		
		b[0] = '\0';
		string_delete(&b);
		test(b == NULL);
		
		c[0] = 'H';
		c[1] = 'i';
		c[2] = '\0';
		string_delete(&c);
		test(c == NULL);
		
		printf("\n");
	}
	
	{
		printf("string_equals: ");
		test(string_equals(NULL, NULL) == true);
		test(string_equals("", "") == true);
		test(string_equals("Hello", "Hello") == true);
		test(string_equals("Hello", NULL) == false);
		test(string_equals("Hello", "World") == false);
		test(string_equals(NULL, "World") == false);
		printf("\n");
	}
	
	{
		printf("string_copy: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* f = NULL;
		
		string_copy(NULL, &a);
		test(a == NULL);
		
		string_copy("", &b);
		test(string_equals("", b));
		
		string_copy("a", &c);
		test(string_equals("a", c));
		
		string_copy("Hello", &d);
		test(string_equals("Hello", d));
		
		string_copy("World", &e);
		string_copy("", &e);
		test(string_equals("", e));
		
		string_copy("Hello World!", &f);
		string_copy(NULL, &f);
		test(f == NULL);
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		string_delete(&f);
		printf("\n");
	}
	
	{
		printf("substring: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		
		substring(a, 0, 0, &a);
		test(a == NULL);
		
		string_copy("", &b);
		substring(b, 0, 0, &a);
		test(string_equals("", b));
		
		string_copy("Hello World", &c);
		substring(c, 0, 5, &c);
		test(string_equals("Hello", c));
		
		string_copy("Hello World", &d);
		substring(d, 6, 5, &d);
		test(string_equals("World", d));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		printf("\n");
	}
	
	{
		printf("string_trim: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* f = NULL;
		char* g = NULL;
		
		string_trim(&a);
		test(a == NULL);
		
		string_copy("", &b);
		string_trim(&b);
		test(string_equals("", b));
		
		string_copy("c", &c);
		string_trim(&c);
		test(string_equals("c", c));
		
		string_copy("d ", &d);
		string_trim(&d);
		test(string_equals("d", d));
		
		string_copy(" e", &e);
		string_trim(&e);
		test(string_equals("e", e));
		
		string_copy(" f ", &f);
		string_trim(&f);
		test(string_equals("f", f));
		
		string_copy(" hi ", &g);
		string_trim(&g);
		test(string_equals("hi", g));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		string_delete(&f);
		string_delete(&g);
		printf("\n");
	}
	
	{
		printf("string_append_char: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("string_append: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("string_prepend: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("string_find: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("string_replace: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("string_find_replace: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("stringlist: ");
		char** list = NULL;
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		string_copy("", &a);
		string_copy("Hello", &b);
		
		test(stringlist_length(list) == 0);
		
		stringlist_add(c, &list);
		test(stringlist_length(list) == 0);
		
		stringlist_add(a, &list);
		test(stringlist_length(list) == 1);
		
		test(string_equals(a, list[0]));
		
		stringlist_delete(&list);
		test(stringlist_length(list) == 0);
		
		test(list == NULL);
		
		stringlist_add(b, &list);
		stringlist_add(a, &list);
		test(stringlist_length(list) == 2);
		
		test(string_equals(b, list[0]));
		
		test(string_equals(a, list[1]));
		
		test(string_equals(NULL, list[2]));
		
		stringlist_delete(&list);
		test(stringlist_length(list) == 0);
		
		test(list == NULL);
		
		string_delete(&a);
		string_delete(&b);
		printf("\n");
	}
	
	{
		printf("string_split: ");
		test(false);
		printf("\n");
	}
	
	{
		printf("string_join: ");
		test(false);
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

