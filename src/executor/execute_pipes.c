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
/*have one function itterate over commands one 1.command one last one in between */
int execute_pipes(t_shell *shell)
{
	t_clist **cmd;
	cmd = &shell->clist;

	printf("cmd= %s\n", (*cmd)->cmd[0]);
	if(check_if_builtin(shell, *cmd) == false)
		first_pipe(shell, *cmd);
	cmd = &(*cmd)->next;
	printf("in pipe :%s:\n", shell->exe->output_str);
	shell->exe->current_cmd = 1;
	printf("cmd= %s\n", (*cmd)->cmd[0]);
	last_pipe(shell, *cmd);

}

int first_pipe(t_shell *shell, t_clist *cmd)
{
	pid_t pid;
	int child_status;

	if(pipe(shell->exe->pipe_fd) == -1)
	{
		printf("pipe error");
		exit(EXIT_FAILURE);
	}
	//close(shell.exe.pipe_fd[0]);
	pid = fork();
	if(pid == -1)
		printf("fork error");
	else if(pid == 0)//pid ==0 -> child procces
	{
		dup2(shell->exe->pipe_fd[1], STDOUT_FILENO);
		close(shell->exe->pipe_fd[1]);//closeend of pipe
		close(shell->exe->pipe_fd[0]);//closeend of pipe
		//close(shell->exe.pipe_fd[1]);//close write end because output is allredy redirected
		char *env[] = {NULL};
		if(execve(cmd->cmd[0], cmd->cmd, env) == -1)//shell->clist->cmd[0]
		{
			printf("exec error");
			//ft_error("exec error",shell);
			//exit(EXIT_FAILURE);
		}
	}
	else
	{//erverthing frome here is executed in parent procces
		if (waitpid(pid, &child_status, 0) == -1)// Wait for the child process to complete
			ft_error("waitpid",*shell);
		//close(shell->exe->pipe_fd[1]);
		//shell->exe->output_len = read(shell->exe->pipe_fd[0],shell->exe->output_str,sizeof(shell->exe->output_str));
		//shell->exe->output_str[shell->exe->output_len] = '\0';

		//if(shell->exe->output_len == -1)
		//	printf("read failed\n");
		close(shell->exe->pipe_fd[0]);
		close(shell->exe->pipe_fd[1]);//close read end of pipe
	}
}

int last_pipe(t_shell *shell, t_clist *cmd)
{
	pid_t child_pid;
	int child_status;

	child_pid = fork();
	printf("pid %d\n",child_pid);
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{// This code is executed in the child process
		dup2(shell->exe->pipe_fd[0], STDIN_FILENO);
		close(shell->exe->pipe_fd[0]);//close read end of pipe
		close(shell->exe->pipe_fd[1]);
		char *args[] = {cmd->cmd[0],cmd->cmd,NULL};
		char *env[] = {NULL};//*env  = envlist_to_array(shell.envlist);
		if (execve(cmd->cmd[0],args,env) == -1)
		{
			ft_error("exec error",*shell);
			exit(EXIT_FAILURE);
		}
	}
	else
	{// This code is executed in the parent process
		close(shell->exe->pipe_fd[1]);
		close(shell->exe->pipe_fd[0]);
		if (waitpid(child_pid, &child_status, 0) == -1)// Wait for the child process to complete
			ft_error("waitpid",*shell);
	}
	return 0;
}