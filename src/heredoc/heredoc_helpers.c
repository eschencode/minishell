/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:46:53 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/25 16:47:14 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_check(t_shell *shell, t_clist *cmd)
{
	if (cmd && cmd->cmd && cmd->cmd[1] && cmd->cmd[1][0] == '<' \
	&& cmd->cmd[1][1] == '<' && shell->num_tokens <= 3)
		return (1);
	return (0);
}

int	heredoc_create(void)
{
	int	fd;

	fd = open("src/heredoc/heredoc.txt", \
	O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	return (fd);
}

char	*get_heredoc_key(t_clist *cmd)
{
	char	*key;
	char	*new_str;

	key = cmd->cmd[2];
	new_str = ft_strdup(key);
	return (new_str);
}
