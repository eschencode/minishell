/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:54:02 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/15 10:54:58 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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