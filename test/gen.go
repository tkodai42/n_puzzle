package main

import (
	"flag"
	"fmt"
	"math/rand"
	"strconv"
	"time"
)

var size int;
var solvable bool;
var iterations int;
var arrayMap []int;

func coordToIdx(x, y int) (int) {
	return y * size + x;
}

func idxToCoord(i int) (int, int) {
	return i % size, i / size;
}

func swapCoords(c1, c2 int) {
	tmp := arrayMap[c1]
	arrayMap[c1] = arrayMap[c2]
	arrayMap[c2] = tmp
}

func isInRange(x, y int) (bool) {
	return 0 <= x && x < size && 0 <= y && y < size
}

func shuffleMap() {
	n := 0
	for n = 0; arrayMap[n] != 0; n++ {
	}
	for i := 0; i < iterations; i++ {
		var choice []int
		x, y := idxToCoord(n)
		if isInRange(x + 1, y) {
			choice = append(choice, n + 1)
		}
		if isInRange(x - 1, y) {
			choice = append(choice, n - 1)
		}
		if isInRange(x, y + 1) {
			choice = append(choice, n + size)
		}
		if isInRange(x, y - 1) {
			choice = append(choice, n - size)
		}
		idx := rand.Intn(len(choice))
		swp := choice[idx]
		swapCoords(n, swp)
		n = swp
	}
}

func generateMap() {
	arrayMap = make([]int, size * size)

	x := 0
	y := 0
	dx := 1
	dy := 0
	for n := 1; n < size * size; n++ {
		arrayMap[coordToIdx(x, y)] = n
		if x + dx < 0 || size <= x + dx || (dx != 0 && arrayMap[coordToIdx(x + dx, y)] != 0) {
			dy = dx
			dx = 0
		}
		if y + dy < 0 || size <= y + dy || (dy != 0 && arrayMap[coordToIdx(x, y + dy)] != 0) {
			dx = -dy
			dy = 0
		}
		x += dx
		y += dy
	}
	arrayMap[coordToIdx(x, y)] = 0
}

func printMap() {
	digit := len(strconv.Itoa(size * size))
	for i := 0; i < size * size; i++ {
		spacer := ' '
		if i % size == size - 1 {
			spacer = '\n'
		}
		fmt.Printf("%*d%c", digit, arrayMap[i], spacer)
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())
	flagSolvable := flag.Bool("s", false, "Generate solvable puzzle")
	flagUnsolvable := flag.Bool("u", false, "Generate unsolvable puzzle")
	shuffleTimes := flag.Int("t", 4242, "Specify shuffling times")
	flag.Parse()
	args := flag.Args()
	var err error
	size, err = strconv.Atoi(args[0])
	if err != nil || size < 3 {
		panic("Puzzle size must be bigger than 2")
	}
	if *shuffleTimes < 0 {
		panic("Value must be a positive integer")
	}
	iterations = *shuffleTimes

	if !*flagSolvable && !*flagUnsolvable {
		solvable = rand.Intn(2) == 1
	} else if *flagSolvable && *flagUnsolvable {
		panic("You cannot choose both solvable and unsolvable.")
	} else {
		solvable = *flagSolvable
	}

	generateMap()
	shuffleMap()
	printMap()
}