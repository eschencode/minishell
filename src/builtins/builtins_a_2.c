/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:07:36 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/15 10:26:48 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_env(t_shell *shell, char *str)
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
                return (1);
        }
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

int     validate_n_flag(char *str)
{
    int x;

    x = 0;
    while (str[++x] && str[x] != ' ' && str[x] != '\t')
    {
        if (str[x] != 'n')
            return (0);
    }
    return (1);
}

bool    ft_echo(t_shell *shell, t_clist *c_node, int fd_in, int fd_out)
{
    int y;
    int n;
    int n_flag;
    int word_flag;
    int dont_print;
    char *var;
    char *n_str;
    char **cmd;

    ft_dup2(fd_in, fd_out);
    y = 0;
    n_flag = 0;
    word_flag = 0;
    n = c_node->n_args;
    cmd = c_node->cmd;
    while (cmd[++y])
    {
        dont_print = 0;
        if ((n_str = strstr(cmd[y], "-n")) != NULL)
        {
            if (validate_n_flag(n_str) == 1)
            {
                n_flag = 1;
                if (word_flag == 0)
                    dont_print = 1;
            }
        }
        if ((var = strstr(cmd[y], "$")) != NULL)
        {
            if (env_get_val(shell, var) != NULL)
                printf("%s", cmd[y]);
        }
        else
        {
            if (dont_print == 0)
            {
                printf("%s", cmd[y]);
                word_flag = 1;
                if (n != 1)
                    printf(" ");
            }
        }
        n--;
    }
    if (n_flag == 0)
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

bool ft_penis(void)
{
    printf("c=======================================3\n");
    return (true);
}