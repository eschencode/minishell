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
		shell->exe->current_cmd = 0;
		//printf("cmd= %s\n", shell->clist->cmd[1]);
		if(check_if_builtin(shell) == false)
			first_pipe(shell);
		printf("in pipe :%s:\n", shell->exe->output_str);
		shell->exe->current_cmd = 1;
		printf("cmd= %s\n", shell->clist->cmd[0]);//cmd[0] = ./1 but cmd[2] = NULL
		last_pipe(shell);

}

int first_pipe(t_shell *shell)
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
		close(shell->exe->pipe_fd[0]);//close read end of pipe
		//close(shell->exe.pipe_fd[1]);//close write end because output is allredy redirected
		char *env[] = {NULL};
		if(execve(shell->clist->cmd[0], shell->clist->cmd, env) == -1)
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
		//add write part here after function ran
		close(shell->exe->pipe_fd[1]);
		//shell->exe.output_str = malloc(sizeof(char)* 100);
		shell->exe->output_len = read(shell->exe->pipe_fd[0],shell->exe->output_str,sizeof(shell->exe->output_str));
		shell->exe->output_str[shell->exe->output_len] = '\0';

		if(shell->exe->output_len == -1)
			printf("read failed\n");
		close(shell->exe->pipe_fd[0]);
	}

}

int last_pipe(t_shell *shell)
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
		int i = 0;
		printf("cmd= %s\n",shell->clist->cmd[1]);
		char *args[] = {shell->clist->cmd[1],shell->exe->output_str,NULL};
		printf("arg=:%s:\n",args[0]);
		printf("arg=:%s:\n",args[1]);
		char *env[] = {NULL};//*env  = envlist_to_array(shell.envlist);
		if (execve(shell->clist->cmd[shell->exe->current_cmd],args,env) == -1)
		{
			ft_error("exec error",*shell);
			exit(EXIT_FAILURE);
		}
	}
	else
	{// This code is executed in the parent process
		if (waitpid(child_pid, &child_status, 0) == -1)// Wait for the child process to complete
			ft_error("waitpid",*shell);
	}
	return 0;
}