/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:41:15 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/25 15:35:10 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error_file(char *errmsg)
{
	ft_putendl_fd(errmsg, 2);
	return (0);
}

int	handle_file_error(t_shell *shell, int *fd_in, int *fd_out)
{
	ft_putendl_fd("No such file or directory", 2);
	shell->exit_code = 1;
	if (*fd_in == -1)
		close(*fd_in);
	if (*fd_out == -1)
		close(*fd_out);
	return (-1);
}

int	handle_right_redirection(t_shell *shell, int i, int *fd_out)
{
	if (i + 1 < shell->num_tokens && shell->tokens[i + 1].token && \
	shell->tokens[i].type == RIGHT)
		*fd_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT | \
		O_TRUNC, S_IRUSR | S_IWUSR);
	else if (i + 3 < shell->num_tokens && shell->tokens[i +3].token && \
	shell->tokens[i + 2].type == RIGHT)
		*fd_out = open(shell->tokens[i + 3].token, O_WRONLY | O_CREAT \
		| O_TRUNC, S_IRUSR | S_IWUSR);
	if (i + 1 < shell->num_tokens && shell->tokens[i + 1].token && \
	shell->tokens[i].type == RIGHT_RIGHT)
		*fd_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT \
		| O_APPEND, S_IRUSR | S_IWUSR);
	else if (i + 3 < shell->num_tokens && shell->tokens[i + 3].token && \
	shell->tokens[i + 2].type == RIGHT_RIGHT)
		*fd_out = open(shell->tokens[i + 3].token, O_WRONLY | O_CREAT \
		| O_APPEND, S_IRUSR | S_IWUSR);
	return (*fd_out);
}

int	handle_left_redirection(t_shell *shell, int i, int *fd_in)
{
	if (i + 1 < shell->num_tokens && shell->tokens[i + 1].token && \
	shell->tokens[i].type == LEFT)
		*fd_in = open(shell->tokens[i + 1].token, O_RDONLY);
	else if (i + 3 < shell->num_tokens && shell->tokens[i + 3].token && \
	shell->tokens[i + 2].type == LEFT)
		*fd_in = open(shell->tokens[i + 3].token, O_RDONLY);
	return (*fd_in);
}

int	check_redir(t_shell *shell, t_clist *cmd, int *fd_in, int *fd_out)
{
	int	i;

	i = 0;
	if (heredoc_check(cmd) != 0)
		ft_heredoc(shell, cmd);
	if (ft_strstr(shell->input_str, ">>") == NULL && ft_strstr(shell->\
	input_str, ">") == NULL && ft_strstr(shell->input_str, "<") == NULL)
		return (false);
	while (shell->tokens[i].token && \
	(ft_strcmp(shell->tokens[i].token, cmd->cmd[0]) != 0))
		i++;
	i++;
	if (shell->tokens[i].token == NULL)
		return (false);
	if (shell->tokens[i].token[0] == '-')
		i++;
	if (shell->tokens[i].token == NULL)
		return (false);
	while (shell->tokens[i].token && shell->tokens[i].type == ARG)
		i++;
	*fd_out = handle_right_redirection(shell, i, fd_out);
	*fd_in = handle_left_redirection(shell, i, fd_in);
	if (*fd_in == -1 || *fd_out == -1)
		return (handle_file_error(shell, fd_in, fd_out));
	return (0);
}
