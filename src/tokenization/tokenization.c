#include "../../include/minishell.h"

TokenType is_type(const char *token)
{
	int i = 0;
	while(token[i])
	{
		if(token[i] == '|')
			return(PIPE);
		if(token[i] == '<' && token[i +1] == '<')
			return(LEFT_LEFT);
		else if(token[i] == '<')
			return(LEFT);
		if(token[i] == '>' && token[i+1] == '>')
			return(RIGHT_RIGHT);
		else if(token[i] == '>')
			return(RIGHT);
		if(token[i] == '\'')
			return(SINGLE_QUOTE);
		if(token[i] == '"')
			return(DOUBLE_QUOTE);
		i++;
	}
	return(WORD);
}

int count_quotes(char *input)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
			quotes++;
	}
	return (quotes);
}

char *handle_quotes(char *input)
{
	int i;
	int j;
	int quotes;
	char *spaced_input;

	quotes = count_quotes(input);
	spaced_input = (char *)malloc((ft_strlen(input) + (quotes * 2) + 1));
	i = -1;
	j = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			spaced_input[j] = ' ';
			spaced_input[++j] = input[i];
			spaced_input[++j] = ' ';
		}
		else
			spaced_input[j] = input[i];
		j++;
	}
	spaced_input[j] = '\0';
	free(input);
	return (spaced_input);
}

t_tokens *tokenization(char *input)
{
	int i;
	int num_tokens;
	char *quotes_spaced_input;
	char **split_input;
	t_tokens *tokens;

	num_tokens = 0;
	i = 0;

	if (count_quotes(input))
		input = handle_quotes(input);
	split_input = ft_split(input, ' ');
	free(input);
	if(split_input)
	{
		while(split_input[num_tokens])
			num_tokens++;
	}

	tokens = malloc((num_tokens + 1) * sizeof(t_tokens));
	while(i < num_tokens)
	{
		tokens[i].type = is_type(split_input[i]);
		tokens[i].token = malloc((ft_strlen(split_input[i]) + 1) * sizeof(char));
		ft_strlcpy(tokens[i].token, split_input[i], (ft_strlen(split_input[i])));
		tokens[i].id = i;
		i++;
	}
	tokens[i].token = NULL;
	tokens[i].id = -1;
	i = -1;
	while (split_input[++i])
		free(split_input[i]);
	free(split_input);
	return(tokens);
}
