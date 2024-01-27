/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:26:38 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/14 14:30:17 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	export_reassign(t_shell *shell, char *str)
{
	int	y;

	y = env_find_row(shell, str);
	free(shell->env[y]);
	shell->env[y] = ft_strdup(str);
	return (true);
}

int	export_syntax_check(char **str)
{
	int	x;
	int	count;

	if (str[1] == NULL)
		return (1);
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

bool	ft_export(t_shell *shell, char **cmd, int fd_in, int fd_out)
{
	char	**env;
	int		old_len;

	ft_dup2(fd_in, fd_out);
	if (export_syntax_check(cmd))
		return (true);
	if (is_in_env(shell, cmd[1]))
		return (export_reassign(shell, cmd[1]));
	old_len = count_str_arr(shell->env);
	env = malloc(sizeof(char *) * (old_len + 1 + 1));
	str_arr_cpy(env, shell->env);
	free_double_str(shell->env);
	free(shell->env);
	env[old_len] = ft_strdup(cmd[1]);
	env[old_len + 1] = NULL;
	shell->env = env;
	shell->exit_code = 0;
	return (true);
}
