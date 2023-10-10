/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:49:36 by leschenb          #+#    #+#             */
/*   Updated: 2023/10/02 13:49:43 by leschenb         ###   ########.fr       */
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

typedef struct s_tokens
{
	char *token;
	int id;
	
} t_tokens;



t_tokens *tokenization(char *input);


#endif
