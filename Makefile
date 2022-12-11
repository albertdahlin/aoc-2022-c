MAKEFLAGS += --no-builtin-rules
CFLAGS=
SRC=$(wildcard src/*.c)
TEST_SRC=$(wildcard test/*.c)
OBJ_DEV=$(patsubst src/%.c,build/%.dev.o,$(SRC))
OBJ_OPT=$(patsubst src/%.c,build/%.opt.o,$(SRC))
TEST_OUT=$(patsubst test/%.c,build/%.test,$(TEST_SRC))
ARGS?=

dev: build build/dev

opt: build build/opt

build/dev: $(OBJ_DEV)
	@$(CC) $^ -o $@

test: $(TEST_OUT)

build/opt: $(OBJ_OPT)
	$(CC) $(CFLAGS) -O3 $^ -o $@

build/%.dev.o: src/%.c
	$(CC) $(CFLAGS) -c -ggdb $< -o $@

build/%.opt.o: src/%.c
	$(CC) $(CFLAGS) -Wall -c -O3 $< -o $@

build/%.test: test/%.c src/%.c
	$(CC) $(CFLAGS) -Isrc -ggdb $< -o $@
	$@


build:
	mkdir build

clean:
	rm build/*
