#include "../../include/minishell.h"

TokenType is_type(const char *token)
{
	int i = 0;
	while(token[i])
	{
		if(token[i] == '|')
			return(PIPE);
		if(token[i] == '<' && token[i + 1] == '<')
			return(LEFT_LEFT);
		else if(token[i] == '<')
			return(LEFT);
		if(token[i] == '>' && token[i + 1] == '>')
			return(RIGHT_RIGHT);
		else if(token[i] == '>')
			return(RIGHT);
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

t_tokens *tokenization(t_shell *shell, char *input)
{
	int i;
	int num_tokens;
	char **split_input;
	t_tokens *tokens;

	num_tokens = 0;
	i = 0;
	split_input = ft_split(input, ' ');
	free(input);
	if(split_input)
	{
		while(split_input[num_tokens])
			num_tokens++;
	}
	shell->num_tokens = num_tokens;
	tokens = malloc((num_tokens + 1) * sizeof(t_tokens));
	while(i < num_tokens)
	{
		tokens[i].type = is_type(split_input[i]);
		tokens[i].token = malloc((ft_strlen(split_input[i]) + 1) * sizeof(char));
		strcpy(tokens[i].token, split_input[i]);
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
