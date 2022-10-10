NAME = n_puzzle
FILE3 = 3.txt
FILE4 = 4.txt
FILE5 = 5.txt

SRC = $(shell find src -type f -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

CXX = clang++

all	: $(NAME)

$(NAME)	:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

gen		:
	python	gen.py 3 > test/${FILE3}
	python	gen.py 4 > test/${FILE4}
	python	gen.py 5 > test/${FILE5}

3		: all 
	./${NAME}	test/${FILE3}
