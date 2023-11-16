/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:52:52 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/16 17:47:40 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int execute_externals(t_shell shell)
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
		int i = 0;
		char *env[] = {NULL};//*env  = envlist_to_array(shell.envlist);
		if (execve(shell.clist->cmd[0],shell.clist->cmd,env) == -1)
		{
			ft_error("exec error",shell);
			exit(EXIT_FAILURE);
		}
	}
	else
	{// This code is executed in the parent process
		if (waitpid(child_pid, &child_status, 0) == -1)// Wait for the child process to complete 
			ft_error("waitpid",shell);
	}
	return 0;
}

bool check_if_builtin(t_shell *shell)
{
	if(strcmp(shell->tokens[0].token, "pwd") == 0)
		return(pwd_builtin(*shell));
	if (strcmp(shell->clist->cmd[0], "cd") == 0)
		return(cd(*shell));
	if (strcmp(shell->clist->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd)));
	if(strcmp(shell->clist->cmd[0], "clear") == 0)
		return (clearwindow());
	if (strcmp(shell->clist->cmd[0], "printenv") == 0)
		return(print_env(shell->env));
	return(false);
}

// fork only for ./bla bla and builtins on parent
int executor(t_shell *shell)
{
	if(shell->n_pipes > 0)
	{
		printf("n pipes = %d\n",shell->n_pipes);
		execute_pipes(*shell);
	}
	else if(check_if_builtin(shell) == false)
		execute_externals(*shell);
	return (0);
}
