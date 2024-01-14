/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:51 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/14 10:56:24 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int exit_flag;
	char *val;
	t_clist **tracer;

	tracer = &shell->clist;
	exit_flag = 0;
	while (*tracer)
	{
		y = -1;
		while ((*tracer)->cmd[++y])
		{
			if ((*tracer)->cmd[y][0] == '$')
			{
				if (is_in_env(shell, (*tracer)->cmd[y] + 1))
				{
					val = env_get_val(shell, (*tracer)->cmd[y] + 1);
					free((*tracer)->cmd[y]);
					(*tracer)->cmd[y] = ft_strdup(val);
				}
				else if ((strcmp((*tracer)->cmd[y] + 1, "?") == 0) && exit_flag == 0)
				{
					val = ft_itoa(shell->exit_code);
					free((*tracer)->cmd[y]);
					(*tracer)->cmd[y] = val;
					exit_flag = 1;
				}
			}
		}
		tracer = &(*tracer)->next;
	}
}