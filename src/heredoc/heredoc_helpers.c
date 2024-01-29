/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:46:53 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 16:08:15 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_check(t_shell *shell, t_clist *cmd)
{
	if (shell->num_tokens > 0 && cmd->cmd && cmd->cmd[1] && cmd->cmd[1][0] == '<' \
	&& cmd->cmd[1][1] == '<')
	{
		write(1,"2",1);
		return (1);
	}	
	return (0);
}

int	heredoc_create(void)
{
	int	fd;

	fd = open("src/heredoc/heredoc.txt", \
	O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	return (fd);
}

