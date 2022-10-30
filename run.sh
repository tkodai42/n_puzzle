#!/bin/bash

NUM=3
if [ $# != 0 ]
then
	NUM=$1
fi

python gen.py $NUM > test/test_file
./n_puzzle test/test_file
