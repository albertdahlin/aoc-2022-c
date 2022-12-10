MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables
SRC=$(wildcard src/*.c)
TEST_SRC=$(wildcard test/*.c)
OBJ_DEV=$(patsubst src/%.c,build/%.dev.o,$(SRC))
OBJ_OPT=$(patsubst src/%.c,build/%.opt.o,$(SRC))
TEST_OUT=$(patsubst test/%.c,build/%.test,$(TEST_SRC))
ARGS?=

dev: build build/dev

opt: build build/opt

build/dev: $(OBJ_DEV)
	@gcc $^ -o $@

test/%: build/%.test

test: $(TEST_OUT)

build/opt: $(OBJ_OPT)
	gcc $^ -O3 -o $@

build/%.dev.o: src/%.c
	gcc -c -Wall -ggdb $< -o $@

build/%.opt.o: src/%.c
	gcc -c -Wall -O3 $< -o $@

build/%.test: test/%.c src/%.c
	gcc -Wall -Isrc -ggdb $< -o $@
	$@


build:
	mkdir build

clean:
	rm build/*
