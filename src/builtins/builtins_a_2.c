/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:07:36 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/17 11:27:34 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_env(t_shell *shell, char *str)
{
	int n;
	int y;
	
	y = -1;
	n = 0;
	while (str[n] && str[n] != '=')
		n++;

	while (shell->env[++y])
	{
		if (strncmp(shell->env[y], str, n));
			return (1);
	}
	return (0);
}

bool	ft_unset(t_shell *shell, char **cmd)
{
	
}