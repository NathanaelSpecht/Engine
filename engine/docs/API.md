# My Game Engine API

This is the API for my game engine.
**This is still in early development and is subject to change.**

Existing Modules:
- String functions
- Conversion functions for string-to-type and type-to-string conversion, 
and is-type functions to check if a string-to-type conversion will succeed.
- File functions.
- 2D Vector and matrix operations.
- Basic utility functions and macros.

Modules To Be Added:
- Music functions.
- 2D Rendering functions for text and sprite animations.
- 2D World, scene, object, hitbox, entity, and vehicle modeling. 2D model 
of the game world, disparate from the process used to render it.

## stringx.h

- [x] `int string_length (char* s)`
	- Finds the length of a string `s`, not including the null-terminator. NULL 
strings have length 0.

- [x] `void string_delete (char** s)`
	- Frees `s` and sets it to NULL, if not already NULL.

- [x] `bool string_equals (char* a, char* b)`
	- Checks if two strings are equal.

- [x] `void string_copy (char** s, char* a)`
	- Copies `a` into `s`.

- [x] `void substring (char** s, char* a, int start, int length)`
	- Takes a substring of `a` and stores it in `s`. `start` and `length`
describe the substring.

- [x] `void string_trim (char** s)`
	- Trims all whitespace off both ends of `s`.

- [x] `void string_append_char (char** s, char ch, int length)`
	- Quickly appends char `ch` to `s`. `length` is the length of `s`.

- [x] `void string_append (char** s, char* a)`
	- Appends `a` to `s`.

- [x] `void string_prepend (char** s, char* a)`
	- Prepends `a` to `s`.

- [x] `int string_find (char* a, int start, char* s)`
	- Finds the first index in `s` of a string `a`, starting at `start`.

- [x] `void string_replace (char** s, char* a, int start, int length)`
	- Replaces a region in `s` with `a`. `start` and `length` describe the 
region to replace.

- [x] `void string_find_replace (char** s, char* a, char* b)`
	- Replaces all regions matching `a` in `s` with `b`.

- [x] `bool string_starts_with (char* s, char* a)`
	- Checks if string `s` starts with string `a`.

- [x] `int stringlist_length (char** list)`
	- Finds the number of strings in `list`, not including the null-terminator. 
NULL lists have length 0.

- [x] `void stringlist_delete (char*** list)`
	- Frees `list` and sets it to NULL, if not already NULL.

- [x] `void stringlist_add (char*** list, char* s)`
	- Appends a string `s` to the end of `list`.

- [x] `void string_split (char*** list, char* s, char ch)`
	- Splits `s` on separator `ch` into a list of strings `list`.

- [x] `void string_join (char** s, char** list, char ch)`
	- Joins `list` on `ch` into a string `s`.

## convertx.h

- [x] `bool string_is_bool (char* s)`
	- Checks string `s` can be evaluated as bool.

- [x] `bool string_is_int (char* s)`
	- Checks if `s` can be evaluated as int.

- [x] `bool string_is_float (char* s)`
	- Checks if `s` can be evaluated as float.

- [x] `bool string_to_bool (char* s)`
	- Evaluates `s` as bool.

- [x] `int string_to_int (char* s)`
	- Evaluates `s` as int.

- [x] `float string_to_float (char* s)`
	- Evaluates `s` as float.

- [x] `void bool_to_string (char** s bool b)`
	- Evaluates bool `b` as a string, storing it in `s`.

- [x] `void int_to_string (char** s, int i)`
	- Evaluates int `i` as a string `s`.

- [x] `void float_to_string (char** s, float f, int d)`
	- Evaluates float `f` as decimal number with up to `d` digits, and stores 
it in string `s`.

## filex.h

- [x] `bool file_exists (char* file)`
	- Checks if `file` exists.

- [x] `void file_delete (char* file)`
	- Deletes `file`.

- [x] `void file_read (char* file, char** ascii)`
	- Opens `file`, reads all of its bytes as `ascii`, skips unrepresentable 
bytes, and closes the file.

- [x] `void file_write (char* file, char* ascii)`
	- Writes `ascii` into `file`. If file does not exist, creates it, otherwise 
overwrites it.

- [x] `void file_append (char* file, char* ascii)`
	- Appends `ascii` to end of `file`. If file does not exist, works the same 
