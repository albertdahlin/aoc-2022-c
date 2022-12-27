# Advent of code 2022

My goal here is to execute all 25 solutions in less than 1s total time.

## Assumptions & rules:

- Input must be used as the string is given to you by AOC. No pre-processing allowed.
- You can assume the input is correctly formated and that it always ends with a new line.
- Your program must print the correct result from other peoples input aswell (cheater).
- Result from both part 1 and part 2 must be printed.
- Times can be averaged over multiple runs.
- All bets are off when it comes to hardware. Use your quantum computer, ASIC, FPGA, graphics card or whatever fancy thing you have.


## Progress

Here are some timings from my old trusty 2012 i7 (3770K) desktop.

|  Day |     Time     |
| ---: | -----------: |
|  [1] |         31µs |
|  [2] |         17µs |
|  [3] |         25µs |
|  [4] |         29µs |
|  [5] |         20µs |
|  [6] |         25µs |
|  [7] |         34µs |
|  [8] |        108µs |
|  [9] |        562µs |
| [10] |          5µs |
| [11] |      6,166µs |
| [12] |     23,352µs |
| [13] |        216µs |
| [14] |      5,165µs |
| [15] |    263,944µs |
| [18] |      1,475µs |
| [19] |    667,913µs |
| [24] |    232,987µs |
|  Sum |  1,202,077µs |

## Run it

I've only tested this on Linux with GCC.
I leave no guarantees that it will work on other systems.

Compile
```
make dev # development
make opt # optimized build
```

Run
```
./build/opt
```
You can put your input in the `input/dayN.txt` files.

Run every solution 10,000 times and average the execution time.
This is how I measure the times in the table above.
```
./build/opt -r 10000 -m
```

[1]: src/Day01.c
[2]: src/Day02.c
[3]: src/Day03.c
[4]: src/Day04.c
[5]: src/Day05.c
[6]: src/Day06.c
[7]: src/Day07.c
[8]: src/Day08.c
[9]: src/Day09.c
[10]: src/Day10.c
[11]: src/Day11.c
[12]: src/Day12.c
[13]: src/Day13.c
[14]: src/Day14.c
[15]: src/Day15.c
[18]: src/Day18.c
[19]: src/Day19.c
[24]: src/Day24.c

