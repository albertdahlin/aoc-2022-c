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
|  [1] |         16µs |
|  [2] |          6µs |
|  [3] |         23µs |
|  [4] |         22µs |
|  [5] |         14µs |
|  [6] |         20µs |
|  [7] |         22µs |
|  [8] |         92µs |
|  [9] |        438µs |
| [10] |          3µs |
| [11] |      4,549µs |
| [12] |        707µs |
| [13] |        181µs |
| [14] |      4,760µs |
| [15] |    264,395µs |
| [18] |        981µs |
| [19] |    674,527µs |
| [20] |          0µs |
| [24] |    229,601µs |
|  Sum |  1,180,356µs |

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

