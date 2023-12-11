/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:41:20 by aeastman          #+#    #+#             */
/*   Updated: 2023/12/11 16:22:00 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int heredoc_syntax_check(t_clist *cmd)
{
	if (ft_strlen(cmd->cmd[2]) < 1)
		return (1);
	
	printf("parse error near `\n'");
	return (0);
}

bool	ft_heredoc(t_shell *shell, t_clist *cmd)
{
	if (heredoc_syntax_check(cmd) == 1)
		return (true);
	
	return (true);
}