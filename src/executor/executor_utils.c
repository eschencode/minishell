/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:14 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/26 19:04:11 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	ft_dup2(int in, int out)
{
	int error_check;

	error_check = dup2(in, STDIN_FILENO);
	if(error_check == -1)
	{
		close(in);
		fprintf(stderr, "Error duplicating input: %s\n", strerror(errno));
		return(perror("dup in"),errno);
	}
	error_check = dup2(out, STDOUT_FILENO);
	if(error_check == -1)
	{
		close(out);
		return(perror("dup out"),errno);
	}
	if(out != 1)//stdout --> should print on terminal
		close(out);
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

void ft_error(char *errmsg, t_shell shell)
{
	printf("ERROR %s\n",errmsg);
	//ft_free_all(shell.tokens, &shell);
}

char *exe_path(t_shell *shell, char *exe)
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
		exe_path = malloc(sizeof(char) * (ft_strlen(paths[y]) + ft_strlen(exe) + 4));
		ft_strlcpy(exe_path, paths[y], ft_strlen(paths[y]));
		ft_strcat(exe_path, "/");
		ft_strcat(exe_path, exe);
		if (access(exe_path, F_OK | X_OK) == 0)
		{
			free_double_str(paths);
			return (exe_path);
		}
		free(exe_path);
	}
	free_double_str(paths);
	return NULL;
}
