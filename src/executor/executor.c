/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:52:52 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 16:06:50 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_externals(t_shell *shell)
{
	pid_t	child_pid;
	int		child_status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (shell->exe_path == NULL)
			shell->exe_path = shell->clist->cmd[0];
		if (execve(shell->exe_path, shell->clist->cmd, shell->env) == -1)
		{
			ft_error("command not found");
			shell->exit_code = 127;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &child_status, 0);
	}
	return (0);
}

bool	check_if_builtin(t_shell *shell, t_clist *cmd, int fd_in, int fd_out)
{
	if (strcmp(cmd->cmd[0], "pwd") == 0)
		return (pwd_builtin(fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "cd") == 0)
		return (cd(shell, cmd->cmd[1], fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd, fd_in, fd_out)));
	if (strcmp(cmd->cmd[0], "clear") == 0)
		return (clearwindow(fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(shell, cmd->cmd[1], fd_in, fd_out));
	if (strcmp(cmd->cmd[0], "printenv") == 0)
		return (print_env(shell->env, fd_in, fd_out));
	if (strcmp(shell->clist->cmd[0], "echo") == 0)
		return (ft_echo(shell->clist, fd_in, fd_out));
	if (strcmp(shell->clist->cmd[0], "penis") == 0)
		return (ft_penis());
	return (false);
}


int	handle_redirections1(t_shell *shell, t_clist **cmd, int fd_in, int fd_out)
{
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (check_redirections(shell, *cmd, &fd_in, &fd_out) == -1)
		return (-1);
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (0);
}

void	restore_stdin_stdout(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

// fork only for ./bla bla and builtins on parent
int	executor(t_shell *shell)
{
	int		fd_in;
	int		fd_out;
	int		saved_stdin;
	int		saved_stdout;
	t_clist	**cmd;

	fd_in = 0;
	fd_out = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	cmd = &shell->clist;
	if (shell->n_pipes > 0)
	{
		execute_pipes(shell);
		return (0);
	}
	if (handle_redirections1(shell, cmd, fd_in, fd_out) == -1)
		return (0);
	if (check_if_builtin(shell, *cmd, 0, 1) == false)
	{
		exe_path(shell, shell->clist->cmd[0]);
		execute_externals(shell);
	}
	restore_stdin_stdout(saved_stdin, saved_stdout);
	return (0);
}
