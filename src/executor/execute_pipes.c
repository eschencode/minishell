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


int execute_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	int error_check;
	//add here check for redirections later
	error_check = ft_dup2(fd_in, fd_out);
	if(!cmd->cmd[0])
	{
		error_check = -1;
		return(error_check);
	}
	if(execve(cmd->cmd[0],cmd->cmd, shell->env) == -1)//
	{
		ft_error("exec error",*shell);
		exit(EXIT_FAILURE);
	}
}


/*check for built in or external set signals  */
int	execute_pipe_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	int ret;

	printf("Executing pipe command: %s\n", cmd->cmd[0]);
	printf("fd in %d\n",fd_in);
	printf("fd out %d\n",fd_out);
	if (check_if_builtin(shell, cmd, fd_in, fd_out) == false)
		execute_cmd(shell,cmd,fd_in,fd_out);


}

int init_pipe_data(t_shell *shell, t_pipedata *pipedata, int fd_in, int fd_out)
{
	t_clist *ptr;
	int i;

	printf("Initializing pipe data\n");
	i = 0;
	ptr = shell->clist;
	pipedata->child = 0;
	pipedata->childs = 0;
	pipedata->fd_in = fd_in;
	pipedata->fd_out = fd_out;
	ft_memset(pipedata->pids, 0 , 100);
	ft_memset(pipedata->pipes, 0 , 200);
	while(ptr)
	{
		pipedata->childs++;
		ptr = ptr->next;
	}
	while(i < pipedata->childs - 1)
	{
		if(pipe(pipedata->pipes + 2 * i) == -1)
			return(perror("pipe error"),errno);
		i++;
	}
	return(0);
}
//closes all pipes exept the one u read from and gonna write to
void	close_all_pipes(t_pipedata *pipedata, int chase_one, int chase_tow)
{
	int i;

	i = 0;
	while(i < (pipedata->childs - 1) * 2)
	{
		if(i != chase_one && i != chase_tow)
			close(pipedata->pipes[i]);
		i++;
	}
}

int	run_child(t_shell *shell,t_pipedata *pipedata, t_clist *cmd)
{
	int	fd_in;
	int fd_out;
	if(pipedata->child == 0)//is first command --> input stdin output pipe
	{
		fd_in = pipedata->fd_in;
		fd_out = pipedata->pipes[1];
		printf("1\n");
	}
	if(pipedata->child == pipedata->childs - 1)//its last so from pipe to stdout
	{
		fd_in = pipedata->pipes[2 * pipedata->child - 2];
		fd_out = pipedata->fd_out;
		printf("2\n");
	}
	else
	{
		fd_in = pipedata->pipes[2 * pipedata->child -2];//read end of previus cmd
		fd_out = pipedata->pipes[2 * pipedata->child + 1];//out to writre end of next cmd
	}
	close_all_pipes(pipedata, 2 * pipedata->child + 1, 2 * pipedata->child - 2);//+1 == write to -2 read from
	//now dup check built in or cmd 
	
	fd_in = execute_pipe_cmd(shell , cmd, fd_in, fd_out);
}	



int run_parent(t_pipedata *pipedata)
{//waits for all child to finish
	pid_t	pid;
	int		child_status;
	int		ret;
	close_all_pipes(pipedata, -1, -1);
	pipedata->child--;
	ret = 1;
	while(pipedata->child >= 0)
	{
		pid = waitpid(pipedata->pids[pipedata->child], &child_status,0);
		if(pid == pipedata->pids[pipedata->childs -1])//last cmd set ret to return of last cmd
		{
			if((pipedata->child == (pipedata->childs -1 )) && WIFEXITED(child_status))
				ret = WEXITSTATUS(child_status);
		}
		pipedata->child--;
	}
	return(ret);


}
/*have one function itterate over commands one 1.command one last one in between */
int execute_pipes(t_shell *shell)
{
	t_clist *cmd;
	t_pipedata	*pipedata;

	pipedata = malloc(sizeof(t_pipedata));
	init_pipe_data(shell, pipedata, 0,1);
	cmd = shell->clist;
	
	while(cmd)
	{
		pipedata->pids[pipedata->child] = fork();
		if(pipedata->pids[pipedata->child] == -1)
			return(perror("fork error"), errno);
		else if(pipedata->pids[pipedata->child] == 0)
			run_child(shell,pipedata, cmd);
		pipedata->child++;
		cmd = cmd->next;
	}
	run_parent(pipedata);
	free(pipedata);
	return(0);
}
