/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:00:10 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/29 14:12:50 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*dupplicates stdin + out too resets them after cmd execution*/
int	safe_dup(int *safe_in, int *safe_out)
{
	*safe_in = dup(STDIN_FILENO);
	if (*safe_in == -1)
		return (perror("dup error"), errno);
	*safe_out = dup(STDOUT_FILENO);
	if (*safe_out == -1)
		return (perror("dup error"), errno);
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	handle_builtin_cmd(t_shell *shell, t_clist *cmd, int in, int out)
{
	int	safe_in;
	int	safe_out;
	int	ret;

	ret = safe_dup(&safe_in, &safe_out);
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (pwd_builtin(shell, in, out));
	if (ft_strcmp(cmd->cmd[1], "cd") == 0)
		return (cd(shell, cmd->cmd[0], in, out));
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return ((ft_export(shell, shell->clist->cmd, in, out)));
	if (ft_strcmp(cmd->cmd[0], "clear") == 0)
		return (clearwindow(in, out));
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(shell, shell->clist->cmd[1]));
	if (ft_strcmp(cmd->cmd[0], "printenv") == 0)
		return (print_env(shell->env, in, out));
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(shell, cmd, in, out));
	ret = ft_dup2(safe_in, safe_out);
	return (ret);
}
