#!/bin/bash

NUM=3
if [ $# != 0 ]
then
	NUM=$1
fi

RESULT_DIR=result
mkdir result

make -C ./use_close_set
make -C ./use_open_status_vector

python ./use_close_set/tester/gen.py $NUM > ./$RESULT_DIR/test_file
./use_close_set/n_puzzle -f5 -v ./$RESULT_DIR/test_file > ./$RESULT_DIR/result_set
./use_open_status_vector/n_puzzle -f5 -v ./$RESULT_DIR/test_file > ./$RESULT_DIR/result_vec

echo "=== USE CLOSED SET ==="
tail -n 5 ./$RESULT_DIR/result_set
echo 
echo "=== USE OPEN VEC ==="
tail -n 5 ./$RESULT_DIR/result_vec
