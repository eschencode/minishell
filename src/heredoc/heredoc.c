/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:41:20 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/03 16:40:51 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int heredoc_syntax_check(t_clist *cmd)
{
	if (ft_strlen(cmd->cmd[1]) < 3)
	{
		printf("msh: parse error near newline\n");
		return (1);
	}
	return (0);
}

int		heredoc_create(void)
{
	int fd;
	fd = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	return (fd);
}

char	*get_heredoc_key(t_clist *cmd)
{
	char *key;
	char *new_str;

	key = cmd->cmd[1];
	key = key + 2;
	new_str = ft_strdup(key);
	return (new_str);
}

bool	ft_heredoc(t_clist *cmd)
{
	int input_ret;
	int heredoc_fd;
	char *heredoc_key;
	char *heredoc_input;
	
	if (heredoc_syntax_check(cmd) == 1)
		return (true);
	heredoc_fd = heredoc_create();
	if (heredoc_fd == -1)
		return (true);
	heredoc_key = get_heredoc_key(cmd);
	heredoc_input = NULL;
	input_ret = -1;
	while (input_ret != 0)
	{
		heredoc_input = readline("heredoc> ");
		input_ret = ft_strncmp(heredoc_key, heredoc_input, ft_strlen(heredoc_input));
		if (input_ret != 0)
		{
			write(heredoc_fd, heredoc_input, ft_strlen(heredoc_input));
			write(heredoc_fd, "\n", 1);
		}
		free(heredoc_input);
	}
	free(cmd->cmd[1]);
	cmd->cmd[1] = ft_strdup("heredoc.txt");
	free(heredoc_key);
	return (false);
}