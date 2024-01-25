/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:14 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/25 16:24:53 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_dup2(int in, int out)
{
	int	error_check;
	int	fd_in;
	int	fd_out;

	fd_in = in;
	fd_out = out;
	error_check = dup2(fd_in, STDIN_FILENO);
	if (error_check == -1)
	{
		close(fd_in);
		fprintf(stderr, "Error duplicating input: %s\n", strerror(errno));
		return (perror("dup in"), errno);
	}
	error_check = dup2(fd_out, STDOUT_FILENO);
	if (error_check == -1)
	{
		close(fd_out);
		return (perror("dup out"), errno);
	}
	if (fd_out != 1)
		close(fd_out);
	return (0);
}

bool	print_env(char **env_arry, int fd_in, int fd_out)
{
	int	i;

	i = 0;
	ft_dup2(fd_in, fd_out);
	while (env_arry[i])
	{
		printf("%s\n", env_arry[i]);
		i++;
	}
	return (true);
}

void	ft_error(char *errmsg)
{
	ft_putendl_fd(errmsg, 2);
}
