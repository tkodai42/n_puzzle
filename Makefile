NAME = n_puzzle
FILE3 = 3.txt
FILE4 = 4.txt
FILE5 = 5.txt
FILE10 = 10.txt
FILE11 = 11.txt

SRCS = $(shell find src -type f -name "*.cpp")
HDRS = $(shell find src -type f -name "*.hpp")
OBJS = $(SRCS:.cpp=.o)

CXX = clang++
#CXXFLAGS += -O2 -Wall -Wextra -Werror
#CXXFLAGS += -lncurses

all		: $(NAME)

$(NAME)	:	$(OBJS)
	$(CXX) -lncurses -o $(NAME) $(OBJS)

$(OBJS)	:	$(HDRS)

clean	:
	rm -rf $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

gen		:
	python	gen.py 3 > test/${FILE3}
	python	gen.py 4 > test/${FILE4}
	python	gen.py 5 > test/${FILE5}
	python	gen.py 10 > test/${FILE10}
	python	gen.py 11 > test/${FILE11}

3		:	all 
	./${NAME}	test/${FILE3}

33		:	all
	python	gen.py 3 > test/${FILE3}
	@cat test/$(FILE3)
	./${NAME}	test/${FILE3}

4		:	all 
	./${NAME}	test/${FILE4}

run 	:
	python	gen.py $(ARG) > test/$(FILE$(ARG))
	@cat test/$(FILE${ARG})
	./${NAME} test/${FILE$(ARG)}

define F
   @echo ==========================================
   @echo [input file] $(1)
   @cat $(1)
   @echo [execute]
   @./${NAME} $(1)

endef

xs :=  $(shell find map/invalid -type f -name "*.map")

map:	all
	$(foreach x,$(xs),$(call F,$(x)))
	@echo ==========================================
