
dev: build build/dev
	build/dev

optimize: build build/optimized
	build/optimized

build/dev: src/main.c src/*.c
	gcc -Wall -g $< -o $@

build/optimized: src/main.c src/*.c
	gcc -msse4.2 -Wall -O3 $< -o $@


build/day-%: test/day%.c src/Day%.c
	gcc -Wall -g -Isrc $< -o $@
	$@


build:
	mkdir build

clean:
	rm build/*
