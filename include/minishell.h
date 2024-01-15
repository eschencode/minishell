/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:49:36 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/14 14:31:32 by aeastman         ###   ########.fr       */
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
	bool external_flag; //if true == external command
	int cmd_pos;
	char **cmd;
	int n_args;
	struct s_clist *next;
} t_clist;

typedef struct s_pipedata{
	int	pids[100];
	int	pipes[200];
	int	childs;
	int	child;
	int	fd_in;
	int	fd_out;
}	t_pipedata;

typedef struct s_shell
{
	t_tokens *tokens;
	char *input_str;
	int	tokens_flag;
	int num_tokens;
	t_clist *clist;
	int		env_flag;
	char **env;
	char *path;
	char *cd_last_path;
	int	n_pipes;
	int redirect_in;
	int redirect_out;
	char	*saved_cmd;
	char	*exe_path;
	int		exit_code;

} t_shell;

//minishell.c
void ft_free_all(t_tokens *tokens, t_shell *shell);
void free_double_str(char **str);


// tokenization/tokenization.c
t_tokens *tokenization(t_shell *shell, char *input);
int 	count_quotes(char *input);

// parser/checker.c
void 	checker(t_shell *shell);
void ft_expander(t_shell *shell);
void count_pipes(t_shell *shell);

//signals
void 	signal_handler(int sig);

//builtins
bool 	cd(t_shell *shell, char *cmd, int fd_in, int fd_out);

//parser/parser.c
int		parser(t_shell *shell);
void 	print_clist(t_shell *shell);

//executor
int 	executor(t_shell *shell);
bool check_if_builtin(t_shell *shell, t_clist *cmd, int fd_in, int fd_out);

//executor bulitin
int handle_builtin_cmd(t_shell *shell,t_clist *cmd, int in, int out);

//execute pipes
int execute_pipes(t_shell *shell);
int first_pipe(t_shell *shell, t_clist *cmd);
int last_pipe(t_shell *shell, t_clist *cmd);
int init_pipe_data(t_shell *shell, t_pipedata *pipedata, int fd_in, int fd_out);
int execute_cmd(t_shell *shell,t_clist *cmd, int fd_in, int fd_out);
bool	check_redirections_check(t_shell *shell);
bool	check_redirections_pipes(t_shell *shell,int *fd_in, int *fd_out);
//executor_utils.
void ft_error(char *errmsg);
bool print_env(char **env_arry, int fd_in, int fd_out);
int	ft_dup2(int in, int out);
void exe_path(t_shell *shell, char *exe);

//builtins_l
bool 	pwd_builtin(int fd_in, int fd_out);
void	add_path_to_hist(t_shell *shell);
int 	echo_l(t_shell shell);

// builtins_a
bool 	clearwindow(int fd_in, int fd_out);
bool	ft_export(t_shell *shell, char **cmd, int fd_in, int fd_out);
void	free_env(t_shell *shell);

// builtins_a_2
int		is_in_env(t_shell *shell, char *str);
bool	ft_unset(t_shell *shell, char *cmd, int fd_in, int fd_out);
bool    ft_echo(t_shell *shell, t_clist *c_node, int fd_in, int fd_out);
char 	*env_get_val(t_shell *shell, char *var);
int 	env_get_id(t_shell *shell, char *var);

// builtins_a_3
bool	ft_heredoc(t_clist *cmd);

//executor redirectios
bool check_for_redirections(t_shell *shell, t_clist *cmd);
bool check_for_redirections_out(t_shell *shell,t_clist *cmd);
// expander/expander_quotes.c
void	expander_quotes(t_shell *shell);

void print_tokens(t_tokens *tokens);


void tilde_expander(t_shell *shell);

void	push_to_env(t_shell *shell, char *str);

// expanders.c
void	run_expanders(t_shell *shell);

bool	ft_penis(void);

int		env_find_row(t_shell *shell, char *str);
int		count_str_arr(char **str);
void	str_arr_cpy(char **new, char **old);

#endif
