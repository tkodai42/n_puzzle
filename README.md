# n_puzzle



## USAGE

### SYNOPSIS

     n_puzzle [-...] [file]

### DESCRIPTION

     The options are as follows:

     -c    calculation: heuristic
     -d    debug: display board
     -f1   The Manhattan-distance
     -f2   Improved Manhattan-distance
     -f3   Correct number of pieces
     -f4   Euclidean-distance
     -f5   original
     -g    greedy search
     -h    HELP
     -n    omit ordered sequence of status
     -o    use open/close list
     -p    play n_puzzle!!!
     -u    Uniform Cost
     -v    visualize

## DETAILS

### Heauristic Functions

- function for estimating the cost of the cheapest path from current state to the goal

| heauristics | option | calculation | detail |
| --- | --- | --- | --- | 
| Manhattan-distance | -f1 | `abs(x1 - x2) + abs(y1 - y2)` | <img width="383" alt="Capture d’écran 2023-02-13 à 00 15 37" src="https://user-images.githubusercontent.com/60470877/218319546-202f119d-b3b0-4a1a-96f5-32b0b1636e5c.png"> |
| Improved Manhattan-distance | -f2 | `abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2)` | |
| Correct number of pieces | -f3 | <img width="127" alt="Capture d’écran 2023-02-13 à 11 08 42" src="https://user-images.githubusercontent.com/60470877/218354980-727c2324-4c1a-42c9-b989-1c7fdf53c04d.png">
 | |
| Euclidean distance | -f4 | `sqrt( abs(x1-x2) * abs(x1-x2) + abs(y1-y2) * abs(y1-y2) )` | <img width="252" alt="Capture d’écran 2023-02-12 à 23 52 49" src="https://user-images.githubusercontent.com/60470877/218318383-abb16345-700b-44bd-8f69-6ca5fa5d0f61.png"> |
| Original | -f5 |  | |

### Algorithms

- g(n) : the cost of the path from the start node to n
- h(n) : a heuristic function

| algorithm | option | calculation | detail |
| --- | --- | --- | --- | 
| A* search algorithm  |  | `f(n) = g(n) + h(n)` | consider both cost and heuristic |
| Greedy search | -g | `f(n) = h(n)` | only consider heuristic |
| Uniform cost search | -u | `f(n) = g(n)` | only consider cost |

## RUN
    make

    ARG=${FILE_NAME}; ./generator ${MAP_SIZE} > ${ARG}; ./n_puzzle ${ARG}

### MAKE RULES
    make gen:   create maps (size 3 ~ 50)
	make run:   generate a new map of size 3 and run n_puzzle
    make map:   check all invalid maps

### VISUALIZE

    SLEEP_TIME=${NUMBER(10000 ~ 100000)} ./n_puzzle -v ${MAP}

### SCRIPTS

- generate map of size N (3 if not specified) and run n_puzzle
#### run.sh 
- visualize (`-f5` and `-v` options are used)
```shell
(example)
$> ./run2.sh 4
n: 120 g: 120 h: 0 w: 120 hash: 29894077883260074544
[ 1][ 2][ 3][ 4]
[12][13][14][ 5]
[11][  ][15][ 6]
[10][ 9][ 8][ 7]
heuristics      : original
expanded nodes  : 596
nodes           : 998
step            : 120
time            : 0.000967
```

#### run2.sh 
- show results of both when using closed set and when using open vector
```shell
(example)
$> ./run2.sh
=== USE CLOSED SET ===
heuristics      : The Manhattan-distance
expanded nodes  : 590
nodes           : 944
step            : 20
time            : 0.000957

=== USE OPEN VEC ===
heuristics      : The Manhattan-distance
expanded nodes  : 590
nodes           : 944
step            : 20
time            : 0.000783
```

#### run3.sh 
- show normal output
```
(example)
$> ./run3.sh
 ====== INPUT ======
# This puzzle is solvable
3
2 5 1
6 0 3
7 4 8

 ====================

 ***** RESULT *****

2, 5, 1, 6, 0, 3, 7, 4, 8, 
2, 5, 1, 0, 6, 3, 7, 4, 8, 
0, 5, 1, 2, 6, 3, 7, 4, 8, 
5, 0, 1, 2, 6, 3, 7, 4, 8, 
5, 1, 0, 2, 6, 3, 7, 4, 8, 
5, 1, 3, 2, 6, 0, 7, 4, 8, 
5, 1, 3, 2, 6, 8, 7, 4, 0, 
5, 1, 3, 2, 6, 8, 7, 0, 4, 
5, 1, 3, 2, 0, 8, 7, 6, 4, 
5, 1, 3, 0, 2, 8, 7, 6, 4, 
0, 1, 3, 5, 2, 8, 7, 6, 4, 
1, 0, 3, 5, 2, 8, 7, 6, 4, 
1, 2, 3, 5, 0, 8, 7, 6, 4, 
1, 2, 3, 0, 5, 8, 7, 6, 4, 
1, 2, 3, 7, 5, 8, 0, 6, 4, 
1, 2, 3, 7, 5, 8, 6, 0, 4, 
1, 2, 3, 7, 0, 8, 6, 5, 4, 
1, 2, 3, 7, 8, 0, 6, 5, 4, 
1, 2, 3, 7, 8, 4, 6, 5, 0, 
1, 2, 3, 7, 8, 4, 6, 0, 5, 
1, 2, 3, 7, 8, 4, 0, 6, 5, 
1, 2, 3, 0, 8, 4, 7, 6, 5, 
1, 2, 3, 8, 0, 4, 7, 6, 5, 
heuristics      : The Manhattan-distance
expanded nodes  : 1121
nodes           : 1759
step            : 22
time            : 0.001553
```

### [GENERATOR >>>](tester/README_gen.md)
