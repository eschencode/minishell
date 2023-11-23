/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:41:06 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/23 15:18:59 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	clearwindow(void)
{
	printf("\033[H\033[J");
	return (true);
}

int	count_str_arr(char **str)
{
	int	y;

	y = 0;
	while (str[y])
		y++;
	return (y);
}

void	str_arr_cpy(char **new, char **old)
{
	int	y;

	y = -1;
	while (old[++y])
	{
		new[y] = malloc(sizeof(char) * (ft_strlen(old[y]) + 1));
		ft_strlcpy(new[y], old[y], ft_strlen(old[y]));
	}
}

void	free_env(t_shell *shell)
{
	int	y;

	y = -1;
	if (shell->env_flag)
	{
		while (shell->env[++y])
			free(shell->env[y]);
		free(shell->env);
	}
}

bool	ft_export(t_shell *shell, char **cmd)
{
	char	**env;
	int		old_len;

	if (is_in_env(shell, cmd[1]))
	{
		printf("found matching in env\n");
		return (true);
	}
	old_len = count_str_arr(shell->env);
	env = malloc(sizeof(char *) * (old_len + 1 + 1));
	str_arr_cpy(env, shell->env);
	free(shell->env);
	env[old_len] = malloc(sizeof(char) * (ft_strlen(cmd[1]) + 1));
	ft_strlcpy(env[old_len], cmd[1], ft_strlen(cmd[1]));
	env[old_len + 1] = NULL;
	shell->env = env;
	return (true);
}
