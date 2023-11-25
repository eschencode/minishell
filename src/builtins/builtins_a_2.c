/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:07:36 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/25 14:06:54 by aeastman         ###   ########.fr       */
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
		if (strncmp(shell->env[y], str, n) == 0)
			return (1);
	}
	return (0);
}

bool ft_unset(t_shell *shell, char *cmd, int fd_in, int fd_out)
{
    int x;
    int y;

    ft_dup2(fd_in, fd_out);
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

bool    ft_echo(t_clist *c_node, int fd_in, int fd_out)
{
    int y;
    int n;
    char **cmd;

    ft_dup2(fd_in, fd_out);
    y = 0;
    n = c_node->n_args;
    cmd = c_node->cmd;
    while (cmd[++y])
    {
        printf("%s", cmd[y]);
        if (n != 1)
            printf(" ");
        n--;
    }
    printf("\n");
    return (true);
}

char *env_get_val(t_shell *shell, char *var)
{
    int y;
    int x;
    int n;
    
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

int env_get_id(t_shell *shell, char *var)
{
    int y;
    int n;
    
    n = ft_strlen(var);
    y = 0;
    while (shell->env[y] && (ft_strncmp(var, shell->env[y], n) != 0))
        y++;
    return (y);
}

int get_val_offset(char *str)
{
    int x;

    printf("str -> %s\n", str);
    x = -1;
    while (str[x] != '=')
        x++;
    x++;
    return (x);
}