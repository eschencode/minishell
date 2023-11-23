/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:51 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/23 16:46:46 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_quotes(t_shell *shell)
{
	int i;
	int n_quotes;

	i = -1;
	n_quotes = 0;
	while (shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == DOUBLE_QUOTE || \
		shell->tokens[i].type == SINGLE_QUOTE)
			n_quotes++;
	}
	if (!(n_quotes % 2))
		return (1);
	return (0);
}

void count_pipes(t_shell *shell)
{
	int i;

	shell->n_pipes = 0;
	i = -1;
	while (shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == PIPE)
			shell->n_pipes++;
	}
}

void ft_expander(t_shell *shell)
{
	int y;
	t_clist **tracer;

	tracer = &shell->clist;
	while (*tracer)
	{
		y = -1;
		while ((*tracer)->cmd[++y])
		{
			if ((*tracer)->cmd[y][0] == '$')
			{
				if (is_in_env(shell, (*tracer)->cmd[y] + 1))
					(*tracer)->cmd[y] = env_get_val(shell, (*tracer)->cmd[y] + 1);
			}
		}
		tracer = &(*tracer)->next;
	}
}

void checker(t_shell *shell)
{
	count_pipes(shell);
}