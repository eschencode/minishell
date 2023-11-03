/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:51 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/03 14:38:23 by aeastman         ###   ########.fr       */
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
	while (shell->tokens[++i].token)
	{
		printf("token type -> %d\n", shell->tokens->type);
		if (shell->tokens[i].type == PIPE)
			shell->n_pipes++;
	}
}

void checker(t_shell *shell)
{
	if (!check_quotes(shell))
		return ;
	// check_pipes;
	count_pipes(shell);
	printf("pipes -> %d\n", shell->n_pipes);
	// parser(shell);
}