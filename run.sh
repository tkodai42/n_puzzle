#!/bin/bash

NUM=3
if [ $# != 0 ]
then
	NUM=$1
fi

make
python tester/gen.py $NUM > map/test_maps/test_file
./n_puzzle -f5 -v map/test_maps/test_file
