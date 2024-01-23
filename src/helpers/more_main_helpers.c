/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_main_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:08:31 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 19:09:12 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	catch_eof_signal(t_shell *shell)
{
	if (shell->input_str == NULL)
		return (1);
	return (0);
}

int	exit_check(t_shell *shell)
{
	if (ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) != 0)
		return (0);
	if (shell->num_tokens > 2)
	{
		printf("too many arguments for exit\n");
		return (1);
	}
	if (shell->num_tokens <= 1)
		exit_routine(shell, 0);
	if (check_str_digit(shell->tokens[1].token) == 0)
		exit_routine(shell, (ft_atoi(shell->tokens[1].token)));
	return (1);
}