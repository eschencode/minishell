/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:14 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/16 13:06:35 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void print_env(char **env_arry)
{
	int i = 0;
	while(env_arry[i])
	{
		printf("%s\n",env_arry[i]);
		i++;
	}
}

void ft_error(char *errmsg, t_shell shell)
{
	printf("ERROR %s\n",errmsg);
	//ft_free_all(shell.tokens, &shell);
}
