
# Makefile -- Compiles the 'TIS' game engine library
# version 0.1, 2022 August 30

ifeq ($(OS),Windows_NT)
COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
#TIS_SOURCE = tis\tis_string.c \
#	tis\tis_convert.c \
#	tis\tis_file.c
SOURCE = $(wildcard src/*.c)
TIS_SOURCE = $(wildcard tis/*.c)
#LIBRARY = -Isrc -IC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\include\SDL2 \
#	-LC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\lib \
#	-lmingw32 -lSDL2main -lSDL2 -lm
INCLUDE = -Isrc
TIS_INCLUDE = -Itis -Isdl2/x86_64-w64-mingw32/include/SDL2 \
	-Lsdl2/x86_64-w64-mingw32/lib
LIBRARY = -lmingw32 -lSDL2main -lSDL2 -lm

else
COMPILE = gcc -O0 -Wall -Wno-unused-variable
#TIS_SOURCE = tis/tis_string.c \
#	tis/tis_convert.c \
#	tis/tis_file.c
SOURCE = $(wildcard src/*.c)
TIS_SOURCE = $(wildcard tis/*.c)
#LIBRARY = -Isrc -I/usr/include/SDL2 -L/usr/lib \
#	-lSDL2 -lm
INCLUDE = -Isrc
TIS_INCLUDE = -Itis -Isdl2/x86_64-w64-mingw32/include/SDL2 \
	-Lsdl2/x86_64-w64-mingw32/lib
LIBRARY = -lSDL2 -lm

endif

main:
	$(COMPILE) main.c $(SOURCE) $(TIS_SOURCE) -o app \
	$(INCLUDE) $(TIS_INCLUDE) $(LIBRARY)

test:
	$(COMPILE) test.c $(TIS_SOURCE) -o test $(TIS_INCLUDE) $(LIBRARY)

hello:
	$(COMPILE) hello.c -o hello $(TIS_INCLUDE) $(LIBRARY)

help:
	@echo "'TIS' game engine library"
	@echo "version 0.1, 2022 September 12"
	@echo ""
	@echo "  Command       App Name  Description"
	@echo "  'make'        'app'     Compile TIS with your project."
	@echo "  'make test'   'test'    Unit tests."
	@echo "  'make hello'  'hello'   Compilation environment test."
	@echo "  'make help'             Display this message."
	@echo ""	
	@echo "Copyright (C) 2022 Nathanael Specht"
	@echo "Refer to LICENSE for licensing."

