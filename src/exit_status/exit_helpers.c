/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:48:27 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/24 19:38:03 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	push_exit_code(t_shell *shell, int child_status)
{
	if (WIFEXITED(child_status))
		shell->exit_code = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
		shell->exit_code = 128 + WTERMSIG(child_status);
}
