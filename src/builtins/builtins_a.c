/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:41:06 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/11 15:57:43 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void clearwindow(void)
{
	printf("\033[H\033[J");
}

bool ft_export(t_shell *shell, char **cmd)
{
	int x;
	int i;
	int len1;
	int len2;
	char *var;
	char *val;
	char *args;

	x = -1;
	len1 = 0;
	len2 = 0;
	args = cmd[1];
	while (args[++x] != '=')
		len1++;

	while (args[++x])
		len2++;
	var = malloc(sizeof(char) * (len1 + 1));
	val = malloc(sizeof(char) * (len2 + 1));
	x = -1;
	while (args[++x] != '=')
		var[x] = args[x];
	var[x] = '\0';
	i = -1;
	while (args[++x])
		val[++i] = args[x];
	val[++i] = '\0';
	insert_node_env(shell, new_node_env(shell, var, val));

	printf("var -> %s value -> %s\n", shell->envlist->variable, shell->envlist->value);
	return (true);
}