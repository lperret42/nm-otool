NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra

SRC_PATH = ./src/
INCLUDES_PATH = ./includes/
OBJ_PATH = ./obj/

SRC = ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memccpy.c \
	  ft_memmove.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strlen.c \
	  ft_strdup.c \
	  ft_strcpy.c \
	  ft_strncpy.c \
	  ft_strcat.c \
	  ft_strncat.c \
	  ft_strlcat.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strstr.c \
	  ft_strnstr.c \
	  ft_strcmp.c \
	  ft_strncmp.c \
	  ft_atoi.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_itoa.c \
	  ft_itoa_base.c \
	  ft_putchar.c \
	  ft_putstr.c \
	  ft_putcolor.c \
	  ft_putendl.c \
	  ft_putnbr.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstdel.c \
	  ft_lstadd.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_putgrid.c \
	  print_memory.c \
	  get_next_line.c\
	  conv_c.c\
	  conv_s.c\
	  conv_d.c\
	  conv_percent.c\
	  conv_o.c\
	  conv_x.c\
	  conv_p.c\
	  conv_u.c\
	  conv_b.c\
	  usual_tools.c\
	  parsing.c core.c\
	  ft_printf.c\
	  alpha.c\
	  digit.c\
	  signed_toa.c\
	  unsigned_toa.c\
	  utf.c\
	  trashers.c

OBJ= $(addprefix $(OBJ_PATH),$(SRC:.c=.o))

all: $(NAME)

$(NAME): obj $(OBJ)
	#@libtool -v -static -o $@ $(LIBFT_A) $(OBJ)
	@libtool -v -static -o $@ $(OBJ)
	@echo "\033[32mLinking & indexing" [ $(NAME) ] "\033[0m"

obj:
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@$(CC) $(FLAGS) $(LIBFT_H) -I$(INCLUDES_PATH) -o $@ -c $<
	@echo "\033[33mCompiling" [ $< ] "\033[0m"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[0;31mCleaning object files" [ $(NAME) ] "\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mDelete" [ $(NAME) ] "\033[0m"

re: fclean all
