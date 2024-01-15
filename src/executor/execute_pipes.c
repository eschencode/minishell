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

bool	check_redirections_check(t_shell *shell)
{
	int	i;
	i = 0;
	if (strstr(shell->input_str, ">>") == NULL && strstr(shell->input_str, ">") == NULL && strstr(shell->input_str, "<") == NULL)
		return (false);

	while(shell->tokens[i].token && (strcmp(shell->tokens[i].token, shell->saved_cmd) != 0))
		i++;
	i++;
	if(shell->tokens[i].token[0] == '-') //skips options
		i++;
	if (shell->tokens[i].type == RIGHT)
		return(true);
	else if (shell->tokens[i + 2].type == RIGHT)
		return(true);
	if(shell->tokens[i].type == LEFT)
		return(true);
	else if (shell->tokens[i + 2].type == LEFT)
		return(true);
	if(shell->tokens[i].type == RIGHT_RIGHT)
		return(true);
	else if(shell->tokens[i + 2].type == RIGHT_RIGHT)
		return(true);
	return(false);
}

int execute_cmd(t_shell *shell,t_clist *cmd, int fd_in, int fd_out)
{
	int error_check;
	if (check_redirections_check(shell) == true)
		check_redirections_pipes(shell, &fd_in, &fd_out);

	error_check = ft_dup2(fd_in, fd_out);

	if(!cmd->cmd[0])
	{
		error_check = -1;
		return(error_check);
	}
	if(execve(cmd->cmd[0],cmd->cmd, shell->env) == -1)//
	{
		printf("command not found: %s\n",cmd->cmd[0]);
		//ft_error("exec error",*shell);
		exit(EXIT_FAILURE);
	}
	return (0);
}


bool	check_redirections_pipes(t_shell *shell,int *fd_in, int *fd_out)
{
	int	i;
	i = 0;
	while(shell->tokens[i].token && (strcmp(shell->tokens[i].token, shell->saved_cmd) != 0))
		i++;
	i++;
	if(shell->tokens[i].token[0] == '-') //skips options
		i++;
	while(shell->tokens[i].token && shell->tokens[i].type == ARG)
        i++;
	if (shell->tokens[i].type == RIGHT)
		*fd_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (shell->tokens[i + 2].type == RIGHT)
		*fd_out  = open(shell->tokens[i + 3].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(shell->tokens[i].type == LEFT)
		*fd_in = open(shell->tokens[i + 1].token, O_RDONLY);
	else if (shell->tokens[i + 2].type == LEFT)
		*fd_in = open(shell->tokens[i + 3].token, O_RDONLY);
	if(shell->tokens[i].type == RIGHT_RIGHT)
		*fd_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	else if(shell->tokens[i + 2].type == RIGHT_RIGHT)
		*fd_out = open(shell->tokens[i + 3].token, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if(*fd_out == -1 || *fd_in == -1)
		printf("error accesing file\n");//add more eroro here probaby clos the fd too :()
	return(0);
}


bool check_if_builtin1(t_clist *cmd)
{
	if(strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "cd") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "export") == 0)
		return (true);
	if(strcmp(cmd->cmd[0], "clear") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "unset") == 0)
		return (true);
	if (strcmp(cmd->cmd[0], "printenv") == 0)
		return(true);
	if (strcmp(cmd->cmd[0], "echo") == 0)
		return(true);
	return (false);
}
/*check for built in or external set signals  */
int	execute_pipe_cmd(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	int ret;

	ret = 0;

	if (check_if_builtin1(cmd) == true)
	{
		handle_builtin_cmd(shell , cmd, fd_in, fd_out);
	}
	else
	{
		exe_path(shell, cmd->cmd[0]);//free later ?
		if(shell->exe_path != NULL)
		{
			shell->saved_cmd = malloc(sizeof(char) * ft_strlen(cmd->cmd[0]));
			shell->saved_cmd = ft_strdup(cmd->cmd[0]);
			cmd->cmd[0] = shell->exe_path;
			//printf("cmd = %s and savedcmd %s",cmd->cmd[0],shell->saved_cmd);
		}
		ret = execute_cmd(shell,cmd,fd_in,fd_out);
	}
	return (ret);
}

int init_pipe_data(t_shell *shell, t_pipedata *pipedata, int fd_in, int fd_out)
{
	t_clist *ptr;
	int i;

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
/*sets up the filedisriptors -->execute_pipe_cmd*/
int	run_child(t_shell *shell,t_pipedata *pipedata, t_clist *cmd)
{
	int	fd_in;
	int fd_out;
	if(pipedata->child == 0)//is first command --> input stdin output pipe
	{
		fd_in = pipedata->fd_in;
		fd_out = pipedata->pipes[1];
	}
	if(pipedata->child == pipedata->childs - 1)//its last so from pipe to stdout
	{
		fd_in = pipedata->pipes[2 * pipedata->child - 2];
		fd_out = pipedata->fd_out;
	}
	else
	{
		fd_in = pipedata->pipes[2 * pipedata->child -2];//read end of previus cmd
		fd_out = pipedata->pipes[2 * pipedata->child + 1];//out to writre end of next cmd
	}
	close_all_pipes(pipedata, 2 * pipedata->child + 1, 2 * pipedata->child - 2);//+1 == write to -2 read from
	fd_in = execute_pipe_cmd(shell , cmd, fd_in, fd_out);
	exit(fd_in);
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