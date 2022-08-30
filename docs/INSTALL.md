# Trees In Space (TIS) Game Engine

TIS can be cloned from GitHub using:
`git clone https://github.com/NathanaelSpecht/TreesInSpaceEngine`
On Windows, this requires git to be installed.

Alternatively, download TIS as a zip file from GitHub:
1. Open the TIS GitHub repository in a browser, 
[here](https://github.com/NathanaelSpecht/TreesInSpaceEngine).
2. Click the green "Code" button and select "Download ZIP".
3. Unzip the file wherever you want.

## Dependencies

TIS is a set of functions, and not a complete program.
You'll need to install some software before you can compile TIS with your own 
code.

On Linux, you'll need these:
- [GCC](https://gcc.gnu.org). In terminal, type `sudo apt install gcc`.
- [GNU Make](https://gnu.org/software/make). In terminal, type 
`sudo apt install make`.

On Windows, you'll need these:
- [MinGW-w64](https://mingw-w64.org). Download and install, following the 
instructions on the site.
- After installing mingw, add the folder containing mingw32-make.exe to your 
PATH.
- There may be more steps as Windows and MinGW change. Use your best judgement.

TIS depends on the following software libraries to compile:
- [SDL2](https://libsdl.org)

You may need to edit the `INCLUDE` variable in TIS's `Makefile` so the compiler 
looks in the correct location for each library.

## Test Your Environment

To test your development environment, use the included `hello.c` test program:

Compile with `make hello` then run with `./hello`.

Hello will compile if your compilation environment is setup correctly.
If you want, you can run hello to print "hello" to stdout.

If hello compiles, then your environment is ready for TIS.

## Test TIS

To test TIS, use the included `test.c` test program:

Compile with `make test` then run with `./test`.

Test will conduct unit tests on every function in TIS.
Passing tests will print "pass" to stdout.
Failing tests will print "FAIL" to stdout.

If TIS passes all unit tests, then it is ready for use in your projects.

## Using TIS in Your Project

To use TIS in your own projects, copy TIS's `LICENSE` file and `src/` files into 
your project folder, and compile TIS's source code along with your own code.
Use the included `Makefile` as a reference for compiling on multiple platforms.

Refer to `docs/API.md` for an overview of the functions in TIS.
I try to keep the API descriptions up-to-date with `src/`.

## Compile TIS on Linux and Windows

TIS is a collection of functions, **not** a complete program.
The included `main.c` program is an example meant to showcase some of the 
functionality in TIS.
**main.c is not yet complete and probably won't compile.**
To compile TIS along with this example, type `make` then run with `./app`.

## Compile TIS on Other Platforms

I intend to support TIS only for Linux and Windows.

That said, TIS is organized such that only two files need to be changed to 
get it working on your platform.
The `os.h` file contains the cross-platform API for functions that use 
platform-specific code.
Implement this interface in `your-platform.c` (like the included `linux.c` and 
`windows.c`) and add an option for your platform in TIS's `Makefile` to compile 
it with the remainder of the project.
Then compile and run the included unit tests until all tests are passing on 
your platform.

If you have a different compilation environment, you'll need to change the 
`Makefile` to work in that environment. Good luck!

