/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:51 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/04 16:52:28 by aeastman         ###   ########.fr       */
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

void checker(t_shell *shell)
{
	// check if we have any input at all (or tokens ?)
	if (!check_quotes(shell))
		return ;
	// check_pipes;
	count_pipes(shell);
	parser(shell);
}