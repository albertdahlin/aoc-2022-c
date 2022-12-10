# Advent of code 2022

My goal here is to execute all 25 solutions in less than 1ms total time.

## Assumptions & rules:

- Input must be used as the string is given to you by AOC. No pre-processing allowed.
- You can assume the input is correctly formated and that it always ends with a new line.
- Your program must print the correct result from other peoples input aswell (cheater).
- Result from both part 1 and part 2 must be printed.
- Times can be averaged over multiple runs.
- All bets are off when it comes to hardware. Use your quantum computer, ASIC, FPGA, graphics card or whatever fancy thing you have.


## Progress

Here are some timings from my old trusty 2012 i7 (3770K) desktop.

|  Day |    Time |
| ---: | ------: |
|  [1] |    10µs |
|  [2] |     4µs |
|  [3] |    15µs |
|  [4] |    13µs |
|  [5] |     8µs |
|  [6] |    15µs |
|  [7] |    12µs |
|  [8] |    57µs |
|  [9] |   303µs |
| [10] |     1µs |
|  Sum |   438µs |

## Run it

- I've only tested this on Linux with GCC. I leave no guarantees that it will work on other systems.

Compile
```
make opt
```
Run
```
./build/opt
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
