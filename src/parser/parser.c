/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:08 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 21:12:13 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_for_redirects(t_shell *shell, int *i)
{
	if (shell->tokens[*i].type == LEFT_LEFT)
	{
		if (ft_strlen(shell->tokens[*i].token) > 2)
			shell->tokens[*i].type = LEFT_LEFT;
		else
			shell->tokens[*i + 1].type = FILE_NAME;
	}
	else if (shell->tokens[*i].type == RIGHT || \
	shell->tokens[*i].type == RIGHT_RIGHT || shell->tokens[*i].type == LEFT)
	{
		if (shell->tokens[++*i].token)
			shell->tokens[*i].type = FILE_NAME;
	}
}

void	tokens_retype(t_shell *shell)
{
	int	i;

	i = -1;
	while (i < shell->num_tokens && shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == WORD)
		{
			if (i == 0)
				shell->tokens[i].type = CMD;
			else if (shell->tokens[i - 1].type != WORD \
			&& shell->tokens[i - 1].type != CMD && \
			shell->tokens[i - 1].type != ARG)
				shell->tokens[i].type = CMD;
			else if (shell->tokens[i - 1].type == CMD)
				shell->tokens[i].type = ARG;
			else if (shell->tokens[i - 1].type == ARG)
				shell->tokens[i].type = ARG;
		}
		check_for_redirects(shell, &i);
	}
}

int	parser(t_shell *shell)
{
	shell->clist = NULL;
	count_pipes(shell);
	tokens_retype(shell);
	clist_init(shell);
	clist_args_fill(shell);
	return (0);
}
