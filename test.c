
/*  test.c -- Unit tests for 'TIS' game engine library.
    version 0.1, 2022 August 30
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
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		
		string_append_char('\0', 0, &a);
		test(a == NULL);
		
		string_append_char('b', 0, &b);
		test(string_equals(b, "b"));
		
		string_copy("Hello World", &c);
		string_append_char('!', 11, &c);
		test(string_equals(c, "Hello World!"));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		printf("\n");
	}
	
	{
		printf("string_append: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		
		string_append(NULL, &a);
		test(a == NULL);
		
		string_append("Hello", &b);
		test(string_equals("Hello", b));
		
		string_copy("World", &c);
		string_append(NULL, &c);
		test(string_equals("World", c));
		
		string_copy("Hello", &d);
		string_append(" World", &d);
		test(string_equals("Hello World", d));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		printf("\n");
	}
	
	{
		printf("string_prepend: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		
		string_prepend(NULL, &a);
		test(a == NULL);
		
		string_prepend("Hello", &b);
		test(string_equals("Hello", b));
		
		string_copy("World", &c);
		string_prepend(NULL, &c);
		test(string_equals("World", c));
		
		string_copy("World", &d);
		string_prepend("Hello ", &d);
		test(string_equals("Hello World", d));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		printf("\n");
	}
	
	{
		printf("string_find: ");
		test(string_find(NULL, 0, NULL) == 0);
		test(string_find(NULL, 0, "") == -1);
		test(string_find("", 0, NULL) == -1);
		test(string_find("", 0, "") == 0);
		test(string_find("a", 0, "") == -1);
		test(string_find("a", 0, "Hello") == -1);
		test(string_find("H", 0, "Hello") == 0);
		test(string_find("Hello", 0, "Hello") == 0);
		test(string_find("Hello", 0, "Hi Hello World") == 3);
		test(string_find("Hello", 4, "Hi Hello World") == -1);
		test(string_find("Hello", 0, "HHelloo") == 1);
		test(string_find("World", 0, "Worl d") == -1);
		printf("\n");
	}
	
	{
		printf("string_replace: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		
		string_replace(NULL, 0, 0, &a);
		test(a == NULL);
		
		string_replace("Hello", 0, 0, &b);
		test(string_equals("Hello", b));
		
		string_copy("", &c);
		string_replace("Hello", 0, 0, &c);
		test(string_equals("Hello", c));
		
		string_copy("Hello", &d);
		string_replace(NULL, 0, 0, &d);
		test(string_equals("Hello", d));
		
		string_copy("World", &e);
		string_replace("Hello ", 0, 0, &e);
		test(string_equals("Hello World", e));
		string_replace("World!", 6, 5, &e);
		test(string_equals("Hello World!", e));
		string_replace(", ", 5, 1, &e);
		test(string_equals("Hello, World!", e));
		string_replace("", -1, 0, &e);
		test(string_equals("Hello, World!", e));
		string_replace("", 14, 0, &e);
		test(string_equals("Hello, World!", e));
		string_replace("", 0, 13, &e);
		test(string_equals("", e));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		printf("\n");
	}
	
	{
		printf("string_find_replace: ");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* f = NULL;
		char* g = NULL;
		
		string_find_replace(NULL, NULL, &a);
		test(a == NULL);
		
		string_find_replace(NULL, "", &b);
		test(string_equals("", b));
		string_find_replace(NULL, "a", &b);
		test(string_equals("", b));
		
		string_copy("", &c);
		string_find_replace("", NULL, &c);
		test(c == NULL);
		
		string_copy("Hello", &d);
		string_find_replace("", "", &d);
		test(string_equals("Hello", d));
		
		string_copy("[greeting] [name]", &e);
		string_find_replace("[greeting]", "Hello", &e);
		test(string_equals("Hello [name]", e));//
		string_find_replace("[name]", "World", &e);
		test(string_equals("Hello World", e));
		string_find_replace("Hello World", "", &e);
		test(string_equals("", e));
		string_find_replace("", "Hi", &e);
		test(string_equals("Hi", e));
		string_find_replace("", "a", &e);
		test(string_equals("Hi", e));
		
		string_copy("aaa", &f);
		string_find_replace("a", "Hi. ", &f);
		test(string_equals("Hi. Hi. Hi. ", f));
		
		string_copy("abba", &g);
		string_find_replace("a", "aa", &g);
		test(string_equals("aabbaa", g));
		
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
		char** a = NULL;
		char** b = NULL;
		char** c = NULL;
		char** d = NULL;
		char** e = NULL;
		char** f = NULL;
		
		string_split(NULL, '.', &a);
		test(a == NULL);
		
		string_split("Hello", 'a', &b);
		test(stringlist_length(b) == 1);
		if (stringlist_length(b) == 1) {
			test(string_equals(b[0], "Hello"));
		}
		
		string_split(" Hello", ' ', &c);
		test(stringlist_length(c) == 2);
		if (stringlist_length(c) == 2) {
			test(string_equals(c[0], ""));
			test(string_equals(c[1], "Hello"));
		}
		
		string_split("Hello|", '|', &d);
		test(stringlist_length(d) == 2);
		if (stringlist_length(d) == 2) {
			test(string_equals(d[0], "Hello"));
			test(string_equals(d[1], ""));
		}
		
		string_split("Hello World", ' ', &e);
		test(stringlist_length(e) == 2);
		if (stringlist_length(e) == 2) {
			test(string_equals(e[0], "Hello"));
			test(string_equals(e[1], "World"));
		}
		
		string_split("this_long_name", '_', &f);
		test(stringlist_length(f) == 3);
		if (stringlist_length(f) == 3) {
			test(string_equals(f[0], "this"));
			test(string_equals(f[1], "long"));
			test(string_equals(f[2], "name"));
		}
		
		printf("\nstring_join: ");
		char* s = NULL;
		char* t = NULL;
		char* u = NULL;
		char* v = NULL;
		char* w = NULL;
		char* x = NULL;
		
		string_join(a, '.', &s);
		test(s == NULL);
		
		string_join(b, 'a', &t);
		test(string_equals("Hello", t));
		
		string_join(c, ' ', &u);
		test(string_equals(" Hello", u));
		
		string_join(d, '|', &v);
		test(string_equals("Hello|", v));
		
		string_join(e, ' ', &w);
		test(string_equals("Hello World", w));
		
		string_join(f, '_', &x);
		test(string_equals("this_long_name", x));
		
		stringlist_delete(&a);
		stringlist_delete(&b);
		stringlist_delete(&c);
		stringlist_delete(&d);
		stringlist_delete(&e);
		stringlist_delete(&f);
		string_delete(&s);
		string_delete(&t);
		string_delete(&u);
		string_delete(&v);
		string_delete(&w);
		string_delete(&x);
		printf("\n");
	}
	
	printf("\nClosing test\n");
	
	return 0;
}

