NAME = minishell
CC = gcc
CLANG = clang
CFLAGS = -g -Wall -Werror -Wextra -I ./inc
SRC_DIR = src/obj
LIBFTPRINTF = lib/libftprintf.a
FIND = $(shell find $(SRC_DIR))
SRC = $(filter %.c, $(FIND))
OBJ = ${SRC:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -C lib
		ar -rcs minishell.a $(OBJ)
		$(CLANG) $(CFLAGS) src/main.c minishell.a $(LIBFTPRINTF) -lreadline -o $(NAME)

test:
	$(CC) $(CFLAGS) test.c $(LIBFTPRINTF) $(LIBFT) -lreadline -o test

clean:
		make -C lib clean
		rm -rf $(OBJ)

fclean: clean
		make -C lib fclean
		rm -rf minishell.a
		rm -rf $(NAME)

re: fclean all
