/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:36:35 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/11 15:30:16 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this file contains functions that can be used to generate and delete linked lists
#include "../../include/minishell.h"

t_env *new_node_env(t_shell *shell, char *var, char *val)
{
	t_env *env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	env_node->variable = var;
	env_node->value = val;
	env_node->next = NULL;

	return (env_node);
}

void insert_node_env(t_shell *shell, t_env *node)
{
	t_env **tracer;

	tracer = &shell->envlist;
	while (*tracer)
		tracer = &(*tracer)->next;
	node->next = *tracer;
	*tracer = node;
}