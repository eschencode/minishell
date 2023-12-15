
NAME	= minishell
CFLAGS	= #-Wall -Wextra -Werror
CC		=  cc
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

SRC	= 	src/minishell.c src/tokenization/tokenization.c src/parser/checker.c \
		src/signals/signals.c src/builtins/builtins_l.c src/parser/parser.c \
		src/executor/executor.c src/builtins/builtins_a.c src/builtins/builtins_a_2.c\
		src/executor/executor_utils.c src/executor/execute_pipes.c src/executor/execute_buildin.c \
    src/heredoc/heredoc.c

OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libs/libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	$(MAKE) $@ -C ./libs/libft

re: fclean all
	./$(NAME)

run: $(NAME)
	./$(NAME)

r: $(NAME)
	./$(NAME)

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)
