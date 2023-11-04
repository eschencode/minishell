/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:08 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/04 16:54:11 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_clist *new_node(t_shell *shell)
{
	t_clist *clist_node;

	clist_node = (t_clist *)malloc(sizeof(t_clist));
	clist_node->external_flag = 1;
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

void clist_init(t_shell *shell)
{
	int n_nodes;
	t_clist *node;

	n_nodes = (shell->n_pipes + 1) + 1;

	while (--n_nodes)
	{
		node = new_node(shell);
		insert_node(shell, node);
	}

}

int	parser(t_shell *shell)
{
	shell->clist = NULL;
	clist_init(shell);
	clist_cmds_fill(shell);
	// clist_args_fill(shell);

	t_clist *clist = shell->clist;
	while (clist->next)
	{
		printf("args->%d\n", clist->external_flag);
		clist = clist->next;
	}
	printf("args->%d\n", clist->external_flag);
	return (0);
}
