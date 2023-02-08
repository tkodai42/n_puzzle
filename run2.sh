#!/bin/bash

NUM=3
if [ $# != 0 ]
then
	NUM=$1
fi

RESULT_DIR=result
mkdir result

make 
make -C ./prev_submit

python ./tester/gen.py $NUM > ./$RESULT_DIR/test_file
./n_puzzle -f5 -v ./$RESULT_DIR/test_file > ./$RESULT_DIR/result_set
./prev_submit/n_puzzle -f5 -v ./$RESULT_DIR/test_file > ./$RESULT_DIR/result_vec

echo "=== USE CLOSED SET ==="
tail -n 5 ./$RESULT_DIR/result_set
echo 
echo "=== USE OPEN VEC ==="
tail -n 5 ./$RESULT_DIR/result_vec
