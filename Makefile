
# Copyright 2022-2023 Nathanael Specht

NG_SRC = $(wildcard ng/*.c)
DEMO_SRC = $(wildcard demo/*.c)
TEST_SRC = $(wildcard test/*.c)

ifeq ($(OS),Windows_NT)
MAKE = mingw32-make
COMPILE = gcc -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
LIB = -lmingw32 -lSDL2main -lSDL2 -lm
LIB_INCLUDE = -Isdl/mingw/include/SDL2 -Lsdl/mingw/lib

else
MAKE = make
COMPILE = gcc -O0 -Wall -Wno-unused-variable
LIB = -lSDL2 -lm
LIB_INCLUDE = -Isdl/ubuntu/include -Lsdl/ubuntu/lib

endif

main:
	$(COMPILE) demo.c $(DEMO_SRC) $(NG_SRC) -o app -Idemo -Ing $(LIB_INCLUDE) $(LIB)

test:
	$(COMPILE) test.c $(TEST_SRC) $(NG_SRC) -o app -Itest -Ing $(LIB_INCLUDE) $(LIB)

help:
	@echo "Engie (ng)"
	@echo ""
	@echo "  Type '$(MAKE)' to compile the demo,"
	@echo "  or '$(MAKE) test' to compile the test,"
	@echo "  or '$(MAKE) help' to display this message again."
	@echo ""
	@echo "Copyright 2022-2023 Nathanael Specht"


