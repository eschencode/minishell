/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:49:36 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/26 17:31:10 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/errno.h>
# include <limits.h>
# include <pwd.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdbool.h>

typedef enum t_tokentype
{
	WORD,
	CMD,
	ARG,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	RIGHT,
	RIGHT_RIGHT,
	LEFT,
	LEFT_LEFT,
	FILE_NAME
}	t_TokenType;

typedef struct s_tokens
{
	char		*token;
	t_TokenType	type;
	int			id;
}	t_tokens;

typedef struct s_clist
{
	bool			external_flag;
	int				cmd_pos;
	char			**cmd;
	int				n_args;
	struct s_clist	*next;
}	t_clist;

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
	t_tokens	*tokens;
	int			signal_code;
	char		*input_str;
	int			tokens_flag;
	int			num_tokens;
	t_clist		*clist;
	int			env_flag;
	char		**env;
	char		*path;
	char		*cd_last_path;
	int			n_pipes;
	int			redirect_in;
	int			redirect_out;
	char		*exe_path;
	int			exit_code;
	int			loop_exit;
	struct sigaction *sig_int;
}	t_shell;

//minishell.c
void	ft_free_all(t_tokens *tokens, t_shell *shell);
void	free_double_str(char **str);
// tokenization/tokenization.c
void	tokenization(t_shell *shell, char *input);
int		count_quotes(char *input);
// parser/checker.c
void	checker(t_shell *shell);
void	count_pipes(t_shell *shell);
//signals
void	signal_handler(int sig);
//cd.c
bool	cd(t_shell *shell, char *cmd, int fd_in, int fd_out);
//parser/parser.c
int		parser(t_shell *shell);
void	print_clist(t_shell *shell);
//executor
int		executor(t_shell *shell);
bool	check_if_builtin(t_shell *shell, t_clist *cmd, int fd_in, int fd_out);
//executor bulitin
int		safe_dup(int *safe_in, int *safe_out);
int		handle_builtin_cmd(t_shell *shell, t_clist *cmd, int in, int out);
int		ft_strcmp(char *str1, char *str2);
//execute pipes
int		execute_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out);
bool	check_if_builtin1(t_clist *cmd);
int		execute_pipe_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out);
int		init_piped(t_shell *shell, t_pipedata *pipedata, int fd_in, int fd_out);
void	close_all_pipes(t_pipedata *pipedata, int chase_one, int chase_tow);
//execute_pipes_part2
int		run_child(t_shell *shell, t_pipedata *pipedata, t_clist *cmd);
int		run_parent(t_pipedata *pipedata, t_shell *shell);
int		execute_pipes(t_shell *shell);

//executor redir
int		check_redir(t_shell *shell, t_clist *cmd, int *fd_in, int *fd_out);
int		handle_redirections(t_shell *shell, int i, int *fd_in, int *fd_out);
int		handle_file_error(t_shell *shell, int *fd_in, int *fd_out);

//executor_utils.
int		ft_dup2(int in, int out);
bool	print_env(char **env_arry, int fd_in, int fd_out);
void	ft_error(char *errmsg);
//path_util.c
char	*create_exe_path(char *path, char *exe);
void	free_resources(t_shell *shell, char **paths);
void	set_exe_path(t_shell *shell, char *exe_path, char **paths);
void	exe_path(t_shell *shell, char *exe);
//builtins_l
bool	pwd_builtin(int fd_in, int fd_out);
void	add_path_to_hist(t_shell *shell);
int		echo_l(t_shell shell);
// builtins_a
bool	clearwindow(int fd_in, int fd_out);
bool	ft_export(t_shell *shell, char **cmd, int fd_in, int fd_out);
void	free_env(t_shell *shell);
// builtins_a_2
int		is_in_env(t_shell *shell, char *str);
bool	ft_unset(t_shell *shell, char *cmd, int fd_in, int fd_out);
bool	ft_echo(t_shell *shell, t_clist *c_node, int fd_in, int fd_out);
char	*env_get_val(t_shell *shell, char *var);
int		env_get_id(t_shell *shell, char *var);
// heredoc
int		ft_heredoc(t_shell *shell, t_clist *cmd);
int		heredoc_check(t_shell *shell, t_clist *cmd);
// expander/expander_quotes.c
void	expander_quotes(t_shell *shell);
void	print_tokens(t_tokens *tokens);
void	tilde_expander(t_shell *shell);
void	push_to_env(t_shell *shell, char *str);
// expanders.c
void	run_expanders(t_shell *shell);
bool	ft_penis(void);
int		env_find_row(t_shell *shell, char *str);
int		count_str_arr(char **str);
void	str_arr_cpy(char **new, char **old);
char	**custom_split(char *str);
char	*fast_forward_str(char *str);
// signals
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	sigs_init(void);

// rest -> unsorted
void	ft_free_clist(t_shell *shell);
void	ft_free_tokens(t_tokens *tokens);
int		validate_input_str(t_shell *shell);
int		catch_eof_signal(t_shell *shell);
int		weird_token_catcher(t_shell *shell);
int		exit_check(t_shell *shell);
void	env_init(t_shell *shell);
void	exit_routine(t_shell *shell, int exit_code);
int		check_str_digit(char *str);
char	*ret_push_val_into_str(char *str, char *val, char *var, int pos);
char	*ret_push_val_into_str_tilde(char *str, char *val, char *var, int pos);
void	clist_init(t_shell *shell);
void	clist_args_fill(t_shell *shell);
char	*fast_forward_str(char *str);
int		fast_forward_str_int(char *str);
char	**add_element(char **array, int current_size, char *new_element);
int		get_regular_len(char *str);
int		get_quotes_len(char *str);
void	push_exit_code(t_shell *shell, int child_status);
int		dollar_check(char *str);
int		eval_input_error(t_shell *shell);
int		get_quotes_len(char *str);
int		get_regular_len(char *str);
int		heredoc_check(t_shell *shell, t_clist *cmd);
int		heredoc_create(void);
char	*get_heredoc_key(t_clist *cmd);
int		command_checker(t_shell *shell);
#endif
