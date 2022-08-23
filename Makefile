
ifeq ($(OS),Windows_NT)
COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
SOURCE = tis\tis.c
LIBRARY = -Itis -IC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\include\SDL2 \
	-LC:\Libraries\SDL2\dev\SDL2-2.0.22\x86_64-w64-mingw32\lib \
	-lmingw32 -lSDL2main -lSDL2 -lm

else
COMPILE = gcc -O0 -Wall -Wno-unused-variable
SOURCE = tis/tis.c
LIBRARY = -Itis -I/usr/include/SDL2 -L/usr/lib \
	-lSDL2 -lm

endif

app:
	$(COMPILE) main.c $(SOURCE) -o app $(LIBRARY)

hello:
	$(COMPILE) hello.c -o hello $(LIBRARY)

test:
	$(COMPILE) test.c $(SOURCE) -o test $(LIBRARY)

help:
	@echo "Trees In Space Engine (TIS) game engine functions."
	@echo ""
	@echo "  Command       App Name  Description"
	@echo "  'make'        'app'     Example app implemented with TIS."
	@echo "  'make test'   'test'    Unit tests."
	@echo "  'make hello'  'hello'   Compilation environment test."
	@echo "  'make help'             Display this message."
	@echo ""
	@echo "  On Windows, use 'mingw32-make' instead of 'make'."
	@echo ""
	@echo "Copyright (C) 2022  Nathanael Specht"

