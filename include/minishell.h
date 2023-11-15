/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:49:36 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/15 16:06:39 by leschenb         ###   ########.fr       */
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

typedef struct s_env
{
	char *variable;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_clist
{
	bool external_flag; //if true == external command
	int cmd_pos;
	char **cmd;
	int n_args;
	bool pre_pipe;
	bool post_pipe;
	struct s_clist *next;
} t_clist;

typedef struct s_pipes
{
	int current_cmd;
	int pipe_fd[2];
	int output_len;
	char *output_str;
} t_pipes;

typedef struct s_shell
{
	t_tokens *tokens;
	char *input_str;
	int	tokens_flag;
	t_clist *clist;
	t_env	*envlist;
	int	n_pipes;
	t_pipes pipes;

} t_shell;


//minishell.c
void ft_free_all(t_tokens *tokens, t_shell *shell);

// tokenization/tokenization.c
t_tokens *tokenization(char *input);

// parser/checker.c
void 	checker(t_shell *shell);

//signals
void 	signal_handler(int sig);

//builtins
int 	cd(t_shell shell);

//parser/parser.c
int		parser(t_shell *shell);

//executor
int 	executor(t_shell *shell);

//execute pipes
int execute_pipes(t_shell shell);
int first_pipe(t_shell shell);
int last_pipe(t_shell shell);

//executor_utils.
char **envlist_to_array(t_env *envlist);
void ft_error(char *errmsg, t_shell shell);
void print_env(char **env_arry);

//builtins_l
int 	pwd_builtin(t_shell shell);
int 	echo_l(t_shell shell);

// builtins_a
void 	clearwindow(void);
bool 	ft_export(t_shell *shell, char **cmd);

// linked_lists.c
t_env 	*new_node_env(t_shell *shell, char *var, char *val);
void 	insert_node_env(t_shell *shell, t_env *node);

#endif
