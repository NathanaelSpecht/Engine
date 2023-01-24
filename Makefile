
# Copyright 2022-2023 Nathanael Specht

ifeq ($(OS),Windows_NT)
COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
YOUR_SOURCE = $(wildcard src/*.c)
NG_SOURCE = $(wildcard ng/*.c)
YOUR_INCLUDE = -Isrc
NG_INCLUDE = -Ing -Isdl/windows/mingw/include/SDL2 -Lsdl/windows/mingw/lib
LIBRARY = -lmingw32 -lSDL2main -lSDL2 -lm

else
COMPILE = gcc -O0 -Wall -Wno-unused-variable
YOUR_SOURCE = $(wildcard src/*.c)
NG_SOURCE = $(wildcard ng/*.c)
YOUR_INCLUDE = -Isrc
NG_INCLUDE = -Ing -Isdl/ubuntu/include -Lsdl/ubuntu/lib
LIBRARY = -lSDL2 -lm

endif

main:
	$(COMPILE) main.c $(YOUR_SOURCE) $(NG_SOURCE) -o app $(YOUR_INCLUDE) $(NG_INCLUDE) $(LIBRARY)

help:
	@echo "engine (ng)"
	@echo ""
	@echo "  command:     description:"
	@echo "  make         compile engine with your code. creates app."
	@echo "  make help    display this message."
	@echo ""
	@echo "Copyright 2022-2023 Nathanael Specht"