as `file_write`, else appends to end.

## vectorx.h

Data Structures:

- [x] `struct vector2d {double x, double y}`
	- A vector v has n columns.
	Entry i in v is denoted vi.

- [x] `struct matrix2d {double xx, double xy, double yx, double yy}`
	- An mxn matrix A has m rows and n columns.
	Entry at row i column j in A, is denoted Aij.

Unary Vector and Matrix Operations:

- [x] `double vector2d_length (vector2d a)`
	- sqrt((a1 * a1) + (a2 * a2))

- [x] `vector2d vector2d_unit (vector2d a, double p)`
	- vector(a1 / length(a), a2 / length(a)),
	where length(a) != 0 at precision p,
	otherwise unit = 0

- [x] `matrix2d matrix2d_transpose (matrix2d A)`
	- matrix(A11, A21, A12, A22)

- [x] `double matrix2d_determinant (matrix2d A)`
	- (A11 * A22) - (A12 * A21)

- [x] `matrix2d matrix2d_adjoint (matrix2d A)`
	- matrix(A22, -A12, -A21, A11)

- [x] `matrix2d matrix2d_inverse (matrix2d A, double p)`
	- scale(1 / determinate(A), adjoint(A)),
	where determinate(A) != 0 at precision p,
	otherwise inverse = 0

Scalar, Scalar-Vector, and Scalar-Matrix Operations:

- [x] `bool d_equals (double a, double b, double p)`
	- a == b,
	at precision p

- [x] `vector2d vector2d_scale (double r, vector2d a)`
	- vector(r * a1, r * a2)

- [x] `matrix2d matrix2d_scale (double r, matrix2d A)`
	- matrix(r * A11, r * A12, r * A21, r * A22)

Vector-Vector and Matrix-Vector Operations:

- [x] `bool vector2d_equals (vector2d a, vector2d b, double p)`
	- a1 == b1 && a2 == b2,
	at precision p

- [x] `vector2d vector2d_add (vector2d a, vector2d b)`
	- vector(a1 + b1, a2 + b2)

- [x] `double vector2d_dot (vector2d a, vector2d b)`
	- (a1 * b1) + (a2 * b2)

- [x] `double vector2d_theta (vector2d a, vector2d b, double p)`
	- invcos(dot(a, b) / (length(a) * length(b))),
	where (length(a) * length(b)) != 0 at precision p,
	otherwise theta = 0

- [x] `double vector2d_cross (vector2d a, vector2d b, double theta)`
	- length(a) * length(b) * sin(theta),
	where theta is the angle from a to b

- [x] `vector2d matrixvector2d_dot (matrix2d A, vector2d b)`
	- vector(dot(A1, b), dot(A2, b))

Matrix-Matrix Operations:

- [x] `bool matrix2d_equals (matrix2d A, matrix2d B, double p)`
	- A11 == B11 && A12 == B12 && A21 == B21 && A22 == B22,
	at precision p

- [x] `matrix2d matrix2d_add (matrix2d A, matrix2d B)`
	- matrix(A11 + B11, A12 + B12, A21 + B21, A22 + B22)

- [x] `matrix2d matrix2d_dot (matrix2d A, matrix2d B)`
	- matrix(dot(A1, T1), dot(A1, T2), dot(A2, T1), dot(A2, T2)),
	where T = transpose(B)

## utilx.h

- [x] int types at least 8, 16, 32, or 64 bits.
	may be signed `int#` or unsigned `uint#`, where `#` is the number of bits.
	easier to write and more readable than the types in `stdint.h`

- [x] `void here ()`
	- prints the file name and line number in the same style as gcc errors.
	easier to write and more readable than the equivalent code:
	`printf("%s:%d\n", __FILE__, __LINE__);`

- [x] `void* delete (void* ptr)`
	- frees ptr if not null, else does nothing. returns null.
	may be called many times, like c++'s delete.

- [x] `void* alloc (void* ptr, int64 n)`
	- reallocs ptr if n > 0, else deletes ptr. returns new address or null.
	program exits if a memory error ocurrs, as expected in modern languages.

- [x] `void* alloc_no_exit (void* ptr, int64 n)`
	- alloc without exit on memory error, as expected for the original realloc.

## renderx.h

## musicx.h

## worldx.h


