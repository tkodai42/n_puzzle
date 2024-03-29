package main

import (
	"flag"
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

var size int = 4;
var solvable bool;
var iterations int;
var arrayMap []int;

const COLOR_RED = "\x1b[31m"
const COLOR_GREEN ="\x1b[32m"
const COLOR_END = "\x1b[m"

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
	if !solvable {
		if arrayMap[0] != 0 && arrayMap[1] != 0 {
			swapCoords(0, 1)
		} else {
			swapCoords(size, size + 1)
		}
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

func checkSolvable(randomMap []int) (bool) {
	copyMap := make([]int, size * size)
	for v, i := range randomMap {
		copyMap[i] = v
	}

	cntSwap := 0
	for n := 0; n < size * size; n++ {
		if arrayMap[n] == copyMap[n] {
			continue
		}
		for i := n + 1; i < size * size; i++ {
			if arrayMap[n] == copyMap[i] {
				copyMap[n], copyMap[i] = copyMap[i], copyMap[n]
				cntSwap++;
				break
			}
		}
	}

	dx := 0
	dy := 0
	for _, i := range randomMap {
		if randomMap[i] == 0 {
			x, y := idxToCoord(i)
			dx = int(math.Abs(float64(dx - x)))
			dy = int(math.Abs(float64(dy - y)))
		}
		if arrayMap[i] == 0 {
			x, y := idxToCoord(i)
			dx = int(math.Abs(float64(dx - x)))
			dy = int(math.Abs(float64(dy - y)))
		}
	}
	return (dx + dy) % 2 == cntSwap % 2
}

func generateRandomMap() {
	randomMap := make([]int, size * size)
	for v, i := range arrayMap {
		randomMap[i] = v
	}

	rand.Seed(time.Now().Unix())
	for i := size * size - 1; i > 0; i-- {
		j := rand.Intn(i + 1)
		randomMap[i], randomMap[j] = randomMap[j], randomMap[i]
	}

	mapState := checkSolvable(randomMap)
	arrayMap = randomMap

	if mapState != solvable {
		if arrayMap[0] != 0 && arrayMap[1] != 0 {
			swapCoords(0, 1)
		} else {
			swapCoords(size, size + 1)
		}
	}
}

func printMap() {
	digit := len(strconv.Itoa(size * size))

	state := COLOR_GREEN + "solvable" + COLOR_END
	if !solvable {
		state = COLOR_RED + "unsolvable" + COLOR_END
	}
	fmt.Println("# This puzzle is", state)
	fmt.Println(size)
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
	shuffleTimes := flag.Int("t", 0, "Specify shuffling times")
	flag.Parse()
	args := flag.Args()
	var err error
	if len(args) > 0 {
		size, err = strconv.Atoi(args[0])
		if err != nil || size < 3 {
			fmt.Fprintf(os.Stderr, "Puzzle size must be bigger than 2\n")
			return
		}
	}
	if *shuffleTimes < 0 {
		fmt.Fprintf(os.Stderr, "Value must be a positive integer\n")
		return
	}
	iterations = *shuffleTimes

	if !*flagSolvable && !*flagUnsolvable {
		solvable = rand.Intn(2) == 1
	} else if *flagSolvable && *flagUnsolvable {
		fmt.Fprintf(os.Stderr, "You cannot choose both solvable and unsolvable.\n")
		return
	} else {
		solvable = *flagSolvable
	}

	generateMap()
	if (iterations != 0) {
		shuffleMap()
	} else {
		generateRandomMap()
	}
	printMap()
}