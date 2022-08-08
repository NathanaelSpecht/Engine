
#ifeq ($(OS),Windows_NT)
#
#COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
#SOURCE = 
#LIBRARY = -IC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\include\SDL2 \
#	-LC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\lib \
#	-lmingw32 -lSDL2main -lSDL2 -lm
#
#else
#
#COMPILE = gcc -O0 -Wall -Wno-unused-variable
#SOURCE = 
#LIBRARY = -I/usr/include/SDL2 -L/usr/lib \
#	-lSDL2 -lm
#
#endif

#engine:
#	$(COMPILE) main.c $(SOURCE) -o engine $(LIBRARY)
#
#help:
#	@echo "Trees in Space Engine (TIS)"
#	@echo "Type 'make' to compile TIS, or"
#	@echo "     'make help' for this help message, or"
#	@echo "     'make hello' to test your environment, or"
#	@echo "     'make test' to compile unit tests"
#	@echo "On Windows, use 'mingw32-make' instead of 'make'
#
#hello:
#	$(COMPILE) hello.c -o hello $(LIBRARY)
#
#test:
#	$(COMPILE) test.c $(SOURCE) -o test $(LIBRARY)

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
	@echo "To compile TIS:"
	@echo "    'make ubuntu' or 'mingw32-make windows'"
	@echo "To test your environment:"
	@echo "    'make helloUbuntu' or 'mingw32-make helloWindows'"
#TODO
#	@echo "To compile unit tests:"
#	@echo "    'make testUbuntu' or 'mingw32-make testWindows'"

ubuntu:
	$(COMPILE_UBUNTU) main.c $(SOURCE_UBUNTU) -o engine $(LIBRARY_UBUNTU)

windows:
	$(COMPILE_WINDOWS) main.c $(SOURCE_WINDOWS) -o engine $(LIBRARY_WINDOWS)

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

