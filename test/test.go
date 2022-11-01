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
var arrayMap []int;

func coordToIdx(x, y int) (int) {
	return y * size + x;
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
	puzzleSize := flag.Int("x", 4, "Puzzle size")
	flag.Parse()
	
	if *puzzleSize < 3 {
		panic("Puzzle size must be bigger than 2")
	}
	size = *puzzleSize

	if !*flagSolvable && !*flagUnsolvable {
		solvable = rand.Intn(2) == 1
	} else if *flagSolvable && *flagUnsolvable {
		panic("You cannot choose both solvable and unsolvable.")
	} else {
		solvable = *flagSolvable
	}

	generateMap()

	printMap()
}