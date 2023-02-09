# n_puzzle

### SYNOPSIS

     n_puzzle [-...] [file]

### DESCRIPTION

     The options are as follows:

     -d    debug

     -f1   The Manhattan-distance

     -f2   Improved Manhattan-distance

     -f3   Corrent number of pieces

     -f4   Euclidean-distance

     -f5   original

     -g    greedy search

     -h    HELP

     -p    play n_puzzle!!!

     -u    Uniform Cost

     -v    visualize

     -o    use open/close list

### COMPILE

    make gen:   create maps(size 3 ~ 50)
    make map:   check invalid maps
    ARG=${FILE_NAME}; ./generator ${MAP_SIZE} > ${ARG}; ./n_puzzle ${ARG}

### VISUALIZE

    export SLEEP_TIME=${NUMBER(10000 ~ 100000)}

