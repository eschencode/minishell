/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:54:02 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/25 16:38:13 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_match_flag(char *str, int *nl_flag)
{
	int	x;

	x = 0;
	if (str[0] != '-')
		return (0);
	while (str[++x])
	{
		if (str[x] != 'n')
			return (0);
	}
	*nl_flag = 1;
	return (1); 
}

bool	ft_echo(t_clist *c_node, int fd_in, int fd_out)
{
	int		y;
	int		nl_flag;
	int		printed;
	char	*arg;

	ft_dup2(fd_in, fd_out);
	y = 0;
	printed = 0;
	nl_flag = 0;
	arg = c_node->cmd[++y];
	while (arg != NULL)
	{
		if (echo_match_flag(arg, &nl_flag) != 1)
		{
			if (y > 1 && printed > 0)
				ft_putstr_fd(" ", fd_out);
			printed += ft_strlen(arg);
			ft_putstr_fd(arg, fd_out);
		}
		arg = c_node->cmd[++y];
	}
	if (nl_flag != 1)
		ft_putstr_fd("\n", fd_out);
	return (true);
}
