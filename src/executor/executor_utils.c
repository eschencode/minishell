/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:14 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/11 14:13:45 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	ft_dup2(int in, int out)
{
	int error_check;
	int fd_in = in;
	int fd_out = out;

	error_check = dup2(fd_in, STDIN_FILENO);
	if(error_check == -1)
	{
		close(fd_in);
		fprintf(stderr, "Error duplicating input: %s\n", strerror(errno));
		return(perror("dup in"),errno);
	}
	error_check = dup2(fd_out, STDOUT_FILENO);
	if(error_check == -1)
	{
		close(fd_out);
		return(perror("dup out"),errno);
	}
	if(fd_out != 1)//stdout --> should print on terminal
		close(fd_out);
	return(0);
}

bool print_env(char **env_arry, int fd_in, int fd_out)
{
	ft_dup2(fd_in, fd_out);
	int i = 0;
	while(env_arry[i])
	{
		printf("%s\n",env_arry[i]);
		i++;
	}
	return (true);
}

void ft_error(char *errmsg)
{
	ft_putendl_fd(errmsg,2);
	//printf("ERROR %s\n",errmsg);
	//ft_free_all(shell.tokens, &shell);
}

void exe_path(t_shell *shell, char *exe)
{
	int y;
	char *path;
	char *exe_path;
	char **paths;
	
	path = env_get_val(shell, "PATH");
	paths = ft_split(path, ':');
	y = -1;
	while (paths[++y])
	{
		if (access(paths[y], F_OK | X_OK) == 0)
		{
			exe_path = malloc(sizeof(char) * (ft_strlen(paths[y]) + 1));
			strcpy(exe_path, paths[y]);
			ft_strcat(exe_path, "/");
			ft_strcat(exe_path, exe);
			free_double_str(paths);
			free(paths);
			if (shell->exe_path)
				free(shell->exe_path);
			shell->exe_path = exe_path;
			return ;
		}
	}
	free_double_str(paths);
	free(paths);
}
