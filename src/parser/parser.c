/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:08 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/15 18:55:38 by leschenb         ###   ########.fr       */
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
			// find and classify commands (else if to prevent invalid reads)
			if (i == 0)
				shell->tokens[i].type = CMD;
			else if (shell->tokens[i - 1].type != WORD && shell->tokens[i - 1].type != CMD && shell->tokens[i - 1].type != ARG)
				shell->tokens[i].type = CMD;
			// find and classify arguments
			else if (shell->tokens[i - 1].type == CMD)
				shell->tokens[i].type = ARG;
			else if (shell->tokens[i - 1].type == ARG)
				shell->tokens[i].type = ARG;
		}
	}
}

void clist_init(t_shell *shell)
{
	int i;
	int y;
	t_clist *node;

	i = -1;
	y = -1;

	// created nodes for each CMD and adds Command str pointer to each node
	while (shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == CMD)
		{
			node = new_node(shell);
			node->cmd_pos = i;
			insert_node(shell, node);
		}
		if (shell->tokens[i].type == ARG)
			node->n_args++;
	}
}

void clist_args_fill(t_shell *shell)
{
	int i;
	int y;
	char **str;
	t_clist **tracer;

	tracer = &shell->clist;
	while (*tracer)
	{
		y = -1;
		str = malloc(sizeof(char *) * ((*tracer)->n_args + 2));
		i = (*tracer)->cmd_pos;
		while (shell->tokens[i].type == CMD || shell->tokens[i].type == ARG)
		{
			str[++y] = shell->tokens[i].token;//added str dup because i had problem acces cmd[1]
			i++;
		}
		str[++y] = NULL;
		(*tracer)->cmd = str;
		tracer = &(*tracer)->next;
	}
}

void print_clist(t_shell *shell)
{
	int y;
	t_clist **tracer = &shell->clist;

	while (*tracer)
	{
		y = -1;
		printf("command ->");
		while ((*tracer)->cmd[++y])
			printf(" %s", (*tracer)->cmd[y]);
		tracer = &(*tracer)->next;
		printf("\n");
	}
}

int	parser(t_shell *shell)
{
	shell->clist = NULL;
	tokens_retype(shell);
	clist_init(shell);
	clist_args_fill(shell);
	printf("cmd= %s\n", shell->clist->cmd[1]);
	print_clist(shell);
	executor(shell);
	return (0);
}
