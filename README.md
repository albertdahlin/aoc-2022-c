# Advent of code 2022

My goal here is to execute all 25 solutions in less than 1ms total time.

Assumptions & rules:
- Input must be used as the string given by AOC. No pre-processing allowed.
- Assume input is correct and that it always ends with a new line.
- Assume a modern x86 CPU, use any SIMD if needed.
- Only use single threaded code.
- Compiler is gcc, optimizations (-O3) and builtins are allowed.
- Result from both part 1 and part 2 must be printed.
- Times are averaged over multiple runs.

Progress so far:
- [Day 1](src/Day1.c) ~ 9µs
- [Day 2](src/Day2.c) ~ 4µs
- [Day 3](src/Day3.c) ~ 15µs
- [Day 4](src/Day4.c) ~ 14µs
- [Day 5](src/Day5.c) ~ 9µs
- [Day 6](src/Day6.c) ~ 7µs
- [Day 7](src/Day7.c) ~ 13µs

Total time so far: 70µs
```
make optimize
```
