# Advent of code 2022

My goal here is to execute all 25 solutions in less than 1 second total time.

Assumptions & rules:
- Assume input is correct and always ends with a new line.
- Assume a modern x86 CPU, use any SIMD if needed.
- Only use single threaded code.
- Compiler is gcc, optimizations (-O3) and builtins are allowed.
- Times should be reliable any input given by AOC.

Progress so far:
- [Day 1](src/Day1.c) < 50µs
- [Day 2](src/Day2.c) < 50µs
- [Day 3](src/Day3.c) < 50µs
- [Day 4](src/Day4.c) < 50µs

```
git submodule init
git submodule update
make optimize
```
