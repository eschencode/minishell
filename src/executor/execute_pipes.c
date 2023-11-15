/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:00:22 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/15 18:46:59 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"
/*have one function itterate over commands one 1.command one last one in between */
int execute_pipes(t_shell shell)
{
	
		printf("1\n");
		shell.pipes.current_cmd = 0;
		first_pipe(shell);
		
		printf("in pipe :%s:\n",shell.pipes.output_str);
		//shell.pipes.current_cmd = 1;
		//last_pipe(shell);
	
}

int first_pipe(t_shell shell)
{	
	printf("2\n");
	pid_t pid;
	int child_status;
	
	if(pipe(shell.pipes.pipe_fd) == -1)
	{
		printf("pipe error");
		exit(EXIT_FAILURE);
	}
	//close(shell.pipes.pipe_fd[0]);
	pid = fork();
	if(pid == -1)
		printf("fork error");
	else if(pid == 0)//pid ==0 -> child procces 
	{
		close(shell.pipes.pipe_fd[0]);//close read end of pipe
		dup2(shell.pipes.pipe_fd[1], STDOUT_FILENO);
		close(shell.pipes.pipe_fd[1]);//close write end because output is allredy redirected
		char *env[] = {NULL};
		if(execve(shell.clist->cmd[0], shell.clist->cmd, env) == -1)
		{
			printf("exec error");
			//ft_error("exec error",shell);
			//exit(EXIT_FAILURE);
		}
	}
	else
	{//erverthing frome here is executed in parent procces
		close(shell.pipes.pipe_fd[1]);
		if (waitpid(pid, &child_status, 0) == -1)// Wait for the child process to complete 
			ft_error("waitpid",shell);
		//add write part here after function ran 
		shell.pipes.output_str = malloc(sizeof(char)* 100);
		shell.pipes.output_len = read(shell.pipes.pipe_fd[0],shell.pipes.output_str,sizeof(100));
		if(shell.pipes.output_len == -1)
		{
			printf("read fail");
		}
		close(shell.pipes.pipe_fd[0]);
	}
	
}

int last_pipe(t_shell shell)
{
	printf("3\n");
	char readbuffer[187];
	pid_t pid;
	int child_status;
	if(pipe(shell.pipes.pipe_fd) == -1)
	{
		printf("pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if(pid == -1)
		printf("fork error");
	else if(pid == 0)//pid ==0 -> child procces 
	{
		close(shell.pipes.pipe_fd[1]);//close write end of pipe
		char *env[] = {NULL};
		int bytes_read = read(shell.pipes.pipe_fd[0], readbuffer,sizeof(readbuffer));
		readbuffer[bytes_read] = '\0';
		printf("in pipe :%s:\n",readbuffer);
		if(execve(shell.clist->cmd[shell.pipes.current_cmd], readbuffer , env) == -1)
		{
			ft_error("exec error",shell);
			exit(EXIT_FAILURE);
		}
		
	
			if (waitpid(pid, &child_status, 0) == -1)// Wait for the child process to complete 
				ft_error("waitpid",shell);
	}
}



