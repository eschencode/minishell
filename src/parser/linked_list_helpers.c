/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:13:40 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/25 16:33:02 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_clist	*new_node(void)
{
	t_clist	*clist_node;

	clist_node = (t_clist *)malloc(sizeof(t_clist));
	clist_node->n_args = 0;
	clist_node->next = NULL;
	return (clist_node);
}

void	insert_node(t_shell *shell, t_clist *node)
{
	t_clist	**tracer;

	tracer = &shell->clist;
	while (*tracer)
		tracer = &(*tracer)->next;
	node->next = *tracer;
	*tracer = node;
}

void	clist_init(t_shell *shell)
{
	int		i;
	t_clist	*node;

	i = -1;
	while (shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == CMD)
		{
			node = new_node();
			node->cmd_pos = i;
			insert_node(shell, node);
		}
		if (shell->tokens[i].type == ARG)
			node->n_args++;
	}
}

void	clist_args_fill(t_shell *shell)
{
	int		i;
	int		y;
	char	**str;
	t_clist	**tracer;

	tracer = &shell->clist;
	while (*tracer)
	{
		y = -1;
		str = malloc(sizeof(char *) * ((*tracer)->n_args + 2));
		i = (*tracer)->cmd_pos;
		while (i < shell->num_tokens && \
		(shell->tokens[i].type == CMD || shell->tokens[i].type == ARG))
		{
			if (shell->tokens[i].token != NULL)
				str[++y] = ft_strdup(shell->tokens[i].token);
			i++;
		}
		str[++y] = NULL;
		(*tracer)->cmd = str;
		tracer = &(*tracer)->next;
	}
}
