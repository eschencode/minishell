/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:57:14 by aeastman          #+#    #+#             */
/*   Updated: 2023/12/16 15:44:30 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_realloc(char *str, int size)
{
	char *new_str;
	int old_size;

	old_size = ft_strlen(str);
	new_str = malloc(sizeof(char) * (old_size + size + 1));
	ft_strlcpy(new_str, str, old_size);
	free(str);
	return (new_str);
}

void	expander_quotes(t_shell *shell)
{
	int i;
	char *first_string;
	char *token_str;

	i = -1;
	first_string = NULL;
	while (shell->tokens[++i].token)
	{
		token_str = shell->tokens[i].token;
		if (first_string == NULL && ft_strchr(token_str, '\"') != NULL)
		{
			first_string = token_str;
			shell->tokens[i].type = WORD;
		}
		else if (first_string != NULL)
		{
			first_string = ft_realloc(first_string, (ft_strlen(token_str) + 1));
			strcat(first_string, " ");
			strcat(first_string, token_str);
			if (ft_strchr(token_str, '\"') != NULL)
				first_string == NULL;
			free(token_str);
			token_str = NULL;
		}
	}
	printf("firsstr-> %s\n", first_string);
}
