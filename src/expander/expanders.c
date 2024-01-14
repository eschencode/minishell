/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:01:27 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/14 11:03:26 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_expanders(t_shell *shell)
{
	tilde_expander(shell);
	if (strstr(shell->input_str, "\"") != NULL || strstr(shell->input_str, "\'") != NULL)
		expander_quotes(shell);
}