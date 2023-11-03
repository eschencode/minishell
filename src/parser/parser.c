/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:08 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/03 16:04:18 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list *new_node(t_shell *shell)
{
	
}

t_clist *clist_init(t_shell *shell)
{
	int n_nodes;
	t_clist clist_head;

	n_nodes = shell->n_pipes + 1;


	return (clist_head);
}

int	parser(t_shell *shell)
{
	shell->clist = clist_init(shell);
}
