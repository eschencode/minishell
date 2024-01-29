/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_main_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:08:31 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 13:26:04 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_check(t_shell *shell)
{
	if (ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) != 0)
		return (0);
	if (shell->num_tokens > 2)
	{
		shell->exit_code = 1;
		printf("too many arguments for exit\n");
		return (1);
	}
	if (shell->num_tokens <= 1)
		exit_routine(shell, 0);
	if (check_str_digit(shell->tokens[1].token) == 0)
		exit_routine(shell, (ft_atoi(shell->tokens[1].token)));
	else
		shell->exit_code = 156;
	return (1);
}

int	eval_input_error(t_shell *shell)
{
	if (shell->input_str[0] == '\0' \
	|| count_quotes(shell->input_str) % 2 != 0 \
	|| validate_input_str(shell) == 1)
	{
		return (1);
	}
	return (0);
}
