/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:41:20 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 21:06:16 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_heredoc_input(int heredoc_fd, char *heredoc_key)
{
	int		input_ret;
	char	*heredoc_input;

	input_ret = -1;
	heredoc_input = NULL;
	while (input_ret != 0)
	{
		heredoc_input = readline("> ");
		input_ret = ft_strncmp(heredoc_key, heredoc_input, \
		ft_strlen(heredoc_key));
		if (input_ret != 0)
		{
			write(heredoc_fd, heredoc_input, ft_strlen(heredoc_input));
			write(heredoc_fd, "\n", 1);
		}
		free(heredoc_input);
	}
	return (0);
}

char	*get_heredoc_key(t_shell *shell, int i)
{
	char	*key;
	char	*new_str;

	key = NULL;
	if (ft_strlen(shell->tokens[i].token) > 2)
		key = ft_strtrim(shell->tokens[i].token, "<<");
	else
	{
		if (shell->tokens[i + 1].token)
			key = shell->tokens[i + 1].token;
	}
	new_str = ft_strdup(key);
	return (new_str);
}

void	add_file_after_cat(t_shell *shell, t_clist *cmd)
{
	if (shell->num_tokens == 3)
	{
		free(cmd->cmd[1]);
		free(cmd->cmd[2]);
	}
	if (shell->num_tokens == 2)
		free(cmd->cmd[1]);
	cmd->cmd[1] = ft_strdup("src/heredoc/heredoc.txt");
	cmd->cmd[2] = NULL;
}

int	ft_heredoc(t_shell *shell, t_clist *cmd, int i)
{
	int		heredoc_fd;
	char	*heredoc_key;

	heredoc_fd = heredoc_create();
	if (heredoc_fd == -1)
	{
		printf("error creating heredoc");
		return (true);
	}
	heredoc_key = get_heredoc_key(shell, i);
	handle_heredoc_input(heredoc_fd, heredoc_key);
	add_file_after_cat(shell, cmd);
	print_clist(shell->clist);
	free(heredoc_key);
	return (0);
}
