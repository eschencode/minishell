/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:35 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/23 16:03:59 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*sets up the filedisriptors -->execute_pipe_cmd*/
int	run_child(t_shell *shell, t_pipedata *pipedata, t_clist *cmd)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	if (pipedata->child == 0)
	{
		fd_in = pipedata->fd_in;
		fd_out = pipedata->pipes[1];
	}
	else if (pipedata->child == pipedata->childs - 1)
	{
		fd_in = pipedata->pipes[2 * pipedata->child - 2];
		fd_out = pipedata->fd_out;
	}
	else
	{
		fd_in = pipedata->pipes[2 * pipedata->child -2];
		fd_out = pipedata->pipes[2 * pipedata->child + 1];
	}
	close_all_pipes(pipedata, 2 * pipedata->child + 1, 2 * pipedata->child - 2);
	fd_in = execute_pipe_cmd(shell, cmd, fd_in, fd_out);
	exit(fd_in);
}

int	run_parent(t_pipedata *pipedata)
{
	pid_t	pid;
	int		child_status;
	int		ret;

	close_all_pipes(pipedata, -1, -1);
	pipedata->child--;
	ret = 1;
	while (pipedata->child >= 0)
	{
		pid = waitpid(pipedata->pids[pipedata->child], &child_status, 0);
		if (pid == pipedata->pids[pipedata->childs -1])
		{
			if ((pipedata->child == (pipedata->childs -1)) \
			&& WIFEXITED(child_status))
				ret = WEXITSTATUS(child_status);
		}
		pipedata->child--;
	}
	return (ret);
}

int	execute_pipes(t_shell *shell)
{
	t_clist		*cmd;
	t_pipedata	*pipedata;

	pipedata = malloc(sizeof(t_pipedata));
	init_pipe_data(shell, pipedata, 0, 1);
	cmd = shell->clist;
	while (cmd)
	{
		pipedata->pids[pipedata->child] = fork();
		if (pipedata->pids[pipedata->child] == -1)
			return (perror("fork error"), errno);
		else if (pipedata->pids[pipedata->child] == 0)
			run_child(shell, pipedata, cmd);
		pipedata->child++;
		cmd = cmd->next;
	}
	run_parent(pipedata);
	free(pipedata);
	return (0);
}
