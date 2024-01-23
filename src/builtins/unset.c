/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:07:36 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 16:55:27 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_env(t_shell *shell, char *str)
{
	int	n;
	int	x;
	int	y;

	y = -1;
	n = 0;
	while (str[n] && str[n] != '=')
		n++;
	while (shell->env[++y])
	{
		if (ft_strncmp(shell->env[y], str, n) == 0)
		{
			x = 0;
			while (shell->env[y][x] && shell->env[y][x] != '=')
				x++;
			if (n == x)
				return (1);
		}
	}
	return (0);
}

bool	ft_unset(t_shell *shell, char *cmd, int fd_in, int fd_out)
{
	int	x;
	int	y;

	ft_dup2(fd_in, fd_out);
	y = 0;
	while (shell->env[y])
		y++;
	if (!is_in_env(shell, cmd) || y == 0)
		return (true);
	x = 0;
	while (cmd[x] && cmd[x] != '=')
		x++;
	y = 0;
	while (strncmp(shell->env[y], cmd, x) != 0)
		y++;
	free(shell->env[y]);
	while (shell->env[y + 1])
	{
		shell->env[y] = shell->env[y + 1];
		y++;
	}
	shell->env[y] = NULL;
	return (true);
}

char	*env_get_val(t_shell *shell, char *var)
{
	int	y;
	int	x;
	int	n;

	n = ft_strlen(var);
	y = 0;
	while (shell->env[y] && (ft_strncmp(var, shell->env[y], n) != 0))
		y++;
	if (shell->env[y] == NULL)
		return (NULL);
	x = 0;
	while (shell->env[y][x] && shell->env[y][x] != '=')
		x++;
	x++;
	return (shell->env[y] + x);
}

int	env_get_id(t_shell *shell, char *var)
{
	int	y;
	int	n;

	n = ft_strlen(var);
	y = 0;
	while (shell->env[y] && (ft_strncmp(var, shell->env[y], n) != 0))
		y++;
	return (y);
}

bool	ft_penis(void)
{
	printf("c=======================================3\n");
	return (true);
}
