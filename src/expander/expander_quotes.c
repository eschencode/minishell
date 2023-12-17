/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:57:14 by aeastman          #+#    #+#             */
/*   Updated: 2023/12/17 13:19:36 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_realloc(char *str, int size)
{
	char *new_str;
	int old_size;

	old_size = ft_strlen(str);
	new_str = malloc(sizeof(char) * (old_size + size + 1));
	strncpy(new_str, str, old_size);
	free(str);
	return (new_str);
}

void shift_tokens_up(t_shell *shell, int index, int size) {
    
	int i;

	i = index;
	printf("freeing at index->%d\n", index);
	free(shell->tokens[index].token);

    while (i < size) {
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
	printf("arr len -> %d\n", i);
	return (i);
}

void	expander_quotes(t_shell *shell)
{
	int i;
	int first_flag;
	char *first_string;
	char *token_str;
	char *new_str;

	i = -1;
	first_flag = 0;
	first_string = NULL;
	while (shell->tokens[++i].token)
	{
		token_str = shell->tokens[i].token;
		printf("reading chr->%s\n", token_str);
		if (first_flag == 0 && ft_strchr(token_str, '\"') != NULL)
		{
			first_string = token_str;
			shell->tokens[i].type = WORD;
			first_flag = 1;
		}
		else if (first_flag == 1)
		{
			if (ft_strchr(token_str, '\"') != NULL)
				first_flag = 0;
			shift_tokens_up(shell, i, get_tokens_len(shell));
			i--;
		}
	}
}