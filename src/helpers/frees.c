/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:55:14 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 18:06:55 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != NULL)
	{
		printf("token %d: :%s: :%d:\n", tokens[i].id, \
		tokens[i].token, tokens[i].type);
		i++;
	}
}

void	ft_free_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != NULL)
	{
		free(tokens[i].token);
		i++;
	}
	free(tokens);
}

void	free_double_str(char **str)
{
	int	y;

	y = -1;
	while (str[++y])
		free(str[y]);
}

void	ft_free_clist(t_shell *shell)
{
	t_clist	**tracer;
	t_clist	*old_node;

	tracer = &shell->clist;
	while (*tracer)
	{
		old_node = *tracer;
		*tracer = (*tracer)->next;
		free_double_str(old_node->cmd);
		free(old_node->cmd);
		free(old_node);
	}
}

void	ft_free_all(t_tokens *tokens, t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->tokens != NULL)
	{
		while (tokens[++i].token != NULL)
			free(tokens[i].token);
		free(tokens);
	}
	if (shell->input_str != NULL)
		free(shell->input_str);
	free_env(shell);
	if (shell->cd_last_path)
		free(shell->cd_last_path);
	if (shell->exe_path)
		free(shell->exe_path);
	if (shell->path)
		free(shell->path);
}
