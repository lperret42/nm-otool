NAME = ft_nm
CC = gcc
FLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ../libft/
LIBFT_H = -I$(LIBFT_PATH)/includes
LIBFT_A = $(LIBFT_PATH)libft.a
LIBFT_LINK = -L$(LIBFT_PATH) -lft

SRC_PATH = ./src/
INCLUDES_PATH = ./includes/
OBJ_PATH = ./obj/

SRC = main.c nm.c bin_64.c ar.c catch.c error.c

OBJ	= $(addprefix $(OBJ_PATH),$(SRC:.c=.o))

all: $(NAME)

$(NAME): obj $(LIBFT_A) $(OBJ)
	@$(CC) $(FLAGS) -o $@ $(LIBFT_A) $(OBJ)
	@echo "\033[32mLinking & indexing" [ $(NAME) ] "\033[0m"

obj:
	@mkdir $(OBJ_PATH)

$(LIBFT_A):
	@make -C $(LIBFT_PATH)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_PATH) $(LIBFT_H) -o $@ -c $<
	@echo "\033[33mCompiling" [ $< ] "\033[0m"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;31mCleaning object files" [ $(NAME) ] "\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31mDelete" [ $(NAME) ]  "\033[0m"

re: fclean all
