/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:08 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/08 09:01:56 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_clist *new_node(t_shell *shell)
{
	t_clist *clist_node;

	clist_node = (t_clist *)malloc(sizeof(t_clist));
	clist_node->n_args = 0;
	clist_node->next = NULL;

	return (clist_node);
}

void insert_node(t_shell *shell, t_clist *node)
{
	t_clist **tracer;

	tracer = &shell->clist;
	while (*tracer)
		tracer = &(*tracer)->next;
	node->next = *tracer;
	*tracer = node;
}

void tokens_retype(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == WORD)
		{
			// find and classify commands
			if (i == 0)
				shell->tokens[i].type = CMD;
			if (shell->tokens[i - 1].type != WORD && shell->tokens[i - 1].type != CMD && shell->tokens[i - 1].type != ARG)
				shell->tokens[i].type = CMD;
			// find and classify arguments
			if (shell->tokens[i - 1].type == CMD)
				shell->tokens[i].type = ARG;
			if (shell->tokens[i - 1].type == ARG)
				shell->tokens[i].type = ARG;
		}
	}
}

int	parser(t_shell *shell)
{
	shell->clist = NULL;
	tokens_retype(shell);
	// clist_init(shell);
	// clist_cmds_fill(shell);
	// clist_args_fill(shell);
	// print_clist(shell);
	return (0);
}
