
/*  test.c -- Unit tests for 'TIS' game engine library.
    version 0.1, 2022 August 30
*/

#include "tis_string.h"
#include "tis_convert.h"
#include "tis_file.h"
#include "tis_vector.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

void test (bool b) {
	if (b) { 
		printf(" pass");
	} else {
		printf(" FAIL");
	}
}

int main (int argc, char** argv) {
	printf("Starting test\n");
	
	printf("\n[tis_string]:\n");
	
	{
		printf("string_length:");
		test(string_length(NULL) == 0);
		test(string_length("") == 0);
		test(string_length("a") == 1);
		test(string_length("hi") == 2);
		test(string_length("Hello\nWorld!") == 12);
		printf("\n");
	}
	
	{
		printf("string_delete:");
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
		printf("string_equals:");
		test(string_equals(NULL, NULL) == true);
		test(string_equals("", "") == true);
		test(string_equals("Hello", "Hello") == true);
		test(string_equals("Hello", NULL) == false);
		test(string_equals("Hello", "World") == false);
		test(string_equals(NULL, "World") == false);
		printf("\n");
	}
	
	{
		printf("string_copy:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* f = NULL;
		
		string_copy(&a, NULL);
		test(a == NULL);
		
		string_copy(&b, "");
		test(string_equals("", b));
		
		string_copy(&c, "a");
		test(string_equals("a", c));
		
		string_copy(&d, "Hello");
		test(string_equals("Hello", d));
		
		string_copy(&e, "World");
		string_copy(&e, "");
		test(string_equals("", e));
		
		string_copy(&f, "Hello World!");
		string_copy(&f, NULL);
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
		printf("substring:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		
		substring(&a, a, 0, 0);
		test(a == NULL);
		
		string_copy(&b, "");
		substring(&b, b, 0, 0);
		test(string_equals("", b));
		
		string_copy(&c, "Hello World");
		substring(&c, c, 0, 5);
		test(string_equals("Hello", c));
		
		string_copy(&d, "Hello World");
		substring(&d, d, 6, 5);
		test(string_equals("World", d));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		printf("\n");
	}
	
	{
		printf("string_trim:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* f = NULL;
		char* g = NULL;
		
		string_trim(&a);
		test(a == NULL);
		
		string_copy(&b, "");
		string_trim(&b);
		test(string_equals("", b));
		
		string_copy(&c, "c");
		string_trim(&c);
		test(string_equals("c", c));
		
		string_copy(&d, "d ");
		string_trim(&d);
		test(string_equals("d", d));
		
		string_copy(&e, " e");
		string_trim(&e);
		test(string_equals("e", e));
		
		string_copy(&f, " f ");
		string_trim(&f);
		test(string_equals("f", f));
		
		string_copy(&g, " hi ");
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
		printf("string_append_char:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		
		string_append_char(&a, '\0', 0);
		test(a == NULL);
		
		string_append_char(&b, 'b', 0);
		test(string_equals(b, "b"));
		
		string_copy(&c, "Hello World");
		string_append_char(&c, '!', 11);
		test(string_equals(c, "Hello World!"));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		printf("\n");
	}
	
	{
		printf("string_append:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		
		string_append(&a, NULL);
		test(a == NULL);
		string_append(&a, "");
		test(string_equals("", a));
		
		string_append(&b, "Hello");
		test(string_equals("Hello", b));
		
		string_copy(&c, "World");
		string_append(&c, NULL);
		test(string_equals("World", c));
		
		string_copy(&d, "Hello");
		string_append(&d, " World");
		test(string_equals("Hello World", d));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		printf("\n");
	}
	
	{
		printf("string_prepend:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		
		string_prepend(&a, NULL);
		test(a == NULL);
		string_prepend(&a, "");
		test(string_equals("", a));
		
		string_prepend(&b, "Hello");
		test(string_equals("Hello", b));
		
		string_copy(&c, "World");
		string_prepend(&c, NULL);
		test(string_equals("World", c));
		
		string_copy(&d, "World");
		string_prepend(&d, "Hello ");
		test(string_equals("Hello World", d));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		printf("\n");
	}
	
	{
		printf("string_find:");
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
		printf("string_replace:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		
		string_replace(&a, NULL, 0, 0);
		test(a == NULL);
		
		string_replace(&b, "Hello", 0, 0);
		test(string_equals("Hello", b));
		
		string_copy(&c, "");
		string_replace(&c, "Hello", 0, 0);
		test(string_equals("Hello", c));
		
		string_copy(&d, "Hello");
		string_replace(&d, NULL, 0, 0);
		test(string_equals("Hello", d));
		
		string_copy(&e, "World");
		string_replace(&e, "Hello ", 0, 0);
		test(string_equals("Hello World", e));
		string_replace(&e, "World!", 6, 5);
		test(string_equals("Hello World!", e));
		string_replace(&e, ", ", 5, 1);
		test(string_equals("Hello, World!", e));
		string_replace(&e, "", -1, 0);
		test(string_equals("Hello, World!", e));
		string_replace(&e, "", 14, 0);
		test(string_equals("Hello, World!", e));
		string_replace(&e, "", 0, 13);
		test(string_equals("", e));
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		printf("\n");
	}
	
	{
		printf("string_find_replace:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* f = NULL;
		char* g = NULL;
		
		string_find_replace(&a, NULL, NULL);
		test(a == NULL);
		
		string_find_replace(&b, NULL, "");
		test(string_equals("", b));
		string_find_replace(&b, NULL, "a");
		test(string_equals("", b));
		
		string_copy(&c, "");
		string_find_replace(&c, "", NULL);
		test(c == NULL);
		
		string_copy(&d, "Hello");
		string_find_replace(&d, "", "");
		test(string_equals("Hello", d));
		
		string_copy(&e, "[greeting] [name]");
		string_find_replace(&e, "[greeting]", "Hello");
		test(string_equals("Hello [name]", e));
		string_find_replace(&e, "[name]", "World");
		test(string_equals("Hello World", e));
		string_find_replace(&e, "Hello World", "");
		test(string_equals("", e));
		string_find_replace(&e, "", "Hi");
		test(string_equals("Hi", e));
		string_find_replace(&e, "", "a");
		test(string_equals("Hi", e));
		
		string_copy(&f, "aaa");
		string_find_replace(&f, "a", "Hi. ");
		test(string_equals("Hi. Hi. Hi. ", f));
		
		string_copy(&g, "abba");
		string_find_replace(&g, "a", "aa");
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
		printf("string_starts_with:");
		test(string_starts_with(NULL, NULL) == true);
		test(string_starts_with("", "") == true);
		test(string_starts_with(NULL, "") == false);
		test(string_starts_with("", NULL) == false);
		test(string_starts_with("Hello World", "Hello") == true);
		test(string_starts_with("Hello", "a") == false);
		printf("\n");
	}
	
	{
		printf("stringlist:");
		char** list = NULL;
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		
		string_copy(&a, "");
		string_copy(&b, "Hello");
		test(stringlist_length(list) == 0);
		
		stringlist_add(&list, c);
		test(stringlist_length(list) == 0);
		
		stringlist_add(&list, a);
		test(stringlist_length(list) == 1);
		test(string_equals(a, list[0]));
		
		stringlist_delete(&list);
		test(stringlist_length(list) == 0);
		test(list == NULL);
		
		stringlist_add(&list, b);
		stringlist_add(&list, a);
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
		printf("string_split:");
		char** a = NULL;
		char** b = NULL;
		char** c = NULL;
		char** d = NULL;
		char** e = NULL;
		char** f = NULL;
		
		string_split(&a, NULL, '.');
		test(a == NULL);
		
		string_split(&b, "Hello", 'a');
		test(stringlist_length(b) == 1);
		if (stringlist_length(b) == 1) {
			test(string_equals(b[0], "Hello"));
		}
		
		string_split(&c, " Hello", ' ');
		test(stringlist_length(c) == 2);
		if (stringlist_length(c) == 2) {
			test(string_equals(c[0], ""));
			test(string_equals(c[1], "Hello"));
		}
		
		string_split(&d, "Hello|", '|');
		test(stringlist_length(d) == 2);
		if (stringlist_length(d) == 2) {
			test(string_equals(d[0], "Hello"));
			test(string_equals(d[1], ""));
		}
		
		string_split(&e, "Hello World", ' ');
		test(stringlist_length(e) == 2);
		if (stringlist_length(e) == 2) {
			test(string_equals(e[0], "Hello"));
			test(string_equals(e[1], "World"));
		}
		
		string_split(&f, "this_long_name", '_');
		test(stringlist_length(f) == 3);
		if (stringlist_length(f) == 3) {
			test(string_equals(f[0], "this"));
			test(string_equals(f[1], "long"));
			test(string_equals(f[2], "name"));
		}
		
		printf("\nstring_join:");
		char* s = NULL;
		char* t = NULL;
		char* u = NULL;
		char* v = NULL;
		char* w = NULL;
		char* x = NULL;
		
		string_join(&s, a, '.');
		test(s == NULL);
		
		string_join(&t, b, 'a');
		test(string_equals("Hello", t));
		
		string_join(&u, c, ' ');
		test(string_equals(" Hello", u));
		
		string_join(&v, d, '|');
		test(string_equals("Hello|", v));
		
		string_join(&w, e, ' ');
		test(string_equals("Hello World", w));
		
		string_join(&x, f, '_');
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
	
	printf("\n[tis_convert]:\n");
	
	{
		printf("bool:");
		char* a = NULL;
		char* b = NULL;
		
		test(string_is_bool(NULL) == false);
		test(string_to_bool(NULL) == false);
		
		test(string_is_bool("") == false);
		test(string_to_bool("") == false);
		
		test(string_is_bool("true") == true);
		test(string_to_bool("true") == true);
		bool_to_string(&a, true);
		test(string_equals(a, "true"));
		
		test(string_is_bool("false") == true);
		test(string_to_bool("false") == false);
		bool_to_string(&b, false);
		test(string_equals(b, "false"));
		
		test(string_is_bool("Hello") == false);
		test(string_to_bool("Hello") == false);
		
		string_delete(&a);
		string_delete(&b);
		printf("\n");
	}
	
	{
		printf("int:");
		int i = 0;
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		
		test(string_is_int(NULL) == false);
		i = string_to_int(NULL);
		test(i == 0);
		printf(" %d\n", i);
		
		test(string_is_int("") == false);
		i = string_to_int("");
		test(i == 0);
		printf(" %d\n", i);
		
		test(string_is_int("0") == true);
		i = string_to_int("0");
		test(i == 0);
		int_to_string(&a, 0);
		test(string_equals(a, "0"));
		printf(" 0 %s %d\n", a, i);
		
		test(string_is_int("1337") == true);
		i = string_to_int("1337");
		test(i == 1337);
		int_to_string(&c, 1337);
		test(string_equals(c, "1337"));
		printf(" 1337 %s %d\n", c, i);
		
		test(string_is_int("-2147483647") == true);
		i = string_to_int("-2147483647");
		test(i == -2147483647);
		int_to_string(&d, -2147483647);
		test(string_equals(d, "-2147483647"));
		printf(" -2147483647 %s %d\n", d, i);
		
		test(string_is_int("Hello") == false);
		i = string_to_int("Hello");
		test(i == 0);
		printf(" %d\n", i);
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		printf("\n");
	}
	
	{
		// Test for a precision of 6 decimal digits
		printf("float:");
		float f = 0.0;
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* e = NULL;
		char* g = NULL;
		
		test(string_is_float(NULL) == false);
		f = string_to_float(NULL);
		test(f > -0.000001 && f < 0.000001);
		printf(" %f\n", f);
		
		test(string_is_float("") == false);
		f = string_to_float("");
		test(f > -0.000001 && f < 0.000001);
		printf(" %f\n", f);
		
		test(string_is_float("0.0") == true);
		f = string_to_float("0.0");
		test(f > -0.000001 && f < 0.000001);
		float_to_string(&a, 0.0, 6);
		test(string_equals(a, "0.000000"));
		printf(" 0.000000 %s %f\n", a, f);
		
		test(string_is_float("-0.2147483647") == true);
		f = string_to_float("-0.2147483647");
		test(f > -0.214749 && f < -0.214747);
		float_to_string(&d, -0.2147483647, 10);
		test(string_equals(d, "-0.214748"));
		printf(" -0.214748 %s %f\n", d, f);
		
		test(string_is_float("-2147480000.0") == true);
		f = string_to_float("-2147480000.0");
		test(f > -2147490000.0 && f < -2147470000.0);
		float_to_string(&g, -2147480000.0, -6);
		test(string_equals(g, "-2147480000.0"));
		printf(" -2147480000.0 %s %f\n", g, f);
		
		test(string_is_float("Hello") == false);
		f = string_to_float("Hello");
		test(f > -0.000001 && f < 0.000001);
		printf(" %f\n", f);
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&e);
		string_delete(&g);
		printf("\n");
	}
	
	printf("\n[tis_file]:\n");
	
	{
		printf("file_exists:");
		test(file_exists(NULL) == false);
		test(file_exists("") == false);
		test(file_exists("save/test/dne.txt") == false);
		test(file_exists("save/test/empty.txt"));
		test(file_exists("save/test/in.txt"));
		printf("\n");
	}
	
	{
		printf("file_delete:");
		
		file_delete(NULL);
		file_delete("");
		file_delete("save/test/dne.txt");
		
		file_write("save/test/x.txt", "delete this");
		test(file_exists("save/test/x.txt"));
		if (file_exists("save/test/x.txt")) {
			file_delete("save/test/x.txt");
			test(file_exists("save/test/x.txt") == false);
		}
		
		printf("\n");
	}
	
	{
		printf("file_read:");
		char* a = NULL;
		char* b = NULL;
		char* c = NULL;
		char* d = NULL;
		char* z = NULL;
		
		file_read("save/test/dne.txt", &a);
		test(a == NULL);
		
		file_read("save/test/empty.txt", &b);
		test(string_equals("", b));
		
		file_read("save/test/in.txt", &d);
		test(string_equals("Hello World\n", d));
		
		file_read(NULL, &z);
		test(z == NULL);
		file_read("", &z);
		test(z == NULL);
		
		string_delete(&a);
		string_delete(&b);
		string_delete(&c);
		string_delete(&d);
		string_delete(&z);
		printf("\n");
	}
	
	{
		printf("file_write:");
		char* c = NULL;
		
		file_write(NULL, "nothing");
		test(file_exists(NULL) == false);
		
		file_write("", "nothing");
		test(file_exists("") == false);
		
		file_write("save/test/a.txt", NULL);
		test(file_exists("save/test/a.txt") == false);
		
		file_write("save/test/b.txt", "");
		test(file_exists("save/test/b.txt") == false);
		
		file_write("save/test/c.txt", "Hello");
		test(file_exists("save/test/c.txt"));
		if (file_exists("save/test/c.txt")) {
			file_read("save/test/c.txt", &c);
			test(string_equals("Hello", c));
		}
		
		string_delete(&c);
		file_write("save/test/c.txt", "World");
		test(file_exists("save/test/c.txt"));
		if (file_exists("save/test/c.txt")) {
			file_read("save/test/c.txt", &c);
			test(string_equals("World", c));
			file_delete("save/test/c.txt");
		}
		
		string_delete(&c);
		printf("\n");
	}
	
	{
		printf("file_append:");
		char* i = NULL;
		
		file_append(NULL, "nothing");
		test(file_exists(NULL) == false);
		
		file_append("", "nothing");
		test(file_exists("") == false);
		
		file_append("save/test/g.txt", NULL);
		test(file_exists("save/test/g.txt") == false);
		
		file_append("save/test/h.txt", "");
		test(file_exists("save/test/h.txt") == false);
		
		file_append("save/test/i.txt", "Hello");
		test(file_exists("save/test/i.txt"));
		if (file_exists("save/test/i.txt")) {
			file_read("save/test/i.txt", &i);
			test(string_equals("Hello", i));
		}
		
		string_delete(&i);
		file_append("save/test/i.txt", "World");
		test(file_exists("save/test/i.txt"));
		if (file_exists("save/test/i.txt")) {
			file_read("save/test/i.txt", &i);
			test(string_equals("HelloWorld", i));
			file_delete("save/test/i.txt");
		}
		
		string_delete(&i);
		printf("\n");
	}
	
	printf("\n[tis_vector]:\n");
	
	{
		printf("vector2d_length:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_unit:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_transpose:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_determinant:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_adjoint:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_inverse:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_scale:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_scale:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_equals:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_add:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_dot:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_theta:");
		test(false);
		printf("\n");
	}
	
	{
		printf("vector2d_cross:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrixvector2d_dot:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_equals:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_add:");
		test(false);
		printf("\n");
	}
	
	{
		printf("matrix2d_dot:");
		test(false);
		printf("\n");
	}
	
	printf("\nClosing test\n");
	
	return 0;
}

