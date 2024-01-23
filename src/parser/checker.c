/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:41:51 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 21:00:58 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_pipes(t_shell *shell)
{
	int	i;

	shell->n_pipes = 0;
	i = -1;
	while (shell->tokens[++i].token)
	{
		if (shell->tokens[i].type == PIPE)
			shell->n_pipes++;
	}
}

