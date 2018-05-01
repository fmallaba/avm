SRC_DIR := ./src/
OBJ_DIR := ./obj/
SRC := main.cpp OpFactory.cpp Exception.cpp Parse.cpp AVM.cpp
SRC := $(addprefix $(SRC_DIR), $(SRC))
OBJ := $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.cpp=.o))
NAME = avm
CC = clang++
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $^
	@echo "\033[0;32m$@ was create"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all