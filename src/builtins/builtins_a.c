/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:41:06 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/14 14:30:11 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	clearwindow(int fd_in, int fd_out)
{
	ft_dup2(fd_in, fd_out);
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
	while (shell->env[++y])
		free(shell->env[y]);
	free(shell->env);
}

int env_find_row(t_shell *shell, char *str)
{
		int n;
    int x;
	int y;

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
                return (y);
        }
	}
	return (-1);
}

void	push_to_env(t_shell *shell, char *str)
{
	int old_len;
	char **env;
	
	old_len = count_str_arr(shell->env);
	env = malloc(sizeof(char *) * (old_len + 1 + 1));
	str_arr_cpy(env, shell->env);
	free_double_str(shell->env);
	free(shell->env);
	env[old_len] = ft_strdup(str);
	env[old_len + 1] = NULL;
	shell->env = env;
}
