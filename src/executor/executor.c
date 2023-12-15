/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:52:52 by aeastman          #+#    #+#             */
/*   Updated: 2023/12/11 16:23:53 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"


int execute_externals(t_shell *shell)
{
	pid_t child_pid;
	int child_status;
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{// This code is executed in the child process
		if (execve(shell->clist->cmd[0],shell->clist->cmd,shell->env ) == -1)//shell->env;
		{
			printf("command not found: %s\n",shell->clist->cmd[0]);
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

bool check_if_builtin(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	char *test;
	if(strcmp(cmd->cmd[0], "pwd") == 0)
		return (pwd_builtin(cmd, fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "cd") == 0)
		return (cd(*shell));
	if (strcmp(cmd->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd, fd_in, fd_out)));
	if(strcmp(cmd->cmd[0], "clear") == 0)
		return (clearwindow(fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(shell, cmd->cmd[1], fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "printenv") == 0)
		return(print_env(shell->env, fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "echo") == 0)
		return(ft_echo(shell->clist, fd_in, fd_out));
	// printf("debug -> %s\n", shell->clist->cmd[1]);
	// print_clist(shell);
	// if (ft_strncmp(shell->clist->cmd[1], "<<", 2) == 0)
 	// 	return (ft_heredoc(shell, cmd));
	return (false);
}

// fork only for ./bla bla and builtins on parent
int executor(t_shell *shell)
{
	char *path;
	t_clist **cmd;

	cmd = &shell->clist;
	if(shell->n_pipes > 0)
	{
		execute_pipes(shell);
		return(0);
	}
	else
	{
		if(check_if_builtin(shell, *cmd, 0, 1) == false)
		{
			check_for_redirections(shell,*cmd);
			path = exe_path(shell, shell->clist->cmd[0]);
			if(path != NULL)
			{
				shell->clist->cmd[0] = path;
			}
			execute_externals(shell);
		}
	}
	return (0);
}

bool check_for_redirections(t_shell *shell, t_clist *cmd)
{
	int i = 0;
	int fd;
	while(shell->tokens[i].token )
	{
		if(strcmp(shell->tokens[i].token, cmd->cmd[0]) == 0)
		{
			if (shell->tokens[i].type == RIGHT)
			{
				printf("RIGHT token[%d]=%s\n",i,shell->tokens[i].token);
				return(true);
			}
			else if(shell->tokens[i + 1].type == LEFT)
			{
				printf(" LEFT token[%d]=%s\n file to open = %s\n",i,shell->tokens[i].token, shell->tokens[i +2].token);
				fd = open(shell->tokens[i + 2].token, O_RDONLY);
				if(fd == -1)
				{
					printf("error opening file:%s",shell->tokens[i + 2].token);
					close(fd);
				}
				dup2(fd,STDIN_FILENO);
				close(fd);
				return(true);
			}
			if(shell->tokens[i].type == RIGHT_RIGHT)
			{
				printf("RIGHT_RIGHT token[%d]=%s\n",i,shell->tokens[i].token);
				
				return(true);
			}
		}
		i++;
		}
	return(false);
}