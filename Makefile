MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables
SRC=$(wildcard src/*.c)
TEST_SRC=$(wildcard test/*.c)
OBJ_DEV=$(patsubst src/%.c,build/%.dev.o,$(SRC))
OBJ_OPT=$(patsubst src/%.c,build/%.opt.o,$(SRC))
TEST_OUT=$(patsubst test/%.c,build/%.test,$(TEST_SRC))
DAY?=

dev: build build/dev
	build/dev $(DAY)

optimize: build build/optimized
	@build/optimized

build/dev: $(OBJ_DEV)
	@gcc $^ -o $@

test/%: build/%.test

test: $(TEST_OUT)


build/optimized: $(OBJ_OPT)
	gcc $^ -O3 -o $@

build/%.dev.o: src/%.c
	gcc -c -Wall -g $< -o $@

build/%.opt.o: src/%.c
	gcc -c -msse4.2 -Wall -O3 $< -o $@

build/%.test: test/%.c src/%.c
	@gcc -Wall -Isrc -g $< -o $@
	@$@


build:
	mkdir build

clean:
	rm build/*
