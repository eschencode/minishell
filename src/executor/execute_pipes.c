/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:00:22 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/15 19:35:20 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	int	error_check;

	if (check_redirections(shell, cmd, &fd_in, &fd_out) == -1)
		return (1);
	error_check = ft_dup2(fd_in, fd_out);
	if (!cmd->cmd[0])
	{
		error_check = -1;
		return (error_check);
	}
	exe_path(shell, cmd->cmd[0]);
	if (shell->exe_path != NULL)
	{
		cmd->cmd[0] = shell->exe_path;
	}
	if (execve(cmd->cmd[0], cmd->cmd, shell->env) == -1)
	{
		ft_error("comand not found");
		shell->exit_code = 127;
		exit(EXIT_FAILURE);
	}
	return (0);
}

bool	check_if_builtin1(t_clist *cmd)
{
	if (strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "cd") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "export") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "clear") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "unset") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "printenv") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "echo") == 0)
		return (true);
	return (false);
}

/*check for built in or external set signals  */
int	execute_pipe_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	int	ret;

	ret = 0;
	if (check_if_builtin1(cmd) == true)
	{
		handle_builtin_cmd(shell, cmd, fd_in, fd_out);
	}
	else
	{
		ret = execute_cmd(shell, cmd, fd_in, fd_out);
	}
	return (ret);
}

int	init_pipe_data(t_shell *shell, t_pipedata *pipedata, int fd_in, int fd_out)
{
	t_clist	*ptr;
	int		i;

	i = 0;
	ptr = shell->clist;
	pipedata->fd_in = fd_in;
	pipedata->fd_out = fd_out;
	pipedata->child = 0;
	pipedata->childs = 0;
	ft_memset(pipedata->pids, 0, 100);
	ft_memset(pipedata->pipes, 0, 200);
	while (ptr)
	{
		pipedata->childs++;
		ptr = ptr->next;
	}
	while (i < pipedata->childs - 1)
	{
		if (pipe(pipedata->pipes + 2 * i) == -1)
			return (perror("pipe error"), errno);
		i++;
	}
	return (0);
}

/*closes all pipes exept the one u read from and gonna write to*/
void	close_all_pipes(t_pipedata *pipedata, int chase_one, int chase_tow)
{
	int	i;

	i = 0;
	while (i < (pipedata->childs - 1) * 2)
	{
		if (i != chase_one && i != chase_tow)
			close(pipedata->pipes[i]);
		i++;
	}
}
