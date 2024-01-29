/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:41:20 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 16:22:29 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_heredoc_key_2(t_clist *cmd)
{
	char	*key;
	char	*new_str;

	key = cmd->cmd[1] + 2;
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

int	ft_heredoc_2(t_clist *cmd, t_shell *shell, int i)
{
	int		heredoc_fd;
	char	*heredoc_key;

	/*if (cmd->cmd[1] && ft_strlen(cmd->cmd[1]) < 3)
	{
		printf("msh: 1parse error near newline\n");
		return (true);
	}*/
	printf("%s",shell->tokens[i].token);//filer
	heredoc_fd = heredoc_create();
	if (heredoc_fd == -1)
	{
		printf("error creating heredoc");
		return (true);
	}
	heredoc_key = get_heredoc_key_2(cmd);
	handle_heredoc_input(heredoc_fd, heredoc_key);
	free(cmd->cmd[1]);
	cmd->cmd[1] = ft_strdup("src/heredoc/heredoc.txt");
	cmd->cmd[2] = NULL;
	free(heredoc_key);
	return (0);
}



char	*get_heredoc_key(t_shell *shell, int i)
{
	char	*key;
	char	*new_str;
	
	key = NULL;//maybe bad idea but silences warnig
	if(ft_strlen(shell->tokens[i].token) > 2)
		key = ft_strtrim(shell->tokens[i].token,"<<");
	else
	{
		if(shell->tokens[i + 1].token)
			key = shell->tokens[i + 1].token;
	}
	//printf("key = %s",key);
	new_str = ft_strdup(key);
	return (new_str);
}




int	ft_heredoc(t_shell *shell, t_clist *cmd, int i)
{
	int		heredoc_fd;
	char	*heredoc_key;

	//if (shell->tokens[i + 1].token == NULL)
	//{
	//	printf("msh: 4parse error near newline\n");
	//	return (true);
	//}
	heredoc_fd = heredoc_create();
	if (heredoc_fd == -1)
	{
		printf("error creating heredoc");
		return (true);
	}
	heredoc_key = get_heredoc_key(shell, i);
	handle_heredoc_input(heredoc_fd, heredoc_key);
	free(cmd->cmd[1]);
	free(cmd->cmd[2]);
	cmd->cmd[1] = ft_strdup("src/heredoc/heredoc.txt");
	cmd->cmd[2] = NULL;
	free(heredoc_key);
	return (0);
}
