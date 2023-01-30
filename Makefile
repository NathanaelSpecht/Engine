
# Copyright 2022-2023 Nathanael Specht

ifeq ($(OS),Windows_NT)
APP = -o app
COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
MAIN = main.c
SRC = $(wildcard src/*.c)
NG = $(wildcard ng/*.c)
LIB = -lmingw32 -lSDL2main -lSDL2 -lm
SRC_INCLUDE = -Isrc
NG_INCLUDE = -Ing
LIB_INCLUDE = -Isdl/windows/mingw/include/SDL2 -Lsdl/windows/mingw/lib

else
APP = -o app
COMPILE = gcc -O0 -Wall -Wno-unused-variable
MAIN = main.c
SRC = $(wildcard src/*.c)
NG = $(wildcard ng/*.c)
LIB = -lSDL2 -lm
SRC_INCLUDE = -Isrc
NG_INCLUDE = -Ing
LIB_INCLUDE = -Isdl/ubuntu/include -Lsdl/ubuntu/lib

endif

main:
	$(COMPILE) $(MAIN) $(SRC) $(NG) $(APP) $(SRC_INCLUDE) $(NG_INCLUDE) $(LIB_INCLUDE) $(LIB)

help:
	@echo "Engine 'engie' (ng)"
	@echo ""
	@echo "  Type 'make' to compile engie with your code,"
	@echo "  or 'make help' to display this message."
	@echo ""
	@echo "Copyright 2022-2023 Nathanael Specht"


