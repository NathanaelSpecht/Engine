# Obtain

TIS can be cloned from GitHub using:
`git clone https://github.com/NathanaelSpecht/TreesInSpaceEngine`
On Windows, this requires git is installed.

Alternatively, download TIS as a zip file from GitHub:
1. Open the TIS GitHub repository in a browser, [here](https://github.com/NathanaelSpecht/TreesInSpaceEngine).

2. Click the green "Code" button and select "Download ZIP".

3. Unzip the file to wherever you want.

# Compile

If you wish to compile TIS yourself, follow the instructions below for your OS.

### Dependencies

##### Environment

On Ubuntu, you'll need these:
- [GCC](https://gcc.gnu.org). In terminal, type `sudo apt install gcc`.
- [GNU Make](https://gnu.org/software/make). In terminal, type `sudo apt install make`.

On Windows, you'll need these:
- [MinGW-w64](https://mingw-w64.org). Download and install, following the instructions on the site.
- After installing mingw, add the folder containing mingw32-make.exe to your PATH.
- There may be more steps as Windows changes. Use your best judgement.

##### Libraries

TIS depends on the following software libraries to compile:
- [SDL2](https://libsdl.org)
- [Lua](http://lua.org/home.html)

You may need to edit the makefile so it looks in the correct locations for the libraries.

##### Test Your Setup

At this point, we recommend you compile and run the included test program to test your setup:

1. Open the terminal/Command Prompt and navigate to the root directory of the project.

2. Type `make helloUbuntu` on Ubuntu, or `mingw32-make helloWindows` on Windows.
If everything is installed correctly, this should produce a program named "hello".
If there's something wrong with your install, or the makefile is looking for libraries in the wrong places, then make or gcc should tell you, and hello will fail to compile.

3. Run hello using `./hello`.
If you are set up correctly, then hello will print "hello" and exit.
If hello thinks something is wrong, it will attempt to tell you with an "ERROR" message and exit.

If hello prints "hello", then any errors you get while compiling or running TIS are the fault of TIS and not your environment.
**TIS is still in early development, so expect compilation errors from time to time**

### Run Unit Tests

If you wish, you may compile and run the included unit tests:

1. Type `make testUbuntu` on Ubuntu, or `mingw32-make testWindows` on Windows.
If all the code internal to TIS is free of errors, this should produce a program named "test".

2. Run test using `./test`.
Test will conduct unit tests on every function internal to TIS.
If all the code internal to TIS works as intended, test should print a "pass" message for every unit test.
If test thinks something is wrong, it will attempt to tell you with a "FAILURE" message and continue to the next test.
Groups of tests that depend on each other will be labeled as such in the output.

If TIS passes all unit tests, then it is ready to compile for real.

### Supported Operating Systems

To compile TIS, type `make ubuntu` on Ubuntu, or `mingw32-make windows` on Windows.
If TIS is free of errors, this should produce a program named "engine".

### Other

We intend to support only Ubuntu and Windows. 

That said, TIS is organized such that only two files need to be implemented to get it working on your OS.
os.h contains the cross-platform API for functions that use OS-specific code.
Implement this in your-os-here.c and add an option for your OS in the makefile to compile it with the remainder of the project.
You may also need to rewrite the makefile in a different format (for example, CMakeLists) for the compilation environment that works on your OS.

# Install

If you wish to use TIS as a portable tool, then simply run the software.
Everything TIS needs in order to operate is included in the project.

If you want a desktop shortcut, then follow the instructions below for your OS:

### Ubuntu

**TODO instructions to create desktop shortcut on Ubuntu**

### Windows

1. Right-click engine.exe and choose "Create Shortcut".

2. Cut and paste the shortcut to your desktop.

