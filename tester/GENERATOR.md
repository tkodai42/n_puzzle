# n_puzzle generator

## USAGE

### COMPILE

    go build tester/generator.go

### SYNOPSIS

     ./generator [-...] [size]

### DESCRIPTION

    Usage of ./generator:
      -s    Generate solvable puzzle
      -u    Generate unsolvable puzzle

      -t int
            Specify shuffling times

### RUN
- generate unsolvable map of size 40
```
./generator -u 40
```
- generate solvable map of size 25 using 10000 times suffle
```
./generator -s -t 10000 25
```

#### MAKE
- generate 3-15, 20, 25, 30, 35, 40, 45, 50 size valid (solvable) maps

```
make gen
```

## SHUFFLE TYPES

| shuffle | option | detail |
| --- | --- | --- |
| Random shuffle |  | swap all pices randomly and check if the result if solvable |
| Slide shuffle | `-t [N]` | From the complete state, shuffle by slide  empty piece [N] times |

- Random shuffle
```shell
$> ./generator -s
# This puzzle is solvable
4
11  4  7 13
 6 14  9 12
 1  3  2  5
 0 10  8 15
```

- Slide Shuffle (20 times)
```shell
$> ./generator -s -t 20
# This puzzle is solvable
4
 2  3  4  0
 1 12 13  5
11 15 14  6
10  9  8  7
```
