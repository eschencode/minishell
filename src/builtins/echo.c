/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:54:02 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/21 14:03:53 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool    ft_echo(t_shell *shell, t_clist *c_node, int fd_in, int fd_out)
{
    int y;
    char *arg;
    ft_dup2(fd_in, fd_out);

    y = 0;
    while ((arg = c_node->cmd[++y]) != NULL)
    {
        if (y > 1)
            printf(" ");
        printf("%s", arg);
    }
    printf("\n");
    return (true);
}