/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:52:52 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/10 12:02:32 by aeastman         ###   ########.fr       */
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
		if (shell->path != NULL && execve(shell->path, shell->clist->cmd, shell->env) == -1) //shell->env;
		{
			printf("command not found: %s\n",shell->clist->cmd[0]);
			ft_error("exec error");
			shell->exit_code = 127;
			exit(EXIT_FAILURE);
		}
	}
	else
	{// This code is executed in the parent process
		if (waitpid(child_pid, &child_status, 0) == -1)// Wait for the child process to complete
			ft_error("waitpid");
	}
	return 0;
}

bool check_if_builtin(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	if(strcmp(cmd->cmd[0], "pwd") == 0)
		return (pwd_builtin(fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "cd") == 0)
		return (cd(shell, cmd->cmd[1], fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd, fd_in, fd_out)));
	if(strcmp(cmd->cmd[0], "clear") == 0)
		return (clearwindow(fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(shell, cmd->cmd[1], fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "printenv") == 0)
		return(print_env(shell->env, fd_in, fd_out));
	if (strcmp(shell->clist->cmd[0], "echo") == 0)
		return(ft_echo(shell, shell->clist, fd_in, fd_out));
	if (ft_strncmp(shell->clist->cmd[1], "<<", 2) == 0)
 		return (ft_heredoc(cmd));
	return (false);
}


void handle_redirections(t_shell *shell, t_clist **cmd)
{
    shell->redirect_in = STDIN_FILENO;
    shell->redirect_out = STDOUT_FILENO;
    check_for_redirections_out(shell,*cmd);
    if (shell->redirect_in != STDIN_FILENO)
    {
        dup2(shell->redirect_in,STDIN_FILENO);
        close(shell->redirect_in);
    }
    if (shell->redirect_out != STDOUT_FILENO)
    {
        dup2(shell->redirect_out,STDOUT_FILENO);
        close(shell->redirect_out);
    }
}

void	restore_stdin_stdout(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin,STDIN_FILENO);
    dup2(saved_stdout,STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

// fork only for ./bla bla and builtins on parent
int	executor(t_shell *shell)
{
	int saved_stdin;
	int saved_stdout;
	t_clist **cmd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	cmd = &shell->clist;
	if(shell->n_pipes > 0)
	{
		execute_pipes(shell);
		return(0);
	}
	handle_redirections(shell, cmd);
	if(check_if_builtin(shell, *cmd, 0, 1) == false)
	{
		shell->path = exe_path(shell, shell->clist->cmd[0]);
		execute_externals(shell);
	}
	restore_stdin_stdout(saved_stdin, saved_stdout);
	return (0);
}
