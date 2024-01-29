/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:14 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/29 13:16:49 by leschenb         ###   ########.fr       */
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

int	handle_file_error(t_shell *shell, int *fd_in, int *fd_out)
{
	ft_putendl_fd("No such file or directory", 2);
	shell->exit_code = 1;
	if (*fd_in == -1)
		close(*fd_in);
	if (*fd_out == -1)
		close(*fd_out);
	return (-1);
}

bool	check_if_builtin(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (pwd_builtin(shell, fd_in, fd_out));
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (cd(shell, cmd->cmd[1], fd_in, fd_out));
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd, fd_in, fd_out)));
	if (ft_strcmp(cmd->cmd[0], "clear") == 0)
		return (clearwindow(fd_in, fd_out));
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(shell, cmd->cmd[1], fd_in, fd_out));
	if (ft_strcmp(cmd->cmd[0], "printenv") == 0)
		return (print_env(shell->env, fd_in, fd_out));
	if (ft_strcmp(shell->clist->cmd[0], "echo") == 0)
		return (ft_echo(shell, shell->clist, fd_in, fd_out));
	if (ft_strcmp(shell->clist->cmd[0], "penis") == 0)
		return (ft_penis());
	return (false);
}
