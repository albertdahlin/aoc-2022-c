# Advent of code 2022

My goal here is to execute all 25 solutions in less than 1 second total time.

Assumptions & rules:
- Input must be used as the string given by AOC.
- Assume input is correct and that it always ends with a new line.
- Program must not segfault if input is wrong.
- Assume a modern x86 CPU, use any SIMD if needed.
- Only use single threaded code.
- Compiler is gcc, optimizations (-O3) and builtins are allowed.
- Times should be reliable for any input given by AOC.
- Both part 1 and part 2 must be printed.

Progress so far:
- [Day 1](src/Day1.c) < 20µs
- [Day 2](src/Day2.c) < 10µs
- [Day 3](src/Day3.c) < 40µs
- [Day 4](src/Day4.c) < 40µs
- [Day 5](src/Day5.c) < 30µs
- [Day 6](src/Day6.c) < 30µs

```
make optimize
```
