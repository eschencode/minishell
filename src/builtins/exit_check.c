/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:49:40 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/10 11:35:03 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	print_exit_status(t_shell *shell, int fd_in, int fd_out)
{
	ft_dup2(fd_in, fd_out);
	printf("%d\n", shell->exit_code);
	return (true);
}