.SILENT:
NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror
CC	=  cc

# ANSI escape codes for colored output
RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
NO_COLOR		= \033[0m

SRC	= 	src/minishell.c src/tokenization/tokenization.c src/parser/checker.c \
		src/signals/signals.c src/builtins/pwd.c src/parser/parser.c \
		src/executor/executor.c src/builtins/env.c src/builtins/unset.c\
		src/executor/executor_utils.c src/executor/execute_pipes.c src/executor/execute_buildin.c \
		src/executor/executor_redirections.c src/heredoc/heredoc.c src/expander/expander_helpers.c \
		src/expander/expanders.c src/builtins/export.c src/builtins/echo.c src/tokenization/custom_split.c \
		src/executor/execute_pipes_part2.c src/executor/path_util.c src/builtins/cd.c src/helpers/frees.c \
		src/helpers/main_helpers.c src/helpers/more_main_helpers.c src/parser/linked_list_helpers.c \
		src/tokenization/split_helpers.c src/exit_status/exit_helpers.c src/tokenization/split_helpers_2.c \
		src/heredoc/heredoc_helpers.c

OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: $(NAME)
	@echo "$(GREEN)Minishell ready.$(NO_COLOR)"
	

$(LIBFT):
	@echo "$(YELLOW)Compiling libft..$(NO_COLOR)"
	@$(MAKE) -s -C ./libs/libft
	@echo "$(GREEN)Done compiling libft.$(NO_COLOR)"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(YELLOW)Compiling minishell...$(NO_COLOR)"

clean:
	@echo "$(RED)Cleaning up...$(NO_COLOR)"
	@$(MAKE) $@ -s -C ./libs/libft
	@rm -rf $(OBJ)
	@echo "$(RED)Done cleaning up.$(NO_COLOR)"

fclean: clean
	@echo "$(RED)Cleaning up...$(NO_COLOR)"
	@rm -rf $(NAME)
	@$(MAKE) $@ -s -C ./libs/libft
	@echo "$(RED)Done cleaning up.$(NO_COLOR)"

re: fclean all
	@./$(NAME)

run: $(NAME)
	./$(NAME)

r: $(NAME)
	./$(NAME)
