/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:57:14 by aeastman          #+#    #+#             */
/*   Updated: 2023/12/16 17:23:50 by aeastman         ###   ########.fr       */
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

void shift_tokens_up(t_shell *shell, int index, int size) {
    
	int i;

	i = index;
	free(shell->tokens[index].token);

    while (i < size - 1) {
        shell->tokens[i].token = shell->tokens[i + 1].token;
		i++;
    }

    shell->tokens[size - 1].token = NULL;
}

int		get_tokens_len(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->tokens[i].token)
		i++;
	return (i);
}

void	expander_quotes(t_shell *shell)
{
	int i;
	char *first_string;
	char *token_str;
	char *new_str;

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
			new_str = ft_realloc(first_string, (ft_strlen(token_str) + 1));
			ft_strlcpy(first_string, new_str, ft_strlen(new_str));
			strcat(first_string, " ");
			strcat(first_string, token_str);
			if (ft_strchr(token_str, '\"') != NULL)
				first_string == NULL;
			shift_tokens_up(shell, i, get_tokens_len(shell));
		}
	}
	printf("firsstr-> %s\n", first_string);
}
