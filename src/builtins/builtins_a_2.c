/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:07:36 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/19 17:54:31 by aeastman         ###   ########.fr       */
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
		if (!strncmp(shell->env[y], str, n))
			return (1);
	}
	return (0);
}

bool ft_unset(t_shell *shell, char *cmd)
{
    int x;
    int y;

    y = 0;
    while (shell->env[y])
        y++;
    if (!is_in_env(shell, cmd) || y == 0)
        return true;
    x = 0;
    while (cmd[x] && cmd[x] != '=')
        x++;
    y = 0;
    while (strncmp(shell->env[y], cmd, x) != 0)
        y++;
    // Free the memory for the removed environment variable
    free(shell->env[y]);
    while (shell->env[y + 1])
    {
        shell->env[y] = shell->env[y + 1];
        y++;
    }
    shell->env[y] = NULL;

    return true;
}

bool    ft_echo(char *cmd)
{
    printf("%s\n", cmd);
    return (true);
}