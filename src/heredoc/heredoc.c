/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:41:20 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/24 16:56:29 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_check(t_clist *cmd)
{
	if (cmd && cmd->cmd && cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "<<") == 0)
		return (1);
	else
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

int	ft_heredoc(t_clist *cmd)
{
	int		heredoc_fd;
	char	*heredoc_key;

	if (cmd->cmd[2] && ft_strlen(cmd->cmd[2]) < 3)
	{
		printf("msh: parse error near newline\n");
		return (true);
	}
	heredoc_fd = heredoc_create();
	if (heredoc_fd == -1)
	{
		printf("error creating heredoc");
		return (true);
	}
	heredoc_key = get_heredoc_key(cmd);

	handle_heredoc_input(heredoc_fd, heredoc_key);

	free(cmd->cmd[1]);
	free(cmd->cmd[2]);
	cmd->cmd[1] = ft_strdup("src/heredoc/heredoc.txt");
	cmd->cmd[2] = NULL;
	free(heredoc_key);
	return (0);
}
