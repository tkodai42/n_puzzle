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
| Correct number of pieces | -f3 |  | |
| Euclidean distance | -f4 | `sqrt( abs(x1-x2) * abs(x1-x2) + abs(y1-y2) * abs(y1-y2) )` | <img width="252" alt="Capture d’écran 2023-02-12 à 23 52 49" src="https://user-images.githubusercontent.com/60470877/218318383-abb16345-700b-44bd-8f69-6ca5fa5d0f61.png"> |
| Original | -f5 |  | |

### Algorithms

- g(n) : the cost of the path from the start node to n
- h(n) : a heuristic function

| algorithm | option | calculation | detail |
| --- | --- | --- | --- | 
| A* search algorithm  |  | `f(n) = g(n) + h(n)` |  |
| Greedy search | -g | `f(n) = h(n)` | |
| Uniform cost search | -u | `f(n) = g(n)` |  |

## RUN
    make

    ARG=${FILE_NAME}; ./generator ${MAP_SIZE} > ${ARG}; ./n_puzzle ${ARG}

### MAKE RULES
    make gen:   create maps (size 3 ~ 50)
	make run:   generate a new map of size 3 and run n_puzzle
    make map:   check all invalid maps

### VISUALIZE

    SLEEP_TIME=${NUMBER(10000 ~ 100000)} ./n_puzzle -v ${MAP}

