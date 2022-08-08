
#ifeq ($(OS),Windows_NT)
#
#TARGET = tisWindows
#COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
#SOURCE = main.c
#LIBRARY = -IC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\include\SDL2 \
#	-LC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\lib \
#	-lmingw32 -lSDL2main -lSDL2 -lm
#
#else
#
#TARGET = tisUbuntu
#COMPILE = gcc -O0 -Wall -Wno-unused-variable
#SOURCE = main.c
#LIBRARY = -I/usr/include/SDL2 -L/usr/lib \
#	-lSDL2 -lm
#
#endif

#all:
#	$(COMPILE) $(SOURCE) -o $(TARGET) $(LIBRARY)

COMPILE_UBUNTU = gcc -O0 -Wall -Wno-unused-variable
SOURCE_UBUNTU = 
LIBRARY_UBUNTU = -I/usr/include/SDL2 -L/usr/lib \
	-lSDL2 -lm

COMPILE_WINDOWS = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
SOURCE_WINDOWS = 
LIBRARY_WINDOWS = -IC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\include\SDL2 \
	-LC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\lib \
	-lmingw32 -lSDL2main -lSDL2 -lm

help:
	@echo "Trees in Space Engine (TIS)"
	@echo "To compile TIS, choose:"
	@echo "    'make ubuntu' to produce tisUbuntu"
	@echo "    'mingw32-make windows' to produce tisWindows.exe"
	@echo "To test your environment, choose:"
	@echo "    'make helloUbuntu' to produce hello"
	@echo "    'mingw32-make helloWindows' to produce hello.exe"
#TODO
#	@echo "To compile the TIS test suite, choose:"
#	@echo "    'make testUbuntu' to produce test"
#	@echo "    'mingw32-make testWindows' to produce test.exe"

ubuntu:
	$(COMPILE_UBUNTU) main.c $(SOURCE_UBUNTU) -o tisUbuntu $(LIBRARY_UBUNTU)

windows:
	$(COMPILE_WINDOWS) main.c $(SOURCE_WINDOWS) -o tisWindows $(LIBRARY_WINDOWS)

helloUbuntu:
	$(COMPILE_UBUNTU) hello.c -o hello $(LIBRARY_UBUNTU)

helloWindows:
	$(COMPILE_WINDOWS) hello.c -o hello $(LIBRARY_WINDOWS)

#TODO
#testUbuntu:
#	$(COMPILE_UBUNTU) test.c $(SOURCE_UBUNTU) -o test $(LIBRARY_UBUNTU)
#
#testWindows:
#	$(COMPILE_WINDOWS) test.c $(SOURCE_WINDOWS) -o test $(LIBRARY_WINDOWS)

