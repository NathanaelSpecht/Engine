
# Copyright 2022-2023 Nathanael Specht

NG_CPP = $(wildcard ng/*.cpp)
DEMO_CPP = $(wildcard demo/*.cpp)
TEST_CPP = $(wildcard test/*.cpp)

NG_C = $(wildcard archive/ng-c/*.c)
DEMO_C = $(wildcard archive/demo-c/*.c)
TEST_C = $(wildcard archive/test-c/*.c)

ifeq ($(OS),Windows_NT)
MAKE = mingw32-make
FLAGS = -O0 -Wall -Wno-unused-variable -Wl,-subsystem,windows
LIB = -lmingw32 -lSDL2main -lSDL2 -lm
LIB_INCLUDE = -Isdl/mingw/include/SDL2 -Lsdl/mingw/lib

else
MAKE = make
FLAGS = -O0 -Wall -Wno-unused-variable
LIB = -lSDL2 -lm
LIB_INCLUDE = -Isdl/ubuntu/include -Lsdl/ubuntu/lib

endif

main:
	g++ $(FLAGS) demo.cpp $(DEMO_CPP) $(NG_CPP) -o app -Idemo -Ing $(LIB_INCLUDE) $(LIB)

test:
	g++ $(FLAGS) test.cpp $(TEST_CPP) $(NG_CPP) -o app -Itest -Ing $(LIB_INCLUDE) $(LIB)

c:
	gcc $(FLAGS) archive/demo-c.c $(DEMO_C) $(NG_C) -o app -Iarchive/demo-c -Iarchive/ng-c $(LIB_INCLUDE) $(LIB)

testc:
	gcc $(FLAGS) archive/test-c.c $(TEST_C) $(NG_C) -o app -Iarchive/test-c -Iarchive/ng-c $(LIB_INCLUDE) $(LIB)

help:
	@echo "Engie (ng)"
	@echo ""
	@echo "  Type '$(MAKE)' to compile the C++ demo,"
	@echo "  or '$(MAKE) test' to compile the C++ test,"
	@echo "  or '$(MAKE) c' to compile the C demo (version 0.0.1),"
	@echo "  or '$(MAKE) testc' to compile the C test (version 0.0.1),"
	@echo "  or '$(MAKE) help' to display this message again."
	@echo ""
	@echo "Copyright 2022-2023 Nathanael Specht"


