/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:41:15 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/26 17:54:10 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_right_redirection(t_shell *shell, int i, int *fd_out)
{
	if (i + 1 < shell->num_tokens && shell->tokens[i + 1].token && \
	shell->tokens[i].type == RIGHT)
		*fd_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT | \
		O_TRUNC, S_IRUSR | S_IWUSR);
	return (0);
}

int	handle_left_redirection(t_shell *shell, int i, int *fd_in)
{
	if (i + 1 < shell->num_tokens && shell->tokens[i + 1].token && \
	shell->tokens[i].type == LEFT)
		*fd_in = open(shell->tokens[i + 1].token, O_RDONLY);
	return (0);
}

int	handle_right_right_redirection(t_shell *shell, int i, int *fd_out)
{
	if (i + 1 < shell->num_tokens && shell->tokens[i + 1].token && \
	shell->tokens[i].type == RIGHT_RIGHT)
		*fd_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT \
		| O_APPEND, S_IRUSR | S_IWUSR);
	return (0);
}

int	ft_find_right_pipe(t_shell *shell, t_clist *cmd)
{
	int	i;

	i = 0;
	while (ft_strcmp(shell->tokens[i].token, cmd->cmd[0]) != 0)
	{
		i++;
	}
	while (i > 0 && shell->tokens[i - 1].type != PIPE)
	{
		i--;
	}
	i++;
	return (i);
}

int	check_redir(t_shell *shell, t_clist *cmd, int *fd_in, int *fd_out)
{
	int	i;

	i = 0;
	if (heredoc_check(shell, cmd) == 1)
		ft_heredoc(shell, cmd);
	if (ft_strstr(shell->input_str, ">>") == NULL && ft_strstr(shell->\
	input_str, ">") == NULL && ft_strstr(shell->input_str, "<") == NULL)
		return (false);
	if (shell->n_pipes > 0)
	{
		i = ft_find_right_pipe(shell, cmd);
	}
	while (shell->tokens[i].token && shell->tokens[i].type != PIPE)
	{
		if (shell->tokens[i].type == RIGHT)
			handle_right_redirection(shell, i, fd_out);
		if (shell->tokens[i].type == LEFT)
			handle_left_redirection(shell, i, fd_in);
		if (shell->tokens[i].type == RIGHT_RIGHT)
			handle_right_right_redirection(shell, i, fd_out);
		if (*fd_in == -1 || *fd_out == -1)
			return (handle_file_error(shell, fd_in, fd_out));
		i++;
	}
	return (0);
}
