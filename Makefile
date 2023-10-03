
NAME	= minishell
CFLAGS	= #-Wall -Wextra -Werror 
CC		=  cc

SRC	= src/minishell.c
OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libs/libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	$(MAKE) $@ -C ./libs/libft

re: fclean all