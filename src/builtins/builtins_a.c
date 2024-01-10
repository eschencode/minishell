/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:41:06 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/10 11:26:46 by aeastman         ###   ########.fr       */
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

int		export_syntax_check(char **str)
{
	int x;
	int count;

	if (ft_strchr(str[1], '=') == NULL)
		return (1);
	x = -1;
	count = 0;
	while (str[1][++x])
	{
		if (str[1][x] == '=')
			count++;
	}
	if (count != 1)
		return (1);
	if (ft_strlen(str[1]) >= 3)
		return (0);
	return (1);
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

bool	export_reassign(t_shell *shell, char *str)
{
	int y;

	y = env_find_row(shell, str);
	free(shell->env[y]);
	shell->env[y] = ft_strdup(str);
	return (true);
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

bool	ft_export(t_shell *shell, char **cmd, int fd_in, int fd_out)
{
	char	**env;
	int		old_len;

	ft_dup2(fd_in, fd_out);
	if (export_syntax_check(cmd))
		return (true);
	if (is_in_env(shell, cmd[1]))
		return(export_reassign(shell, cmd[1]));

	old_len = count_str_arr(shell->env);
	env = malloc(sizeof(char *) * (old_len + 1 + 1));
	str_arr_cpy(env, shell->env);
	free_double_str(shell->env);
	free(shell->env);
	env[old_len] = ft_strdup(cmd[1]);
	env[old_len + 1] = NULL;
	shell->env = env;
	return (true);
}
