/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:51:49 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/26 15:23:11 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_TokenType	is_type(const char *token)
{
	if (ft_strlen(token) >= 2)
	{
		if (token[0] == '>' && token[1] == '>')
			return (RIGHT_RIGHT);
		if (token[0] == '<' && token[1] == '<')
			return (LEFT_LEFT);
	}
	if (token[0] == '|')
		return (PIPE);
	if (token[0] == '<')
		return (LEFT);
	if (token[0] == '>')
		return (RIGHT);
	return (WORD);
}

int	count_quotes(char *input)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
			quotes++;
	}
	return (quotes);
}

void	tokenization(t_shell *shell, char *input)
{
	int			i;
	char		**split_input;
	t_tokens	*tokens;

	i = 0;
	shell->num_tokens = 0;
	split_input = custom_split(input);
	while (split_input[shell->num_tokens])
		shell->num_tokens++;
	tokens = malloc((shell->num_tokens + 1) * sizeof(t_tokens));
	while (i < shell->num_tokens)
	{
		tokens[i].type = is_type(split_input[i]);
		tokens[i].token = malloc((ft_strlen(split_input[i]) + 1) \
		* sizeof(char));
		ft_strcpy(tokens[i].token, split_input[i]);
		tokens[i].id = i;
		i++;
	}
	tokens[i].token = NULL;
	tokens[i].id = -1;
	free_double_str(split_input);
	free(split_input);
	shell->tokens = tokens;
}
