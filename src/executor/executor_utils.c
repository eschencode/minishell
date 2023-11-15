/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:50:14 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/15 13:29:44 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

char **envlist_to_array(t_env *envlist)
{
	char **env_arry;
	int env_len;
	int i;
	t_env *head;
	head = envlist;
	env_len = 0;
	i = -1;

	while(head != NULL)
	{
		env_len++;
		head = head->next;
	}
	if((env_arry = (char**)malloc((env_len + 1)*sizeof(char *))) == NULL)
		printf("ERROR allocating env var array");
	head = envlist;
	env_len = 0;
	int j = 0;
	while(head != NULL)
	{
		env_len = ft_strlen(head->variable) + ft_strlen(head->value) + 2;
		env_arry[i++] = malloc(env_len * sizeof(char));
		while(head->variable[i])
		{
			env_arry[i][j] = head->variable[j];
			j++;
		}
		env_arry[i][j] = '=';
		j++;
		while(head->value[i])
		{
			env_arry[i][j] = head->variable[j];
			j++;
		}
		env_arry[i][j] = '\0';
	}
	return(env_arry);
}

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
