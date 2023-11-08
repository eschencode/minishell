/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:49:36 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/08 09:47:39 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL
# define MINISHELL

# include "../libs/libft/libft.h"
#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc, free, exit
#include <unistd.h>     // for write, access, close, fork, execve, dup, dup2, pipe
#include <string.h>     // for strerror
#include <signal.h>     // for signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/types.h>  // for wait, waitpid, wait3, wait4
#include <sys/stat.h>   // for stat, lstat, fstat
#include <fcntl.h>      // for open
#include <dirent.h>     // for opendir, readdir, closedir
#include <sys/errno.h> // for perror
#include <limits.h>     // for PATH_MAX
#include <pwd.h>        // for getpwuid
#include <sys/wait.h>   // for WEXITSTATUS
#include <sys/ioctl.h>  // for ioctl
#include <termios.h>    // for tcgetattr, tcsetattr
#include <curses.h>     // for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <readline/readline.h> // for readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
#include <readline/history.h>  // for history related functions
#include <errno.h>      // for errno
#include <stdbool.h>    // for boolean data type

typedef enum{
	WORD,
	CMD,
	ARG,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	RIGHT,
	RIGHT_RIGHT,
	LEFT,
	LEFT_LEFT
} TokenType;

typedef struct s_tokens
{
	char *token;
	TokenType type;
	int id;
} t_tokens;

typedef struct s_clist
{
	int	token_indx; // save position of cmd from index (helps fill args later) 
	bool external_flag; //if true == external command
	char *cmd;
	char **args;
	int	n_args;
	bool pre_pipe;
	bool post_pipe;
	struct s_clist *next;
} t_clist;

typedef struct s_shell
{
	t_tokens *tokens;
	char *input_str;
	int	tokens_flag;
	t_clist *clist;
	int	n_pipes;

} t_shell;

// tokenization/tokenization.c
t_tokens *tokenization(char *input);

// parser/checker.c
void checker(t_shell *shell);

//signals
void signal_handler(int sig);

//builtins
int cd(t_shell shell);

//parser/parser.c
int	parser(t_shell *shell);

//executor
int executor(t_shell shell);

//builtins
int cd(t_shell shell);
int pwd_builtin(t_shell shell);
int echo_l(t_shell shell);


#endif
