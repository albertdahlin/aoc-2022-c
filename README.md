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

|  Day |    Time    |
| ---: | ---------: |
|  [1] |       15µs |
|  [2] |        6µs |
|  [3] |       20µs |
|  [4] |       17µs |
|  [5] |       10µs |
|  [6] |       16µs |
|  [7] |       12µs |
|  [8] |       64µs |
|  [9] |      298µs |
| [10] |        1µs |
| [11] |    4,170µs |
| [12] |   20,409µs |
| [13] |      187µs |
| [14] |    4,847µs |
| [15] |  272,197µs |
| [18] |      991µs |
| [19] |  546,479µs |
|  Sum |  849,737µs |


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

[1]: src/Day1.c
[2]: src/Day2.c
[3]: src/Day3.c
[4]: src/Day4.c
[5]: src/Day5.c
[6]: src/Day6.c
[7]: src/Day7.c
[8]: src/Day8.c
[9]: src/Day9.c
[10]: src/Day10.c
[11]: src/Day11.c
[12]: src/Day12.c
[13]: src/Day13.c
[14]: src/Day14.c
[15]: src/Day15.c
[18]: src/Day18.c
[19]: src/Day19.c

