
# Copyright (C) 2022 Nathanael Specht

ifeq ($(OS),Windows_NT)
COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
YOUR_SOURCE = $(wildcard src/*.c)
MY_SOURCE = $(wildcard engine/*.c)
YOUR_INCLUDE = -Isrc
MY_INCLUDE = -Iengine -Isdl2/x86_64-w64-mingw32/include/SDL2 \
	-Lsdl2/x86_64-w64-mingw32/lib
LIBRARY = -lmingw32 -lSDL2main -lSDL2 -lm

else
COMPILE = gcc -O0 -Wall -Wno-unused-variable
YOUR_SOURCE = $(wildcard src/*.c)
MY_SOURCE = $(wildcard engine/*.c)
YOUR_INCLUDE = -Isrc
MY_INCLUDE = -Iengine -Isdl2/x86_64-w64-mingw32/include/SDL2 \
	-Lsdl2/x86_64-w64-mingw32/lib
LIBRARY = -lSDL2 -lm

endif

main:
	$(COMPILE) main.c $(YOUR_SOURCE) $(MY_SOURCE) -o app \
	$(YOUR_INCLUDE) $(MY_INCLUDE) $(LIBRARY)

test:
	$(COMPILE) test.c $(MY_SOURCE) -o test $(MY_INCLUDE) $(LIBRARY)

hello:
	$(COMPILE) hello.c -o hello $(MY_INCLUDE) $(LIBRARY)

help:
	@echo "My game engine"
	@echo ""
	@echo "  Command       App Name  Description"
	@echo "  'make'        'app'     Compile my engine with your project."
	@echo "  'make test'   'test'    Test my game engine."
	@echo "  'make hello'  'hello'   Test your compilation environment."
	@echo "  'make help'             Display this message."
	@echo ""
	@echo "Copyright (C) 2022 Nathanael Specht"
	@echo "Refer to README for more information."

