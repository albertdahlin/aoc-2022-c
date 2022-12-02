
dev: build build/dev
	build/dev

optimize: build build/optimized
	build/optimized

build/dev: src/main.c src/*.c lib/src/*.h
	gcc -Wall -g -Ilib/src $< -o $@

build/optimized: src/main.c src/*.c
	gcc -Wall -O3 -Ilib/src $< -o $@


build/day-%: test/day%.c src/Day%.c
	gcc -Wall -g -Isrc -Ilib/src $< -o $@
	$@


build:
	mkdir build

clean:
	rm build/*
