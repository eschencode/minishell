/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:41:20 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/21 15:01:23 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int heredoc_check(t_clist *cmd)
{
	if(cmd->cmd[1] && strcmp(cmd->cmd[1],"<<") == 0)
		return(1);
	else
		return(0);
}

int heredoc_syntax_check(t_clist *cmd)
{
	if(cmd->cmd[2] && ft_strlen(cmd->cmd[2]) < 3)
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
	
	key = cmd->cmd[2];
	new_str = ft_strdup(key);
	return (new_str);
}

int	ft_heredoc(t_clist *cmd)
{
	int input_ret;
	int heredoc_fd;
	char *heredoc_key;
	char *heredoc_input;
	if (heredoc_syntax_check(cmd) == 1)
		return (true);
	heredoc_fd = heredoc_create();
	if (heredoc_fd == -1)
		printf("error creating heredoc");
		//return (true);
	heredoc_key = get_heredoc_key(cmd);
	heredoc_input = NULL;
	input_ret = -1;
	while (input_ret != 0)
	{
		heredoc_input = readline("> ");
		input_ret = ft_strncmp(heredoc_key, heredoc_input, ft_strlen(heredoc_input));
		if (input_ret != 0)
		{
			write(heredoc_fd, heredoc_input, ft_strlen(heredoc_input));
			write(heredoc_fd, "\n", 1);
		}
		free(heredoc_input);
	}
	free(cmd->cmd[1]);
	free(cmd->cmd[2]);
	cmd->cmd[1] = ft_strdup("heredoc.txt");
	cmd->cmd[2] = NULL;
	free(heredoc_key);
	return (0);
}