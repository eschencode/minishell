/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:52:52 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/15 14:19:34 by leschenb         ###   ########.fr       */
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
	int i = 0;

	if(strcmp(shell->tokens[0].token, "pwd") == 0)
	{
		pwd_builtin(*shell);
		return(true);
	}
	if (strcmp(shell->clist->cmd[0], "cd") == 0)
	{
		cd(*shell);
		return(true);
	}
	if (strcmp(shell->clist->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd)));
	if(strcmp(shell->clist->cmd[0], "clear") == 0)
		{
			clearwindow();
			return(true);
		}
	if (strcmp(shell->clist->cmd[0], "printenv") == 0)
	{
		char **arr = envlist_to_array(shell->envlist);
		print_env(arr);
		return(true);
	}
	return(false);
}

// fork only for ./bla bla and builtins on parent
int executor(t_shell *shell)
{
	shell->exe.output_str = malloc(sizeof(char)* 100);
	if(shell->n_pipes > 0)
	{
		execute_pipes(shell);
	}
	else if(check_if_builtin(shell) == true)//change all printfs to write on output str better for pipes
		printf("%s\n",shell->exe.output_str);
	else
	{
		execute_externals(*shell);
	}
	return (0);
}
