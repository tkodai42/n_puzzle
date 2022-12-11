NAME = n_puzzle
TESTER = generator

CC = g++

HDRS_PATH		+= includes/
SRCS_PATH		+= srcs/
OBJS_PATH		+= objs/

SRCS = $(shell find $(SRCS_PATH) -type f -name "*.cpp" | sed 's!^.*/!!')
vpath %.cpp $(SRCS_PATH)

HDRS = $(shell find $(HDRS_PATH) -type f -name "*.hpp" | sed 's!^.*/!!')
vpath %.hpp $(HDRS_PATH)

OBJS		+= $(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))

#CFLAGS		+= -Wall
#CFLAGS		+= -Werror
#CFLAGS		+= -Wextra

CPPFLAGS	+= -I $(HDRS_PATH)

all:				$(NAME)

$(NAME):			$(LIBFT_NAME) $(OBJS)
					$(CC) -lncurses $(OBJS) -o $@

$(OBJS_PATH)%.o:	%.cpp
					$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJS):			Makefile $(HDRS) | $(OBJS_PATH)

$(OBJS_PATH):
					mkdir -p $@

clean:
					$(RM) -r $(OBJS_PATH)

fclean:				clean
					$(RM) $(NAME)
					$(RM) $(TESTER)

re:					fclean all

#===== TEST =====#

TEST_SIZE = 3

run:	$(NAME) $(TESTER)
	./$(TESTER) $(TEST_SIZE) > map/test_maps/$(TEST_SIZE).map
	@cat map/test_maps/$(TEST_SIZE).map
	./$(NAME) map/test_maps/$(TEST_SIZE).map

define F2
   @./$(TESTER) $(1) > map/test_maps/$(1).map
   @echo --- generate map/test_map/$(1).map ---

endef

gen:	$(NAME) $(TESTER)
	$(foreach x, 3 4 5 6 7 8 9 10 11 12 13 14 15 20 25 30 35 40 45 50, $(call F2,$(x)))

$(TESTER):
	go build tester/$@.go

define F
   @echo ==========================================
   @echo ">> [input file] $(1)"
   @cat $(1)
   @echo
   @echo ">> [execute]"
   @./${NAME} $(1)

endef

xs :=  $(shell find map/invalid -type f -name "*.map")

map:	all
	$(foreach x,$(xs),$(call F,$(x)))
	@echo ==========================================

.PHONY:				all clean fclean re

# ./generator $(NUM) > $(file) ; ./n_puzzle $(file)
