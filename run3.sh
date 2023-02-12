#!/bin/bash

clear

NUM=3
if [ $# != 0 ]
then
	NUM=$1
fi

RESULT_DIR=result
mkdir -p result

make -j8

python ./npuzzle-gen.py $NUM > ./$RESULT_DIR/test_file

#### N_PUZZLE ####
./n_puzzle ./$RESULT_DIR/test_file 
